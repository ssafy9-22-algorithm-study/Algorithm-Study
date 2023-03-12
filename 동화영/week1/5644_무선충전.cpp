#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAX_M 100
#define DIR_NUM 4
#define SIZE_N 10

struct CA {
	int y;
	int x;
	int c; // 거리
	int p; // power
};

struct player {
	int y;
	int x;
};

vector<CA> CAs; // AP의 정보들
vector<int> MAP[SIZE_N][SIZE_N]; // 지도
int userDir[2][MAX_M]; // 사용자 2인의 이동 경로
int ydir[DIR_NUM] = { -1, 0, 1, 0 }; // 상우하좌
int xdir[DIR_NUM] = { 0, 1, 0, -1 };
player p[2];
int A; // 충전소 개수
int ans;

void init() {
	ans = 0;
	CAs.clear();
	for (int i = 0; i < SIZE_N; i++) {
		for (int j = 0; j < SIZE_N; j++) {
			MAP[i][j].clear();
		}
	}
}

bool InRange(int ny, int nx) {
	return ny >= 0 && nx >= 0 && ny < SIZE_N && nx < SIZE_N;
}

void drawMAP(int ind) {
	bool visited[SIZE_N][SIZE_N] = { 0, };
	queue<player> myQ;
	CA curr = CAs[ind];
	MAP[curr.y][curr.x].push_back(ind);

	myQ.push({ curr.y, curr.x });
	visited[curr.y][curr.x] = 1;
	while (!myQ.empty()) {
		player now = myQ.front();
		myQ.pop();

		for (int i = 0; i < DIR_NUM; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (!InRange(ny, nx)) continue;
			if (visited[ny][nx]) continue;
			if (abs(ny - curr.y) + abs(nx - curr.x) > curr.c) continue;

			visited[ny][nx] = 1;
			MAP[ny][nx].push_back(ind);
			myQ.push({ ny,nx });
		}
	}
}

int findAgain(int st) {
	player p1 = p[0], p2 = p[1];
	int sz1 = MAP[p1.y][p1.x].size(), sz2 = MAP[p2.y][p2.x].size();

	int maxSum = st;
	for (int i = 0; i < sz1; i++) {
		for (int j = 0; j < sz2; j++) {
			if (MAP[p1.y][p1.x][i] == MAP[p2.y][p2.x][j]) continue;
			int sum = CAs[MAP[p1.y][p1.x][i]].p + CAs[MAP[p2.y][p2.x][j]].p;

			if (sum > maxSum) maxSum = sum;
		}
	}

	return maxSum;
}

void charge() {
	int power[2] = { -1, -1 };
	for (int i = 0; i < 2; i++) {
		int sz = MAP[p[i].y][p[i].x].size();
		if (sz == 0) continue;

		int tmp = 0, tmpInd = 0;
		for (int j = 0; j < sz; j++) {
			int target = MAP[p[i].y][p[i].x][j];
			if (CAs[target].p > tmp) {
				tmp = CAs[target].p;
				tmpInd = target;
			}
		}
		power[i] = tmpInd;
	}

	if (power[0] == -1 && power[1] == -1) return;
	else if (power[0] != -1 && power[1] != -1) {
		if (power[0] != power[1]) {
			ans += (CAs[power[0]].p + CAs[power[1]].p);
		}
		else {
			ans += findAgain(CAs[power[0]].p);
		}
	}
	else { // 둘 중 한 명만 0
		if (power[0] == -1) ans += CAs[power[1]].p;
		else ans += CAs[power[0]].p;
	}
}

void move(int ind) {
	for (int i = 0; i < 2; i++) {
		p[i].y += ydir[userDir[i][ind]];
		p[i].x += xdir[userDir[i][ind]];
	}
}

int main() {
	freopen("input5644.txt", "r", stdin);

	int T;
	cin >> T;

	int M;
	for (int tc = 1; tc <= T; tc++) {
		init();

		cin >> M >> A;

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < M; j++) {
				cin >> userDir[i][j];
				userDir[i][j]--;
			}
		}

		int iy, ix, ic, ip;
		for (int i = 0; i < A; i++) {
			cin >> ix >> iy >> ic >> ip;
			iy--; ix--;
			CAs.push_back({ iy, ix, ic, ip });

			drawMAP(i);
		}

		p[0] = { 0,0 }; p[1] = { SIZE_N - 1, SIZE_N - 1 };

		for (int i = 0; i <= M; i++) {
			// 충전 가능시 충전
			charge();
			//이동
			move(i);
		}

		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}

/*
1
20 3
2 2 3 2 2 2 2 3 3 4 4 3 2 2 3 3 3 2 2 3
4 4 1 4 4 1 4 4 1 1 1 4 1 4 3 3 3 3 3 3
4 4 1 100
7 10 3 40
6 3 2 70
*/