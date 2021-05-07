#define LOCAL
#include <iostream>

using namespace std;

const int m = 7, n = 8;
// used for bone, vis for grid
bool used[m][n], vis[m][n];
// g for input grid, ex for existence of bone
int g[m][n], ex[m][n], ans[m][n];
int anscnt, rest = 28;
// 只往右或往下搜索，减少重复
int dx[] = {1,0}, dy[] = {0,1};

bool read_input() {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            int t;
            if(scanf("%d", &t) == EOF) return false;
            g[i][j] = t;
        }
    }
    return true;
}

// 因为只往上或往下搜索，所以已处理部分位于左上角
// 因此，查找右边界或下边界未访问的部分
pair<int, int> next() {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(!vis[i][j]) return {i, j};
        }
    }
    return {-1, -1};
}

bool invalid(int a, int b) {
    return a < 0 || a >= m || b < 0 || b >= n || vis[a][b];
}

void bfs(int sx, int sy) {
    if(rest == 0) {
        anscnt++;
        puts("\n");
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                printf("%4d", ans[i][j]);
            }
            printf("\n");
        }
        return;
    }
    if(invalid(sx, sy)) return;
    vis[sx][sy] = true;
    for(int i = 0; i < 2; i++) {
        int a = sx + dx[i], b = sy + dy[i];
        if(invalid(a,b)) continue;
        int j = g[sx][sy], k = g[a][b];
        if(!ex[j][k] || used[j][k]) continue;
        used[j][k] = used[k][j] = vis[a][b] = true;
        ans[sx][sy] = ans[a][b] = ex[j][k];
        rest--;
        auto p = next();
        bfs(p.first, p.second);
        rest++;
        used[j][k] = used[k][j] = vis[a][b] = false;
    }
    vis[sx][sy] = false;
}

int main(void) {
    #ifdef LOCAL
        freopen("uva211.in", "r", stdin);
        freopen("uva211.out", "w", stdout);
    #endif
    int tcnt = 0;
    for(int i = 0; i <= 6; i++)
        for(int j = i; j <= 6; j++) ex[i][j] = ex[j][i] = ++tcnt;
    int cnt = 0;
    while(read_input()) {
        if(cnt++ > 0) puts("\n\n\n\n");
        printf("Layout #%d:\n\n\n", cnt);
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                printf("%4d", g[i][j]);
            }
            printf("\n");
        }
        printf("\nMaps resulting from layout #%d are:\n", cnt);
        anscnt = 0;
        bfs(0, 0);
        printf("\n\nThere are %d solution(s) for layout #%d.\n", anscnt, cnt);
    }
    return 0;
}

// 暴力搜索
// 每一步搜索2个位置，然后选择下一个位置
// 当所有格子都被搜索完成，那么生成了一个编号

// 如何判断2个位置有效呢？
// 1. 不越界
// 2. 存在符合条件的未被使用的骨牌

// 1. bool数组标记位置使用状态
// 2. 表示骨牌的使用状态, 二维数组
//      判断骨牌是否存在，二维数组。。。 