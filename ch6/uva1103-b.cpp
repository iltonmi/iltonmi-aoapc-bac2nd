#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int M = 210, N = 210;
int m, w, n, grid[M][N], tmp[M][N];
int dx[] = {0, 0, -1, 1}, dy[] = {1, -1, 0, 0};
char word[6] = {'W', 'A', 'K', 'J', 'S', 'D'};
char line[60];

void dfs(int sx, int sy) {
    if(sx < 0 || sx >= m || sy < 0 || sy >= n) return;
    if(grid[sx][sy] != 1) return;
    grid[sx][sy] = 0, tmp[sx][sy] = 1;
    for(int i = 0; i < 4; i++) dfs(sx + dx[i], sy + dy[i]);
}

void fill_hole(int sx, int sy) {
    if(sx < 0 || sx >= m || sy < 0 || sy >= n) return;
    if(tmp[sx][sy] != 0) return;
    tmp[sx][sy] = 1;
    for(int i = 0; i < 4; i++) fill_hole(sx + dx[i], sy + dy[i]);
}

int count_hole() {
    int ans = 0;
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            if(tmp[i][j] == 0) fill_hole(i, j), ans++;
    return ans - 1;
}

void read_pic() {
    memset(grid, 0, sizeof(grid));
    for(int i = 1; i <= m; i++) {
        scanf("%s", line);
        for(int j = 0; j < w; j++) {
            char ch = line[j];
            int num;
            if(isdigit(ch)) num = ch - '0';
            else num = 10 + (ch - 'a');
            for(int k = 3; k >= 0; k--) {
                grid[i][1 + 4 * j + k] = num & 1;
                num >>= 1;
            }
        }
    }
    n = 4 * w;
    m += 2, n += 2;
}

int main(void) {
    int cnt = 0;
    while(scanf("%d%d\n", &m, &w) != EOF, m) {
        read_pic();

        vector<char> v;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) {
                    memset(tmp, 0, sizeof tmp);
                    dfs(i, j);
                    int hole = count_hole();
                    v.push_back(word[hole]);
                }   
            }
        sort(v.begin(), v.end());
        printf("Case %d: ", ++cnt);
        for(auto& ch : v) putchar(ch);
        puts("");
    }
    return 0;
}