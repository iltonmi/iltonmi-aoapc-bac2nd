#define LOCAL

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

typedef pair<int, int> pii;
#define x first
#define y second

const int N = 25;
int g[N][N], dist[N][N][N];
int m, n, k;
int dx[] = {0, 0, -1, 1}, dy[] = {-1, 1, 0, 0};

int ID(int r, int c) {
    return r * (n + 1) + c;
}

bool is_unvalid(int a, int b) {
    return a < 1 || a > m || b < 1 || b > n;
}

int solve() {
    memset(dist, -1, sizeof(dist));
    queue<pii> q;
    dist[1][1][0] = 0;
    q.push({0, ID(1, 1)});
    while(q.size()) {
        auto t = q.front(); q.pop();
        int tx = t.y / (n + 1), ty = t.y % (n + 1), tk = t.x;
        if(tx == m && ty == n) return dist[tx][ty][0];
        for(int i = 0; i < 4; i++) {
            int a = tx + dx[i], b = ty + dy[i];
            if(is_unvalid(a, b)) continue;
            int nk = g[a][b] ? tk + 1 : 0;
            if(dist[a][b][nk] < 0 && nk <= k) {
                dist[a][b][nk] = dist[tx][ty][tk] + 1;
                q.push({nk, ID(a, b)});
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

// 最短路问题，有障碍物
// 显然是BFS
// 特定条件，允许连续经过不超过k个障碍物
// 这是好事，因为可能会导致最短路更短
// 但是，要注意：如果连续经过了k个障碍物，下一个如果还是障碍物，就走不动了
// flash: 我想了一下，如果简单记录经过了多少个障碍物，可能有坑
// 解决方案1：记录每个位置是第几个障碍物，如果是0，那么0个；如果是1，那么就是前面连续的1个数+当前的1
// 这样会有什么问题呢？
// 正常的BFS，只需要记录某个位置是否被走过，已经被走过的位置，必不可能用更短的路程到达
// 允许穿越限定数量的障碍物的BFS，对于无障碍物的位置，上述结论依然成立；
// 试想，对于有障碍物的某个位置，可能由于再走一步会超越障碍物的数量，而停止
// 但如果有一条更远的路，到达同一个位置，但是连续通过障碍物更少，就可以通过这个位置，并且走出一条可行路线
// 一个点的最短距离，不仅由位置决定，还由是连续的第几个障碍物决定的
// 通过BFS，某个位置是第x个障碍物的情况，第一次出现时必然是最优情况
// 换言之，点的状态由位置和当前格子是第几个障碍物决定，(r, c, k)
