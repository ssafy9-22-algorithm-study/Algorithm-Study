/* �̼����� �ȳ�! */
#include <iostream>
#include <cstring>
using namespace std;
#define MAX_R 50
#define DIR_NUM 4

int rdir[DIR_NUM] = { -1, 0, 1, 0 }; // �������
int cdir[DIR_NUM] = { 0, 1, 0, -1 };

int MAP[MAX_R][MAX_R]; // ��
int TMP[MAX_R][MAX_R]; // ���� Ȯ��Ǵ� ��
int R, C; // ���� ������ R*C

int mach; // ����û���� ��ġ�� ��(��)

// �̼����� Ȯ�� - 4����
void spread() {
	memset(TMP, 0, sizeof(TMP));

	// �̼������� �ִ� ĭ�� Ȯ��
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (MAP[i][j] == 0) continue; // �̼����� 0�� ������ ����

			int amt = MAP[i][j];
			int cnt = 0;
			for (int k = 0; k < DIR_NUM; k++) {
				int nr = i + rdir[k];
				int nc = j + cdir[k];

				if (nr < 0 || nc < 0 || nr >= R || nc >= C) continue; // �����δ� Ȯ�� X
				if (nc == 0 && (nr == mach || nr == mach + 1)) continue; // ����û���Ⱑ �ִ� ĭ���δ� Ȯ�� X
				
				// Ȯ��
				TMP[nr][nc] += amt / 5;
				cnt++;
			}

			// Ȯ��� ��ŭ ���ֱ�
			TMP[i][j] -= (amt / 5) * cnt;
		}
	}

	// Ȯ��� �̼����� ��� �ջ�
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			MAP[i][j] += TMP[i][j];
}

// ����û���� �۵� - ��/�Ʒ�
void machOn() {
	// �� - �ð�������� ȸ���ϸ� ����ĭ���� ����
	int dir = 0;
	int cr = mach + rdir[dir];
	int cc = 0;
	while (!(cr == mach && cc == 0)) {
		int pr = cr - rdir[dir];
		int pc = cc - cdir[dir];

		MAP[pr][pc] = MAP[cr][cc];
		MAP[cr][cc] = 0;

		cr += rdir[dir];
		cc += cdir[dir];

		if (cr < 0 || cc < 0 || cr >= R || cc >= C || (cr == mach + 1 && cc == C - 1)) {
			cr -= rdir[dir];
			cc -= cdir[dir];
			dir = (dir + 1) % DIR_NUM;
			cr += rdir[dir];
			cc += cdir[dir];
		}
	}
	MAP[mach][0] = 0;
	
	// �Ʒ� - �ݽð�������� ȸ���ϸ� ���� ĭ���� ����
	dir = 2;
	cr = mach + 1 + rdir[dir];
	cc = 0;
	while (!(cr == mach + 1 && cc == 0)) {
		int pr = cr - rdir[dir];
		int pc = cc - cdir[dir];

		MAP[pr][pc] = MAP[cr][cc];
		MAP[cr][cc] = 0;

		cr += rdir[dir];
		cc += cdir[dir];

		if (cr < 0 || cc < 0 || cr >= R || cc >= C || (cr == mach && cc == C - 1)) {
			cr -= rdir[dir];
			cc -= cdir[dir];
			dir = (dir - 1 + 4) % DIR_NUM;
			cr += rdir[dir];
			cc += cdir[dir];
		}
	}
	MAP[mach + 1][0] = 0;
}

int main() {
	int T; // ����Ǵ� �ð�
	mach = -1;

	// input
	cin >> R >> C >> T;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == -1) {
				MAP[i][j] = 0; // �ش� ĭ�� �̼������� 0���� �ʱ�ȭ

				if(mach == -1) mach = i; // ��ġ ����
			}
		}
	}

	// T�� ���� ����
	for (int i = 0; i < T; i++) {
		spread(); // �̼����� Ȯ��
		machOn(); // ����û���� �۵�
	}

	// ���� ������ �� ���ϱ�
	int ans = 0;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			ans += MAP[i][j];

	// output
	cout << ans << '\n';

	return 0;
}