#include <iostream>
#include <unordered_map>
using namespace std;

// idea by Rujia Lia
// 字符可以通过拉伸来变换：通过每个字符有多少个洞，来区分字符
// 1. 如何找到一个字符？遇到黑色的pixel
// 2. 如何判断一个字符被检查过了，标记
// 3. 如何判断一个字符有多少个洞？
//  3.1. 记录每个字符的每行的最左像素和最右像素
//  3.2. 遍历每行的字符，做flood fill
// 这个方案是错误的，因为，最左最右像素之间，可能存在外部的白色像素
// 因此，只能利用连通这个特点！！！
// 将一个字复制到新的空白图，然后统计白色的连通分量个数 - 1就是洞的数量
// 注意，还要给整个图片加上白色边框，否则会可能因为没有白色背景而导致白色连通分量统计出错
// 这个正确方案，会展示在uva1103-b.cpp

// 细化方案
// 1. 通过遍历原图，对于未被遍历的black pixel，做black pixel的flood fill
// flood fill过程中，标记所有4连通的black pixels为2（防止字符被重复识别），
// 记录每一行的最左和最右像素
// 2. 遍历字符的每一行，对于white pixel，做white pixel的flood fill，填充空洞
// 空洞计数加一，标记为2
typedef pair<int, int> pii;
const int M = 210, N = 210;
int m, w, n, grid[M][N];
int dx[] = {0, 0, -1, 1}, dy[] = {1, -1, 0, 0};
unordered_map<int, pii> map;
char arr[6];

void dfs(int sx, int sy, bool mark_y) {
    if(sx < 0 || sx >= m || sy < 0 || sy >= n) return;
    if(grid[sx][sy] != 1) return;
    grid[sx][sy] = 2;
    if(mark_y) {
        if(!map.count(sx)) map[sx] = {sy, sy};
        else {
            map[sx].first = min(map[sx].first, sy);
            map[sx].second = max(map[sx].second, sy);
        }
    }
    for(int i = 0; i < 4; i++) dfs(sx + dx[i], sy + dy[i], mark_y);
}

// void fill_hole(int sx, int sy) {
//     if(sx < 0 || sx >= m || sy < 0 || sy >= n) return;
//     if(grid[sx][sy] != 0) return;
//     grid[sx][sy] = 2;
//     // for(int dr = -1; dr <= 1; dr++)
//     //     for(int dc = -1; dc <= 1; dc++)
//     //         if(dr != 0 || dc != 0) fill_hole(sx + dr, sy + dc);
//     for(int i = 0; i < 4; i++) 
//         fill_hole(sx + dx[i], sy + dy[i]);
// }

int count_hole() {
    int ans = 0;
    for(auto& t : map) {
        for(int i = t.second.first; i <= t.second.second; i++)
            if(grid[t.first][i] == 0) ans++, dfs(t.first, i, false);
    }
    return ans;
}

int main(void) {
    char line[60];
    arr[1] = 'A', arr[3] = 'J', arr[5] = 'D', arr[4] = 'S', arr[0] = 'W', arr[2] = 'K';
    int cnt = 0;
    while(scanf("%d%d\n", &m, &w) != EOF, m) {
        n = 4 * w;
        for(int i = 0; i < m; i++) {
            scanf("%s", line);
            printf("%s\n", line);
            for(int j = 0; j < w; j++) {
                char ch = line[j];
                // printf(j < w - 1 ? "%c" : "%c\n", ch);
                int num;
                if(isdigit(ch)) num = ch - '0';
                else num = 10 + (ch - 'a');
                // printf(j < w - 1 ? "%d " : "%d\n", num);
                for(int k = 3; k >= 0; k--) {
                    grid[i][4 * j + k] = num & 1;
                    // printf(k > 0 ? "%d " : "%d\n", grid[i][8 * j + k]);
                    num >>= 1;
                }
            }
        }
        // for(int i = 0; i < m; i++)
        //     for(int j = 0; j < n; j++)
        //         printf(j < n - 1 ? "%d " : "%d\n", grid[i][j]);
        printf("Case %d: ", ++cnt);
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) dfs(i, j, true);
                int hole = count_hole();
                // 忘记排序了！！！
                printf("%c", arr[hole]);
                map.clear();
            }
        puts("");
    }
    return 0;
}