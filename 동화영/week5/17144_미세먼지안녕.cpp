/* 미세먼지 안녕! */
#include <iostream>
#include <cstring>
using namespace std;
#define MAX_R 50
#define DIR_NUM 4

int rdir[DIR_NUM] = { -1, 0, 1, 0 }; // 상우하좌
int cdir[DIR_NUM] = { 0, 1, 0, -1 };

int MAP[MAX_R][MAX_R]; // 방
int TMP[MAX_R][MAX_R]; // 매초 확산되는 양
int R, C; // 방의 사이즈 R*C

int mach; // 공기청정기 위치의 행(위)

// 미세먼지 확산 - 4방향
void spread() {
	memset(TMP, 0, sizeof(TMP));

	// 미세먼지가 있는 칸은 확산
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (MAP[i][j] == 0) continue; // 미세먼지 0인 구간은 무시

			int amt = MAP[i][j];
			int cnt = 0;
			for (int k = 0; k < DIR_NUM; k++) {
				int nr = i + rdir[k];
				int nc = j + cdir[k];

				if (nr < 0 || nc < 0 || nr >= R || nc >= C) continue; // 밖으로는 확산 X
				if (nc == 0 && (nr == mach || nr == mach + 1)) continue; // 공기청정기가 있는 칸으로는 확산 X
				
				// 확산
				TMP[nr][nc] += amt / 5;
				cnt++;
			}

			// 확산된 만큼 빼주기
			TMP[i][j] -= (amt / 5) * cnt;
		}
	}

	// 확산된 미세먼지 양과 합산
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			MAP[i][j] += TMP[i][j];
}

// 공기청정기 작동 - 위/아래
void machOn() {
	// 위 - 시계방향으로 회전하며 이전칸으로 당기기
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
	
	// 아래 - 반시계방향으로 회전하며 이전 칸으로 당기기
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
	int T; // 진행되는 시간
	mach = -1;

	// input
	cin >> R >> C >> T;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == -1) {
				MAP[i][j] = 0; // 해당 칸의 미세먼지는 0으로 초기화

				if(mach == -1) mach = i; // 위치 저장
			}
		}
	}

	// T초 동안 진행
	for (int i = 0; i < T; i++) {
		spread(); // 미세먼지 확산
		machOn(); // 공기청정기 작동
	}

	// 최종 먼지의 양 구하기
	int ans = 0;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			ans += MAP[i][j];

	// output
	cout << ans << '\n';

	return 0;
}