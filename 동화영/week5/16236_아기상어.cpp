/* 아기 상어 */
#include <iostream>
#include <queue>
using namespace std;
#define MAX_N 20
#define DIR_NUM 4

struct Node {
	int y;
	int x;
	int sz;

	// sz 오름차순
	// y 오름차순
	// x 오름차순
	bool operator < (Node nxt) const {
		if (sz < nxt.sz) return false;
		if (sz > nxt.sz) return true;
		if (y < nxt.y) return false;
		if (y > nxt.y) return true;
		if (x < nxt.x) return false;
		if (x > nxt.x) return true;
		return false;
	}
};

int ydir[DIR_NUM] = { -1, 0, 0, 1 }; // 상좌우하
int xdir[DIR_NUM] = { 0, -1, 1, 0 };

priority_queue<Node> fishes; // 물고기들
int MAP[MAX_N][MAX_N]; // 1~6: 물고기, 0: 빈칸|먹힌 칸
int N;

Node shark; // 아기상어의 좌표 및 사이즈
int eaten; // 먹은 물고기 수(사이즈 증가 시 초기화)
int sec; // 소요 시간

bool InRange(int y, int x) {
	return y >= 0 && x >= 0 && y < N && x < N;
}

// 잡아먹었다 : 1 반환
// 잡아먹을 수 없다 : 0 반환
int bfs() {
	priority_queue<Node> q; // 경로
	int visited[MAX_N][MAX_N] = { 0, }; // 방문여부

	// 아기 상어의 현재 위치로부터 시작
	q.push({ shark.y, shark.x, 0 });
	visited[shark.y][shark.x] = 1;

	while (!q.empty()) {
		// 각 거리마다 탐색이 필요
		// 거리가 d인 칸들 중 상단 > 좌측이 우선순위이므로
		int len = q.size();
		for (int j = 0; j < len; j++) {
			Node now = q.top();
			q.pop();

			// 상어보다 작은 물고기를 찾았다 -> 얘 먹는다
			if (MAP[now.y][now.x] != 0 && MAP[now.y][now.x] < shark.sz) {
				sec += (visited[now.y][now.x] - 1); // 이 물고기 잡으러 오는데 소요된 시간
				MAP[now.y][now.x] = 0; // 물고기 잡아먹었으니 MAP은 0으로

				// 아기 상어의 좌표 이동
				shark.y = now.y;
				shark.x = now.x;
				eaten++; // 한마리 먹었다
				if (eaten >= shark.sz) { // 아기 상어의 크기만큼 물고기를 잡아먹었다면
					shark.sz++; // 아기 상어 크기 증가
					eaten = 0; // 카운팅 0부터 다시 시작
				}

				return 1; // 물고기 잡았다!
			}

			for (int i = 0; i < DIR_NUM; i++) { // 상하좌우 탐색
				int ny = now.y + ydir[i];
				int nx = now.x + xdir[i];

				if (!InRange(ny, nx)) continue;
				if (visited[ny][nx] > 0) continue;
				if (MAP[ny][nx] > shark.sz) continue; // 상어보다 큰 물고기는 이동 X

				// 지나갈 수 있는 칸
				q.push({ ny, nx, now.sz + 1 });
				visited[ny][nx] = visited[now.y][now.x] + 1;
			}
		}
	}

	return 0;
}

int main() {
	// input
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];

			if (MAP[i][j] == 9) { // 아기 상어 정보 저장
				shark = { i,j,2 };
				MAP[i][j] = 0;
			}
			else if (MAP[i][j] != 0) { // 물고기 정보 저장
				fishes.push({ i,j,MAP[i][j] });
			}
		}
	}

	// 살아있는 물고기가 있을 때까지 탐색
	while (!fishes.empty()) {
		Node now = fishes.top();
		if (now.sz >= shark.sz) break; // 더이상 잡아먹을 수 있는 물고기가 없다

		// 잡아먹을 수 있을 줄 알았는데 이미 먹힌 칸이다
		// -> 다음 물고기 탐색한다
		if (MAP[now.y][now.x] == 0) {
			fishes.pop();
			continue;
		}

		// 잡아먹을 물고기 탐색하러 간다
		// 잡아먹을 수 있는 물고기가 없다면 -> 상어보다 크거나 같은 물고기들에게 둘러쌓여있다
		// 엄마 상어에게 도움 요청해야 한다 -> break;
		if (bfs() == 0) break;
	}

	// output
	cout << sec << '\n';

	return 0;
}

/*
4
4 3 2 1
0 3 3 3
0 3 9 3
1 2 3 4
*/