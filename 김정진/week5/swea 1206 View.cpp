#include <iostream>
#include <algorithm>

using namespace std;

int T = 10;
int n,ans;
int h[1005];

int main() {
    for(int tc{1}; tc <= T; tc++) {
        cin >> n;
        ans = 0;
        // 그냥 입력 받고
        for(int i{2}; i <= n+1; i++) {
            cin >> h[i];
        }
        // 입력 하는 김에 2칸 뒤에까지만 0으로 채워두고
        h[n+2] = 0;
        h[n+3] = 0;
        // 앞 뒤 2칸중 가장 큰 건물의 높이를 찾아서
        for(int i{2}; i <= n+1; i++) {
            int mh = max(max(h[i-1],h[i-2]),max(h[i+1],h[i+2]));
            // 현재 빌딩이 2칸 내의 빌딩들 보다 높다면 조망권을 더해준다.
            if(h[i] > mh)
                ans += h[i] - mh;
        }
        // 끝?
        cout << "#" << tc << " " << ans << endl;
    }
}
