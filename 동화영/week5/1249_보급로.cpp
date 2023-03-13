/* 보급로 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
#define MAX_N 100

struct COOR {
	int y;
	int x;
	int cnt;

	// cnt 오름차순
	bool operator < (COOR nxt) const {
		return cnt > nxt.cnt;
	}
};

int ydir[] = { -1, 1, 0, 0 }; // 상하좌우
int xdir[] = { 0, 0, -1, 1 };

int MAP[MAX_N][MAX_N]; // 지도
int N; // 지도의 크기

int findRoad() {
	priority_queue<COOR> pq;
	pq.push({ 0,0,0 });

	int visited[MAX_N][MAX_N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			visited[i][j] = 21e8;

	visited[0][0] = 0;

	int ans; // 도착하는데 필요한 최소 복구시간 (답)
	while (!pq.empty()) {
		COOR now = pq.top();
		pq.pop();

		//if (visited[now.y][now.x] <= now.cnt) continue;

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			
			int nCnt = visited[now.y][now.x] + MAP[ny][nx];
			if (visited[ny][nx] <= nCnt) continue;

			pq.push({ ny, nx, nCnt });
			visited[ny][nx] = nCnt;
		}
	}
	
	ans = visited[N - 1][N - 1];

	return ans;
}

int main() {
	freopen("input1249.txt", "r", stdin);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		
		// input
		cin >> N;
		char a;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				cin >> a;
				MAP[i][j] = a - '0';
			}
				

		// solve
		int ans = findRoad();

		// output
		cout << "#" << tc << " " << ans << '\n';
	}

	return 0;
}

/*
2
4
0100
1110
1011
1010
6
011001
010100
010011
101001
010101
111010
*/