#include <iostream>

using namespace std;

const int N = 110;
int m, n;
char grid[N][N];
int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1}, dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};

int ans;

// 常量数组8连通
// void dfs(int sx, int sy) {
//     grid[sx][sy] = ' ';
//     for(int i = 0; i < 8; i++) {
//         int a = sx + dx[i], b = sy + dy[i];
//         if(a < 0 || a >= m || b < 0 || b >= n) continue;
//         if(grid[a][b] != '@') continue;
//         dfs(a, b);
//     }
// }

// 二重循环8连通
void dfs(int sx, int sy) {
    if(sx < 0 || sx >= m || sy < 0 || sy >= n) return;
    if(grid[sx][sy] != '@') return;
    grid[sx][sy] = ' ';
    for(int dr = -1; dr <= 1; dr++) 
        for(int dc = -1; dc <= 1; dc++) dfs(sx + dr, sy + dc);
}

int main(void) {
    while(scanf("%d%d\n", &m, &n) != EOF && m > 0) {
        for(int i = 0; i < m; i++)
            scanf("%s", grid[i]);
        // puts("");
        // for(int i = 0; i < m; i++)
        //     printf("%s\n", grid[i]);
        ans = 0;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                if(grid[i][j] == '@') ans++, dfs(i, j);
        printf("%d\n", ans);
    }
    return 0;
}