#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
#define MAX_WH 20
#define DIR_NUM 4

struct Node {
	int y;
	int x;
};

int ydir[DIR_NUM] = { -1, 1, 0, 0 }; // 상하좌우
int xdir[DIR_NUM] = { 0, 0, -1, 1 };

int MAP[MAX_WH][MAX_WH];
int N; // 구슬 쏘는 횟수
int H, W; // 벽돌판 사이즈 H*W

int brick; // 벽돌의 총 개수
int curCnt; // 현 기준 남은 벽돌
int ans; // 남는 벽돌의 수

bool InRange(int y, int x) {
	return y >= 0 && x >= 0 && y < H && x < W;
}

void breakBrick(int ind) {
	// 시작점 찾기 - 위에서부터 가장 먼저 찾은 벽돌의 위치
	Node start = { 0,0 };
	for (int i = 0; i < H; i++) {
		if (MAP[i][ind] != 0) {
			start = { i, ind };
			break;
		}
	}

	queue<Node> q;
	q.push(start);

	// 깰 수 있는 모든 벽돌 깨기 => MAP의 값을 0으로 표기
	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		int num = MAP[now.y][now.x];

		if (num == 0) continue; // 이미 깨진 블럭이라면 무시

		// 벽돌 깨뜨리기
		MAP[now.y][now.x] = 0;
		curCnt--;

		// 해당 벽돌로부터 영향받는 벽돌들 queue에 넣어주기
		for (int i = 0; i < DIR_NUM; i++) {
			for (int j = 1; j < num; j++) {
				int ny = now.y + ydir[i] * j;
				int nx = now.x + xdir[i] * j;

				if (!InRange(ny, nx)) continue;
				if (MAP[ny][nx] == 0) continue;

				q.push({ ny, nx });
			}
		}
	}
}

// 벽돌들 아래로 끌어내리기
void cleanBrick() {
	queue<int> q; // 벽돌이 있는 칸의 숫자들

	for (int i = 0; i < W; i++) { // 각 열에 대해
		for (int j = H - 1; j >= 0; j--) { // 아래에서부터
			if (MAP[j][i] != 0) { // 벽돌이 있다면
				q.push(MAP[j][i]); // queue에 넣기
				MAP[j][i] = 0; // 해당 칸은 이제 0으로 셋팅
			}
		}

		int ind = H - 1; // 맨 아래 행부터
		while (!q.empty()) {
			MAP[ind][i] = q.front(); // 벽돌값 넣어주기
			q.pop();
			ind--; // index 위로 옮겨주기
		}
	}
}

// lev번째 구슬을 던질 열 찾기
void selectLine(int lev) {
	// N번 구슬을 굴렀다면 갱신
	if (lev == N) {
		if (curCnt < ans) {
			ans = curCnt;
		}

		return;
	}

	// 전체 열 중 고르기
	for (int i = 0; i < W; i++) {
		if (MAP[H - 1][i] == 0) continue; // 이미 다 깨진 열은 무시

		// 기존의 MAP 복사해두기
		int tmp[MAX_WH][MAX_WH] = { 0, };
		memcpy(tmp, MAP, sizeof(MAP));
		// 기존에 남은 벽돌의 개수 복사해두기
		int tmpCnt = curCnt;

		breakBrick(i); // 깰 수 있는 벽돌 모두 깨기 => bfs
		cleanBrick(); // 벽돌 아래로 끌어내리기

		// lev번째 구슬을 쏘았더니 남은 구슬이 없다면
		if (curCnt == 0) {
			ans = 0;
			return;
		}

		selectLine(lev + 1); // 다음 구슬 어디에 굴릴지 찾으러 가기

		// 원복
		memcpy(MAP, tmp, sizeof(tmp));
		curCnt = tmpCnt;
	}
}

int main() {
	freopen("input5656.txt", "r", stdin);
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		// reset
		ans = 21e8;
		brick = 0;
		curCnt = 0;

		// input
		cin >> N >> W >> H;

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> MAP[i][j];

				if (MAP[i][j] != 0) brick++; // 벽돌 개수 세기
			}
		}

		// solve
		curCnt = brick;
		selectLine(0);

		// output
		cout << "#" << tc << " " << ans << '\n';
	}

	return 0;
}

/*
2
3 10 10
0 0 0 0 0 0 0 0 0 0
1 0 1 0 1 0 0 0 0 0
1 0 3 0 1 1 0 0 0 1
1 1 1 0 1 2 0 0 0 9
1 1 4 0 1 1 0 0 1 1
1 1 4 1 1 1 2 1 1 1
1 1 5 1 1 1 1 2 1 1
1 1 6 1 1 1 1 1 2 1
1 1 1 1 1 1 1 1 1 5
1 1 7 1 1 1 1 1 1 1
2 9 10
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0
1 1 0 0 1 0 0 0 0
1 1 0 1 1 1 0 1 0
1 1 0 1 1 1 0 1 0
1 1 1 1 1 1 1 1 0
1 1 3 1 6 1 1 1 1
1 1 1 1 1 1 1 1 1
*/

/*
1
4 12 15 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
9 9 9 9 9 9 9 9 9 9 9 9	 
*/