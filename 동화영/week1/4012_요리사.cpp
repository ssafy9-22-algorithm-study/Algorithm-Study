#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX_N 16

int ingredient[MAX_N][MAX_N]; // 식재료 시너지
vector<int> ab;
int N; // 재료의 가짓수

int checkPoint() {
	// 8가지 00110101
	vector<int> a;
	vector<int> b;
	for (int i = 0; i < N; i++) {
		if (ab[i] == 0) a.push_back(i); // 1257
		else b.push_back(i); //3468
	}

	int aPoint = 0, bPoint = 0;
	for (int i = 0; i < N / 2; i++) {
		for (int j = 0; j < N / 2; j++) {
			aPoint += ingredient[a[i]][a[j]];
			bPoint += ingredient[b[i]][b[j]];
		}
	}

	return abs(aPoint - bPoint);
}

int main() {
	freopen("input4012.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		ab.clear();

		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> ingredient[i][j];
			}
		}
		// 8가지 식재료
		// 00001111
		// 00011110
		for (int i = 0; i < N / 2; i++) ab.push_back(0);
		for (int i = 0; i < N / 2; i++) ab.push_back(1);

		int ans = 21e8;

		// 모든 케이스에 대해 시너지 점수 계산
		do {
			int diff = checkPoint();
			if (diff < ans) ans = diff;
		} while (next_permutation(ab.begin(), ab.end()));

		cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}

/*
1
4
0 5 3 8
4 0 4 1
2 5 0 3
7 2 3 0
*/