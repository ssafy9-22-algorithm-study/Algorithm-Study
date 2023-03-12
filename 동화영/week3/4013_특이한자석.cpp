#include <iostream>
#include <cstring>
using namespace std;

// 1,3번은 순방향
// 2,4번은 역방향
int map[5][8];
int ptr[5];
int point[5] = { 0, 1, 2, 4, 8 };

void move(int num, int dir) {
	int issame[3] = { 0, }; // 각 자석 사이의 극성이 같은가?
	for (int i = 0; i < 3; i++) {
		int left = map[i + 1][(ptr[i + 1] + 2) % 8]; // i번 위치에서 왼쪽
		int right = map[i + 2][(ptr[i + 2] + 6) % 8]; // i번 위치에서 오른쪽

		if (left == right) issame[i] = 1; // 극성이 같다면 표기
	}

	// 시작 자석 회전시키기
	ptr[num] = (ptr[num] - dir + 8) % 8;

	// 오른쪽 자석들 회전시키기
	for (int i = num + 1; i <= 4; i++) {
		if (issame[i - 2] == 1) break; // 같은 자성이라면 더이상 회전 x

		// 다른 자성
		// 시작 자석의 옆옆이면 같은 방향으로 회전
		// 시작 자석의 옆이면 같은 방향으로 회전
		int tmp = 0;
		if (num % 2 == i % 2) tmp = dir;
		else tmp = -dir;

		ptr[i] = (ptr[i] - tmp + 8) % 8;
	}

	// 왼쪽 자석들 회전시키기
	for (int i = num - 1; i >= 1; i--) {
		if (issame[i - 1] == 1) break; // 같은 자성이라면 더이상 회전 x

		int tmp = 0;
		if (num % 2 == i % 2) tmp = dir;
		else tmp = -dir;

		ptr[i] = (ptr[i] - tmp + 8) % 8;
	}
}

int main() {
	int t;
	cin >> t;

	int k;
	for (int tc = 1; tc <= t; tc++) {
		// 초기화
		memset(ptr, 0, sizeof(ptr));

		// 입력
		cin >> k;

		for (int i = 1; i <= 4; i++) {
			for (int j = 0; j < 8; j++) {
				cin >> map[i][j];
			}
		}

		// 1. 1칸씩 k번 이동
		int num, dir;

		for (int i = 0; i < k; i++) {
			cin >> num >> dir;

			move(num, dir);
		}

		// 2. 최종 점수 합산
		int ans = 0;
		for (int i = 1; i <= 4; i++) {
			// 각 자석의 포인터에 있는 극성을 기준으로 점수 더하기
			// n극 - 0점, s극 - 1,2,4,8점
			ans += map[i][ptr[i]] == 0 ? 0 : point[i];
		}

		cout << "#" << tc << " " << ans << '\n';
	}

	return 0;
}
