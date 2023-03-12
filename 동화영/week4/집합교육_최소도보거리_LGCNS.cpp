#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
	int y;
	int x;
};

Node subway[4]; // 지하철의 4개의 꼭지점 (좌하, 우하, 우상, 좌상)

int findY(Node st, int xInd) {
	int retY = 0;
	if (st.y > subway[3].y) { // 지하철보다 위쪽 밖
		retY = abs(st.y - subway[3].y);
	}
	else if (st.y < subway[0].y) { // 지하철보다 아래쪽 밖
		retY = abs(st.y - subway[0].y);
	}
	else { // 지하철 y축 사이
		retY = 0;
	}
	return retY;
}

// st: 코코 혹은 목적지
// st와 지하철과의 거리 구하기
int findDist(Node st) {
	int ret = 0;

	if (st.x < subway[3].x) { // 지하철보다 왼쪽 밖
		ret = abs(st.x - subway[3].x) + findY(st, 0);
		
	}
	else if (st.x > subway[2].x) { // 지하철보다 오른쪽 밖
		ret = abs(st.x - subway[2].x) + findY(st, 2);
	}
	else { // 지하철 x축 사이
		ret = 0 + findY(st, 1);

		// 지하철 노선도 내에 있는 경우 (4방향과의 거리 중 최소)
		if (ret == 0) {
			int tmp1 = min(abs(st.x - subway[3].x), abs(st.x - subway[2].x));
			int tmp2 = min(abs(st.y - subway[3].y), abs(st.y - subway[0].y));
			ret = min(tmp1, tmp2);
		}
	}

	return ret;
}

int main() {
	Node coco; // 코코의 초기 위치
	Node dest; // 목적지의 위치

	cin >> coco.x >> coco.y
		>> dest.x >> dest.y;

	for (int i = 0; i < 4; i++) {
		cin >> subway[i].x >> subway[i].y;
	}

	// 1. 지하철 이용 없이 도보로 이동시 거리 -> 초기값
	int dist = abs(coco.y - dest.y) + abs(coco.x - dest.x);

	// 2. 지하철 이용하여 걸리는 도보 거리
	int cocoD = findDist(coco);
	int destD = findDist(dest);
	dist = min(dist, cocoD + destD); // 1과 2 중 작은 값

	cout << dist << '\n';

	return 0;
}