#define LOCAL
#include <iostream>
#include <set>
#include <vector>
#include <cmath>

using namespace std;

int n;
vector<int> v;

bool dfs(int d, int maxd, int tmax) {
    if(v[d] == n) {
        printf("%d\n", d);
        return true;
    }
    if(d == maxd) return false;
    // cout << "d:" << d << ':' << v[d] << endl;
    tmax = max(tmax, v[d]);
    // 接下来可能达到的最大值是，max ** (2 ** (maxd - d))
    if((tmax << (maxd - d)) < n) return false;

    for(int i = d; i >= 0; i--) {
        int t1 = v[d], t2 = v[i];
        int t = t1 + t2;
        if(v.size() - 1 < d + 1) v.push_back(t);
        else v[d+1] = t;
        if(dfs(d+1, maxd, tmax)) return true;
        t = t1 - t2;
        if(t > 0) {
            v[d+1] = t;
            if(dfs(d+1, maxd, tmax)) return true;
        }
    }
    return false;
}

int main(void) {
    #ifdef LOCAL
        freopen("uva1374.in", "r", stdin);
        freopen("uva1374.out", "w", stdout);
    #endif
    v.push_back(1);
    while(scanf("%d", &n) == 1, n) {
        for(int maxd = 0; ; maxd++)
            if(dfs(0, maxd, 1)) break;
    }
    return 0;
}

// IDA, 经典。。。