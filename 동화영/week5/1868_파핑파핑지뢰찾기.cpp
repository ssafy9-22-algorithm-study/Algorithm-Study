/* 파핑파핑 지뢰찾기 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <queue>
using namespace std;
#define MAX_N 300
#define DIR_NUM 8

struct Node {
	int y;
	int x;
};

int ydir[DIR_NUM] = { -1, -1, 0, 1, 1, 1, 0, -1 }; // 상 ~ (반시계)
int xdir[DIR_NUM] = { 0, -1, -1, -1, 0, 1, 1, 1 };

int visited[MAX_N][MAX_N]; // 방문 여부
int MAP[MAX_N][MAX_N]; // -1:지뢰
int N; // 지뢰판의 사이즈

// 지뢰 수 세기
void countMine() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j] == -1) {
				for (int k = 0; k < DIR_NUM; k++) {
					int ny = i + ydir[k];
					int nx = j + xdir[k];

					if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
					if (MAP[ny][nx] == -1) continue;

					MAP[ny][nx]++;
				}
			}
		}
	}
}

// 주변에 지뢰 없는 칸(0) 터뜨리기
int bfs() {
	int ret = 0;

	queue<Node> q;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// 주변에 지뢰가 없는 칸 && 방문하지 않은 칸
			if (MAP[i][j] == 0 && visited[i][j] != 1) {
				// 해당 칸부터 퍼지기 시작
				q.push({ i,j });
				visited[i][j] = 1;
				ret++;

				while (!q.empty()) {
					Node now = q.front();
					q.pop();

					for (int k = 0; k < DIR_NUM; k++) {
						int ny = now.y + ydir[k];
						int nx = now.x + xdir[k];

						if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue; // 지뢰판 밖은 무시
						if (visited[ny][nx] == 1) continue; // 이미 방문했다면 무시
						if (MAP[ny][nx] == -1) continue; // 지뢰는 퍼지지 않는다

						visited[ny][nx] = 1; // 방문여부는 표기

						// 다음 탐색할 칸은 MAP의 값이 0인 칸들만
						if (MAP[ny][nx] > 0) continue;
						q.push({ ny, nx });
					}
				}
			}
		}
	}

	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		memset(visited, 0, sizeof(visited));
		memset(MAP, 0, sizeof(MAP));

		// input
		cin >> N;

		// *(지뢰)는 -1로 표기
		string inp;
		for (int i = 0; i < N; i++) {
			cin >> inp;
			for (int j = 0; j < N; j++) {
				if (inp[j] == '*') {
					MAP[i][j] = -1;
				}
			}
		}

		// 1. 지뢰 수 세기
		countMine();

		// 2. 주변에 지뢰 없는 칸(0) 터뜨리기 => bfs
		int cnt = bfs();
		
		// 3. 아직 안 터진 칸 터뜨리기
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// 지뢰는 아니면서 방문하지 않은 칸
				if (MAP[i][j] != -1 && visited[i][j] != 1) {
					cnt++;
				}
			}
		}

		// output
		cout << "#" << tc << " " << cnt << '\n';
	}

	return 0;
}

/*
1
5
..*..
..*..
.*..*
.*...
.*...

0 2 -1 2 0
1 3 -1 3 1
2 -1 3 2 -1
3 2 3 1 1
2 -1 2 0 0

*/