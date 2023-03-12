#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define MAX_N 12
#define DIR_NUM 4

// 주어진 CORE의 좌표
struct CORE {
	int y;
	int x;
};

vector<CORE> cores;
int MAP[MAX_N][MAX_N];
int ydir[DIR_NUM] = { -1, 1, 0, 0 }; // 상하좌우
int xdir[DIR_NUM] = { 0, 0, -1, 1 };
int N;

int connected; // 연결된 코어의 수
int minLine; // 연결 길이의 최소값

int InRange(int y, int x) {
	if (y < 0 || x < 0 || y >= N || x >= N) return 0; // MAP의 바깥
	else if (y == 0 || x == 0 || y == N - 1 || x == N - 1) return 1; // MAP의 가장자리
	else return 2; // MAP의 내부
}

// ind번째의 CORE를 i방향으로 연결 가능한가?
// 가능하다면 길이가 몇인가?
int canConn(int ind, int dir) {
	CORE curr = cores[ind];

	int lines = 0;
	for (int i = 1; i < N; i++) {
		int ny = curr.y + ydir[dir] * i;
		int nx = curr.x + xdir[dir] * i;

		int flag = InRange(ny, nx);
		if (flag == 2 || flag == 1) {
			if (MAP[ny][nx] == 0) {
				lines++; // 선 연결 가능
			}
			else {
				return -1; // MAP 내부이나 해당 칸에 core, line 존재 시 설치 불가
			}
		}
		else { // 가능한 직선 연결하다가 MAP 외부를 만남
			break;
		}
	}

	return lines; // lines 길이만큼 연결 가능하다고 검증 완료
}

// cores의 ind번째 탐색하러 왔다
void dfs(int ind, int currCon, int currLine) {
	if (ind == cores.size()) {
		if (connected < currCon) {
			connected = currCon;
			minLine = currLine;
		}
		if (connected == currCon && minLine > currLine) {
			minLine = currLine;
		}

		return;
	}

	CORE curr = cores[ind];
	for (int i = 0; i < DIR_NUM; i++) {
		int len = canConn(ind, i); // ind번째의 CORE를 i방향으로 연결 가능한가?
		if (len <= 0) continue;

		int tmpMAP[MAX_N][MAX_N];
		memcpy(tmpMAP, MAP, sizeof(MAP));

		// 선 연결이 가능하다고 검증 완료 -> 선 연결하기
		for (int j = 1; j <= len; j++) {
			int ny = curr.y + ydir[i] * j;
			int nx = curr.x + xdir[i] * j;

			MAP[ny][nx] = 2;
		}

		dfs(ind + 1, currCon + 1, currLine + len);

		memcpy(MAP, tmpMAP, sizeof(tmpMAP));
	}

	dfs(ind + 1, currCon, currLine); // 해당 코어를 연결하지 않는 것도 고려
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;

		// 초기화
		cores.clear();
		connected = 0;
		minLine = 21e8;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> MAP[i][j];
				if (MAP[i][j] == 1) {
					// MAP의 가장자리에 위치한 Core는 이미 연결 완료 => 탐색 필요 X
					if (InRange(i, j) == 1) {
						connected++;
						continue;
					}

					cores.push_back({ i,j });
				}
			}
		}

		dfs(0, connected, 0);

		cout << "#" << tc << " " << minLine << '\n';
	}

	return 0;
}