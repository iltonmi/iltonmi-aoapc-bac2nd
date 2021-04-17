#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

int main(void) {
    int rnd = 0;
    int T;
    scanf("%d", &T);
    // const int INT_MAX = (1 << 31) - 1;
    while(T--) {
        int n, s1, v1, s2, v2;
        scanf("%d%d%d%d%d", &n, &s1, &v1, &s2, &v2);
        if(s1 > s2) swap(s1, s2), swap(v1, v2);
        // 用long long只是为了使得max函数的参数类型相同
        ll ans = 0;
        // 说明较大的s2比n小太多
        // 而且，s1 < s2 < 65536, s1 * s2 <= n
        if(n / s2 >= (1 << 16)) {
            // 用long long为了防止溢出
            for(ll i = 0; i <= s1; i++)
                ans = max(ans, v2 * i + (n - s2 * i) / s1 * v1);
            for(ll i = 0; i <= s2; i++)
                ans = max(ans, v1 * i + (n - s1 * i) / s2 * v2);
        } else {
            for(ll i = 0; s2 * i <= n; i++)
                ans = max(ans, v2 * i + (n - s2 * i) / s1 * v1);
        }
        printf("Case #%d: %lld\n", ++rnd, ans);
    }
    return 0;
}