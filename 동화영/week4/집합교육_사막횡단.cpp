/* 사막횡단 */
#include <iostream>
#include <vector>
using namespace std;

struct store {
	int loc; // 상점의 위치
	int cnt; // 판매 가능 물병의 개수
};

vector<store> stores; // 상점의 정보 {
vector<store> history; // 물병을 판매한 이력
int N, M, K;

vector<store> minHis; // 최소 소모 체력인 경우의 이력 (답)
int minAcc; // 최소 소모 체력 (답)

// ind : stores[ind]가 이번에 발견한 상점의 위치
// water : 현재 소유한 물통 개수
// acc : 현재까지 소모한 체력
void dfs(int ind, int water, int acc) {
	// 마지막 도착지점에서 답 갱신
	if (stores[ind].loc == M) {
		if (acc < minAcc) {
			minAcc = acc; // 총 소모 체력을 최소값으로 갱신
			minHis = history; // 이에 대한 경로를 갱신
		}
		return;
	}

	// 1. 현재(ind) ~ 다음(ind+1) 까지의 소모 체력 계산
	int st = stores[ind].loc;
	int en = stores[ind + 1].loc;
	int nDist = en - st;

	// 2. 다음까지 갈 수 있는 물의 양인 경우를 골라서 다음 지점으로 가기
	for (int i = stores[ind].cnt; i >= 0; i--) {
		if (nDist > water + i) break;

		int nWater = water + i; // 해당 상점에서 i개의 물을 산다고 가정
		int tmp = 0; // ind ~ (ind+1) 까지 소모되는 체력
		for (int pos = 0; pos < nDist; pos++) {
			tmp += (nWater - pos);
		}

		history.push_back({ ind, i }); // ind번째 상점에서 i개의 물을 샀다고 저장
		dfs(ind + 1, water - nDist + i, acc + tmp); // 다음 상점으로 가서 탐색
		history.pop_back(); // 원복
	}
}

int main() {
	// reset
	minAcc = 21e8;

	// input
	cin >> N >> M >> K;

	stores.push_back({ 0, 0 });
	int loc, cnt;
	for (int i = 0; i < K; i++) {
		cin >> loc >> cnt;
		stores.push_back({ loc, cnt });
	}
	stores.push_back({ M, 0 });

	// solve
	dfs(0, N, 0);

	// output
	for (int i = 1; i < minHis.size(); i++) {
		cout << stores[minHis[i].loc].loc << " " << minHis[i].cnt << '\n';
	}

	return 0;
}