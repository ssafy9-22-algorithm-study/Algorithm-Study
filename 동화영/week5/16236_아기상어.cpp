/* �Ʊ� ��� */
#include <iostream>
#include <queue>
using namespace std;
#define MAX_N 20
#define DIR_NUM 4

struct Node {
	int y;
	int x;
	int sz;

	// sz ��������
	// y ��������
	// x ��������
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

int ydir[DIR_NUM] = { -1, 0, 0, 1 }; // ���¿���
int xdir[DIR_NUM] = { 0, -1, 1, 0 };

priority_queue<Node> fishes; // ������
int MAP[MAX_N][MAX_N]; // 1~6: �����, 0: ��ĭ|���� ĭ
int N;

Node shark; // �Ʊ����� ��ǥ �� ������
int eaten; // ���� ����� ��(������ ���� �� �ʱ�ȭ)
int sec; // �ҿ� �ð�

bool InRange(int y, int x) {
	return y >= 0 && x >= 0 && y < N && x < N;
}

// ��ƸԾ��� : 1 ��ȯ
// ��Ƹ��� �� ���� : 0 ��ȯ
int bfs() {
	priority_queue<Node> q; // ���
	int visited[MAX_N][MAX_N] = { 0, }; // �湮����

	// �Ʊ� ����� ���� ��ġ�κ��� ����
	q.push({ shark.y, shark.x, 0 });
	visited[shark.y][shark.x] = 1;

	while (!q.empty()) {
		// �� �Ÿ����� Ž���� �ʿ�
		// �Ÿ��� d�� ĭ�� �� ��� > ������ �켱�����̹Ƿ�
		int len = q.size();
		for (int j = 0; j < len; j++) {
			Node now = q.top();
			q.pop();

			// ���� ���� ����⸦ ã�Ҵ� -> �� �Դ´�
			if (MAP[now.y][now.x] != 0 && MAP[now.y][now.x] < shark.sz) {
				sec += (visited[now.y][now.x] - 1); // �� ����� ������ ���µ� �ҿ�� �ð�
				MAP[now.y][now.x] = 0; // ����� ��ƸԾ����� MAP�� 0����

				// �Ʊ� ����� ��ǥ �̵�
				shark.y = now.y;
				shark.x = now.x;
				eaten++; // �Ѹ��� �Ծ���
				if (eaten >= shark.sz) { // �Ʊ� ����� ũ�⸸ŭ ����⸦ ��ƸԾ��ٸ�
					shark.sz++; // �Ʊ� ��� ũ�� ����
					eaten = 0; // ī���� 0���� �ٽ� ����
				}

				return 1; // ����� ��Ҵ�!
			}

			for (int i = 0; i < DIR_NUM; i++) { // �����¿� Ž��
				int ny = now.y + ydir[i];
				int nx = now.x + xdir[i];

				if (!InRange(ny, nx)) continue;
				if (visited[ny][nx] > 0) continue;
				if (MAP[ny][nx] > shark.sz) continue; // ���� ū ������ �̵� X

				// ������ �� �ִ� ĭ
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

			if (MAP[i][j] == 9) { // �Ʊ� ��� ���� ����
				shark = { i,j,2 };
				MAP[i][j] = 0;
			}
			else if (MAP[i][j] != 0) { // ����� ���� ����
				fishes.push({ i,j,MAP[i][j] });
			}
		}
	}

	// ����ִ� ����Ⱑ ���� ������ Ž��
	while (!fishes.empty()) {
		Node now = fishes.top();
		if (now.sz >= shark.sz) break; // ���̻� ��Ƹ��� �� �ִ� ����Ⱑ ����

		// ��Ƹ��� �� ���� �� �˾Ҵµ� �̹� ���� ĭ�̴�
		// -> ���� ����� Ž���Ѵ�
		if (MAP[now.y][now.x] == 0) {
			fishes.pop();
			continue;
		}

		// ��Ƹ��� ����� Ž���Ϸ� ����
		// ��Ƹ��� �� �ִ� ����Ⱑ ���ٸ� -> ���� ũ�ų� ���� �����鿡�� �ѷ��׿��ִ�
		// ���� ���� ���� ��û�ؾ� �Ѵ� -> break;
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