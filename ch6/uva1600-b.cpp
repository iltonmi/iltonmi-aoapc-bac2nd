#define LOCAL

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int N = 25;
int g[N][N], dist[N][N][N];
int m, n, k;
int dx[] = {0, 0, -1, 1}, dy[] = {-1, 1, 0, 0};

struct Node {
    int r, c, k;
};

bool is_unvalid(int a, int b) {
    return a < 1 || a > m || b < 1 || b > n;
}

int solve() {
    memset(dist, -1, sizeof(dist));
    queue<Node> q;
    dist[1][1][0] = 0;
    q.push({1, 1, 0});
    while(q.size()) {
        auto t = q.front(); q.pop();
        if(t.r == m && t.c == n) return dist[t.r][t.c][0];
        for(int i = 0; i < 4; i++) {
            int a = t.r + dx[i], b = t.c + dy[i];
            if(is_unvalid(a, b)) continue;
            int nk = g[a][b] ? t.k + 1 : 0;
            if(dist[a][b][nk] < 0 && nk <= k) {
                dist[a][b][nk] = dist[t.r][t.c][t.k] + 1;
                q.push({a, b, nk});
            }
        }
    }
    return -1;
}

int main(void) {
    #ifdef LOCAL
    freopen("uva1600.in", "r", stdin);
    freopen("uva1600.out", "w", stdout);
    #endif
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &m, &n, &k);
        for(int i = 1; i <= m; i++)
            for(int j = 1; j <= n; j++)
                scanf("%d", &g[i][j]);
        printf("%d\n", solve());
    }
    return 0;
}