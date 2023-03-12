// 1. 맵의 각 위치에서 시작하면 몇이 채취가 되는지 저장
// 2. 1번의 맵을 돌면서(M만큼 겹치지 않게) 최선의 조합을 탐색
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAX_N 10

int MAP[MAX_N][MAX_N];

int picked[MAX_N][MAX_N]; // 각 지점을 시작으로 M만큼의 범위에서 채취할 수 있는 꿀의 최대 수익
vector<int> myV; // picked를 탐색하기 위한 좌표별 벌의 양들
int vMax; // dfs에서 구한 최대

int N, M, C; // N: 사이즈, M: 한번의 채취범위, C: 용기의 양

void dfs(int pInd, int sum, int profit) {
	if (profit > vMax) {
		vMax = profit;
	}

	if (pInd == M) {
		return;
	}

	for (int i = pInd; i < M; i++) {
		int nSum = sum + myV[i];

		if (nSum > C) continue; // vector가 정렬된 상태이므로 더이상 탐색 불가

		dfs(i + 1, nSum, profit + myV[i] * myV[i]);
	}
}

// 좌표 내 모든 지점에서부터 M만큼의 범위를 채취한다고 가정
// 이 때 가능한 꿀의 최대 수익
void pickMAP() {
	int maxH = 0;
	for (int i = 0; i < N; i++) { // 각 행
		for (int j = 0; j <= N - M; j++) { // 각 행에서 가능한 시작 지점(열)
			myV.clear();

			for (int k = 0; k < M; k++) {
				myV.push_back(MAP[i][j + k]);
			}

			sort(myV.begin(), myV.end(), greater<int>());

			vMax = 0;
			dfs(0, 0, 0);

			picked[i][j] = vMax;

		}
	}
}

int findMore(int y, int x) {
	int tmpMax = 0;
	for (int i = x + M; i <= N - M; i++) {
		if (picked[y][i] > tmpMax) tmpMax = picked[y][i];
	}

	for (int i = y + 1; i < N; i++) {
		for (int j = 0; j <= N - M; j++) {
			if (picked[i][j] > tmpMax) tmpMax = picked[i][j];
		}
	}

	return tmpMax;
}

int main() {
	//freopen("input2115.txt", "r", stdin);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M >> C;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> MAP[i][j];
			}
		}

		pickMAP();

		int maxHoney = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= N - M; j++) {
				int honey = findMore(i, j) + picked[i][j];
				if (honey > maxHoney) maxHoney = honey;
			}
		}

		cout << "#" << tc << " " << maxHoney << '\n';
	}

	return 0;
}
