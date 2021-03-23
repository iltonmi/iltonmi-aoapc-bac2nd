#define LOCAL
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    #ifdef LOCAL
        freopen("uva10976.in", "r", stdin);
        freopen("uva10976.out", "w", stdout);
    #endif
    int k;
    vector<pair<int, int>> v;
    while(scanf("%d", &k) != EOF) {
        for(int y = k + 1; y > 2 * k; y++) {
            int x = k * y / (y - k);
            if((k * y) % (y - k)) continue;
            v.push_back({x, y});
        }
        printf("%d\n", v.size());
        for(auto & p : v) printf("1/%d = 1/%d + 1/%d\n", k, p.first, p.second);
        v.clear();
    }
    return 0;
}

// 这题需要思考枚举的边界条件
// 枚举x，根据x计算出y，x >= y
// 那么x的枚举范围是什么呢？因为x, y > 0，所以，k < x
// 又因为x >= y, 1/x <= 1/y, 1/k = 1/x + 1/y <= 2/y, y <= 2k
// xy = kx + ky, x = ky/(y - k)