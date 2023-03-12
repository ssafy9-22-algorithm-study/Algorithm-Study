#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define max_n 12

int nums[max_n]; // 숫자들
int oper[4]; // + - * / 순서
int visited[4]; // 각 부호들의 사용 횟수
int n; // 입력받는 수자의 개수

int sum; // 현재의 결과값
int maxans, minans; // 최대, 최소값

void dfs(int lev) {
	if (lev == n - 1) { // n-1개의 부호를 모두 탐색시
		// 최대, 최소값 갱신
		if (sum > maxans) maxans = sum;
		if (sum < minans) minans = sum;

		return;
	}

	for (int i = 0; i < 4; i++) {
		// 이미 소진된 부호는 사용 불가
		if (visited[i] >= oper[i]) continue;

		int tmp = sum;

		sum = i == 0 ? sum + nums[lev + 1] : i == 1 ? sum - nums[lev + 1] : i == 2 ? sum * nums[lev + 1] : sum / nums[lev + 1]; // 금번의 부호 사용으로 인한 결과
		visited[i]++; // 부호 사용 표기
		
		dfs(lev + 1); // 다음 부호 찾으러 가기

		// 원복
		visited[i]--;
		sum = tmp;
	}

}

int main() {
	freopen("input4008.txt", "r", stdin);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		// 입력
		cin >> n;
		for (int i = 0; i < 4; i++) {
			cin >> oper[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		
		// 초기화
		maxans = -21e8;
		minans = 21e8;
		sum = nums[0]; // 첫번째 숫자로 초기화
		
		// 동작
		dfs(0);

		// 출력
		cout << "#" << tc << " " << (maxans - minans) << "\n";
	}

	return 0;
}

/*
2
5
2 1 0 1
3 5 3 7 9
6
4 1 0 0
1 2 3 4 5 6
*/