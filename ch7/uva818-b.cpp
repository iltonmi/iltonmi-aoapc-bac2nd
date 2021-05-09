#define LOCAL
#include <iostream>
#include <unordered_set>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 16;
unordered_set<int> g[maxn];
int comp_cnt, n;
int vis[maxn];

// whether the x bit from right is switched on
bool on(int s, int x) {
    return s & (1 << x);
}

// whether the component has cycle
bool dfs_fail(int x, int pre, int s) {
    if(vis[x]) return true;
    vis[x] = true;
    int t = pre == -1 ? 0 : 1;
    for(auto i : g[x]) {
        if(!on(s,i) && i != pre) {
            if(++t > 2 || dfs_fail(i, x, s)) return true;
        }
    }
    return false;
}

// count the piece be opened
int cal(int s) {
    int ans = 0;
    for(int i = 0; i < n; i++)
        if(on(s, i)) ans++;
    return ans;
}

// check whether each component has cycle and count components
bool valid(int s) {
    fill_n(vis, maxn, 0);
    int comp_cnt = 0;
    int t = cal(s);
    for(int i = 0; i < n; i++) {
        if(!vis[i] && !on(s, i)) {
            if(t < (++comp_cnt - 1) || dfs_fail(i, -1, s)) return false;
        }
    }
    return true;
}

// enum the open status of pieces
// check whether it will has cycle or some pieces has more than 2 neighbours
// and confirm the opened pieces amount should be sufficient to connect all components
// which means opened pieces >= componets - 1
int solve() {
    int ans = maxn;
    for(int s = 0; s < (1 << n); s++) {
        if(valid(s)) ans = min(cal(s), ans);
    }
    return ans;
}

int main(void) {
    #ifdef LOCAL
        freopen("uva818.out", "w", stdout);
    #endif
    int cnt = 0;
    while(scanf("%d", &n) , n) {
        for(int i = 0; i < maxn; i++) g[i].clear();
        int a, b;
        while(scanf("%d%d", &a, &b), a != -1)
            g[a-1].insert(b-1), g[b-1].insert(a-1);
        printf("Set %d: Minimum links to open is %d\n", ++cnt, solve());
    }
    return 0;
}