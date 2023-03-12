#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define COST_NUM 4
#define MONTH_NUM 12

int minCost, currCost;
int cost[COST_NUM]; // 1일 1달 3달 1년
int inter[COST_NUM] = { 0, 1, 3, 12 };
int days[MONTH_NUM];

// 각 케이스별 데이터 초기화
void init() {
	// 1년권은 1월 1일 등록만 가능
	minCost = cost[COST_NUM - 1];
	currCost = 0;
}

void dfs(int lev) {
	if (lev >= 12) { // 12월까지 탐색 완료시
		if (currCost < minCost) { // 최소 비용 발견 여부 확인
			minCost = currCost; // 최소 비용 갱신
		}
		return;
	}

	// 금번에 탐색할 월 이용일수가 0일인 경우, 바로 다음달 탐색 후 return;
	if (days[lev] == 0) {
		dfs(lev + 1);
		return;
	}

	// 3개월권부터 탐색
	for (int i = COST_NUM - 2; i >= 0; i--) {
		// i == 0 : 해당 월에 1일권 이용
		int currC = i == 0 ? cost[i] * days[lev] : cost[i];
		int currM = i == 0 ? 1 : inter[i]; // int inter[COST_NUM] = { 0, 1, 3, 12 };

		// 이번 비용 추가
		currCost += currC;

		// 등록 이후 다음 월 탐색
		dfs(lev + currM);

		// 비용 복구
		currCost -= currC;
	}
}

int main() {
	freopen("input1952.txt", "r", stdin);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// 1. 입력
		for (int i = 0; i < COST_NUM; i++) {
			cin >> cost[i];
		}

		for (int i = 0; i < MONTH_NUM; i++) {
			cin >> days[i];
		}

		// 2. 초기화
		init();

		// 3. 동작 - 1월부터 탐색 시작
		dfs(0);

		// 4. 출력
		cout << "#" << tc << " " << minCost << '\n';
	}

	return 0;
}

/*
1
10 40 100 300
0 0 2 9 1 5 0 0 0 0 0 0
*/