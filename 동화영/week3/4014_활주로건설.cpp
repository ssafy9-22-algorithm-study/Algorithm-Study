#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;
#define MAX_N 20

vector<int> myV; // 탐색할 라인

int MAP[MAX_N][MAX_N]; // 절벽지대

int N; // 절벽지대의 사이즈
int X; // 경사로의 너비

// 해당 행or열에 활주로 건설이 가능한지 탐색
// true: 가능, false: 불가
bool findRoad() {
	bool ret = true;

	int cnt = 0; // 현재 세고 있는 높이가 연속으로 몇 개 있는가?

	int height = myV[0];
	cnt++;

	for (int i = 1; i < N; i++) {
		if (myV[i] == height) { // 이전 칸과 높이 동일
			cnt++;
		}
		else if (myV[i] > height) {  // 이전 칸보다 높다 -> 경사로를 세우고 다음을 탐색한다
			if (myV[i] - height > 1) { // 높이 차이가 1 초과시 건설 불가
				return false;
			}

			if (cnt < X) { // 이전의 높이가 연속 X개 미만이었다면 건설 불가
				return false;
			}

			// 설치 가능하다면
			// 현재 높이부터 다시 탐색
			height = myV[i];
			cnt = 1;
		}
		else { // 이전 칸보다 낮다 -> 다음 X칸을 탐색하여 경사로 설치 판단
			if (height - myV[i] > 1) { // 높이 차이가 1 초과시 건설 불가
				return false;
			}

			// 현재 지점부터 경사로 설치 가능한가?
			for (int j = i + 1; j < i + X; j++) { // 동일한 높이를 X개 찾아야 설치 가능
				if (j >= N) return false; // X개를 찾기 이전에 맵이 끝났다면 건설 불가

				if (myV[j] != myV[i]) { // 높이가 상이하다면 건설 불가
					return false;
				}
			}

			// 설치 가능하다면
			// 현재 높이부터 다시 탐색
			// 단, i부터 X칸만큼은 경사로를 설치했기 때문에 더이상의 경사로 추가 설치 불가
			height = myV[i];
			cnt = 0;
			i += (X - 1);
		}
	}

	return ret;
}

int main() {
	freopen("input4014.txt", "r", stdin);

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		// input
		cin >> N >> X;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> MAP[i][j];
			}
		}

		// solve
		int ans = 0; // 가능한 경우의 수
		for (int i = 0; i < N; i++) {
			// j번째 행 탐색
			myV.clear();
			for (int j = 0; j < N; j++) {
				myV.push_back(MAP[i][j]);
			}
			if (findRoad()) ans++; // 활주로 건설 가능시 카운팅

			// j번째 열 탐색
			myV.clear();
			for (int j = 0; j < N; j++) {
				myV.push_back(MAP[j][i]);
			}
			if (findRoad()) ans++; // 활주로 건설 가능시 카운팅
		}

		// output
		cout << "#" << tc << " " << ans << '\n';
	}

	return 0;
}

/*
2
6 2
3 3 3 2 1 1
3 3 3 2 2 1
3 3 3 3 3 2
2 2 3 2 2 2
2 2 3 2 2 2
2 2 2 2 2 2
6 4
3 2 2 2 1 2
3 2 2 2 1 2
3 3 3 3 2 2
3 3 3 3 2 2
3 2 2 2 2 2
3 2 2 2 2 2
*/

/*
1 
20 3 
3 3 3 2 2 2 2 3 3 3 4 4 4 4 4 4 5 5 5 5 
3 3 3 2 2 2 2 3 3 3 4 4 4 4 4 4 5 5 5 5 
5 3 3 2 2 2 2 2 3 3 4 4 4 4 5 5 5 5 5 5 
4 3 3 1 1 1 1 1 2 3 4 4 4 5 5 5 5 5 5 5 
4 2 2 1 1 1 1 1 2 3 4 5 5 5 5 5 5 5 5 5 
4 3 3 2 2 2 2 1 2 3 4 5 5 5 5 5 5 5 5 5 
4 4 4 4 4 3 3 2 3 4 5 5 5 5 5 5 5 5 5 5 
4 3 3 3 3 3 3 3 4 4 4 5 5 5 5 5 5 4 4 4 
4 3 3 3 3 3 3 3 4 4 4 5 5 5 5 5 5 4 4 4 
4 3 3 3 3 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 
3 3 3 3 3 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 
3 3 3 3 3 4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 
3 3 3 3 4 4 4 4 5 5 5 5 5 5 5 5 5 5 5 5 
4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 4 4 4 
4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 4 4 4 
5 5 5 5 5 5 5 5 5 5 5 5 4 4 4 4 4 4 4 4 
5 5 5 5 5 5 5 5 5 5 5 5 3 3 3 3 4 4 4 4 
5 5 5 5 5 5 5 5 5 5 5 5 3 3 2 2 3 3 4 4 
5 5 5 5 5 5 5 5 5 5 5 5 3 3 2 2 3 3 4 4 
5 5 5 5 5 5 5 5 4 4 4 4 3 3 3 3 4 4 4 4 
*/