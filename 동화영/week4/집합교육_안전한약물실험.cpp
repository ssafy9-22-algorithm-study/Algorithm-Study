#include <iostream>
#include <string>
using namespace std;

string poison[20]; // 독극물 조합

int N, K;
int cnt; // 안전한 약물의 조합의 수 (답)

// 독극물이 포함되어 있는 조합인가를 판단
// true: 위험한 조합, false: 안전한 조합
bool isUnsafe(string medi) {
	bool isFound = true;

	// 입력받은 독극물을 모두 탐색
	for (int i = 0; i < K; i++) {
		isFound = true;

		// i번째 독극물
		string now = poison[i];
		int len = now.length();

		// 조사하려는 조합보다 길이가 작다면 무시 -> 해당 조합을 전부 포함 X
		if (len > medi.length()) continue;

		// 현재 찾은 조합에 독극물의 각 성분이 포함되어 있는지 확인
		for (int j = 0; j < len; j++) {
			if (medi.find(now[j]) == -1) { // j번째 약물이 없다면
				// medi는 i번째 독극물이 미포함 -> 아직까진 안전
				isFound = false;
				break;
			}
		}

		// 위에서 안전하다고 판단되지 않았다면
		// 즉, 독극물의 약물 성분이 전부 포함되었다면
		// 해당 조합은 위험하다
		if (isFound) return true;
	}

	// 위에서 return되지 않았다면
	// 모든 독극물이 포함되어 있지 않다
	// 즉, 해당 조합은 안전하다
	isFound = false;

	return isFound;
}

// lev: 현재까지 찾은 조합의 글자수
// medi: 현재까지 찾은 조합
void dfs(int lev, string medi) {
	if (lev > N) return; // N 범위 초과시 더이상 탐색 X

	// 구해온 조합이 안전하다면 cnt 카운팅
	if (lev > 0 && lev <= N) {
		if (!isUnsafe(medi)) {
			cnt++;
		}
	}

	// 중복 제거를 위해 직전에 찾은 약물보다 큰값부터 탐색하기
	int prev = lev == 0 ? 0 : (medi[lev - 1] - '0');
	for (int i = prev + 1; i <= N; i++) {
		dfs(lev + 1, medi + to_string(i));
	}
}

int main() {
	// input
	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		cin >> poison[i];
	}

	// dfs로 모든 가능한 조합 찾기
	dfs(0, "");

	// 안전한 약물의 개수 출력하기
	cout << cnt << "\n"; 

	return 0;
}

/* 2번 테케 - 31 개 중
1 2 3 4 5
12 13 14 15 23 24 25 34 35 45
123 124 125 134 135 145 234 345
1234 1345

235 245 1235 1245 2345 12345
*/