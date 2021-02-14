#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int N = 110;
int n, m;
// 邻接表
int h[N], e[N * N], ne[N * N], idx;
int in[N];

void init() {
    memset(h, -1, sizeof(h));
    memset(in, 0, sizeof(in));
    idx = 0;
}

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void solve() {
    vector<int> v;
    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(!in[i]) v.push_back(i), q.push(i);
    
    while(q.size()) {
        auto t = q.front(); q.pop();
        for(int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if(--in[j] == 0) q.push(j), v.push_back(j);
        }
    }
    for(int i = 0; i < v.size(); i++)
        printf(i > 0 ? " %d" : "%d", v[i]);
    puts("");
}

int main(void) {
    while(scanf("%d%d", &n, &m), n) {
        init();
        for(int i = 0; i < m; i++) {
            int a, b; scanf("%d%d", &a, &b);
            if(!a) break;
            add(a, b);
            in[b]++;
        }
        solve();
    }
    return 0;
}