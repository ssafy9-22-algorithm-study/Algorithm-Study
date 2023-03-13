/* �������� ����ã�� */
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

int ydir[DIR_NUM] = { -1, -1, 0, 1, 1, 1, 0, -1 }; // �� ~ (�ݽð�)
int xdir[DIR_NUM] = { 0, -1, -1, -1, 0, 1, 1, 1 };

int visited[MAX_N][MAX_N]; // �湮 ����
int MAP[MAX_N][MAX_N]; // -1:����
int N; // �������� ������

// ���� �� ����
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

// �ֺ��� ���� ���� ĭ(0) �Ͷ߸���
int bfs() {
	int ret = 0;

	queue<Node> q;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// �ֺ��� ���ڰ� ���� ĭ && �湮���� ���� ĭ
			if (MAP[i][j] == 0 && visited[i][j] != 1) {
				// �ش� ĭ���� ������ ����
				q.push({ i,j });
				visited[i][j] = 1;
				ret++;

				while (!q.empty()) {
					Node now = q.front();
					q.pop();

					for (int k = 0; k < DIR_NUM; k++) {
						int ny = now.y + ydir[k];
						int nx = now.x + xdir[k];

						if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue; // ������ ���� ����
						if (visited[ny][nx] == 1) continue; // �̹� �湮�ߴٸ� ����
						if (MAP[ny][nx] == -1) continue; // ���ڴ� ������ �ʴ´�

						visited[ny][nx] = 1; // �湮���δ� ǥ��

						// ���� Ž���� ĭ�� MAP�� ���� 0�� ĭ�鸸
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

		// *(����)�� -1�� ǥ��
		string inp;
		for (int i = 0; i < N; i++) {
			cin >> inp;
			for (int j = 0; j < N; j++) {
				if (inp[j] == '*') {
					MAP[i][j] = -1;
				}
			}
		}

		// 1. ���� �� ����
		countMine();

		// 2. �ֺ��� ���� ���� ĭ(0) �Ͷ߸��� => bfs
		int cnt = bfs();
		
		// 3. ���� �� ���� ĭ �Ͷ߸���
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// ���ڴ� �ƴϸ鼭 �湮���� ���� ĭ
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