#include <iostream>
#include <cstring>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

// idea from Rujia Liu:
// 給每个连通块唯一编号，那么背景白色的编号必为1
// 对所有黑色连通分量的4连通邻居做检查，用集合记录内部白色连通分量的编号
// 白色连通分量的个数就是集合大小
// 思路分析：
// 核心思路都是一样的：区分背景白色和文字内部白色
// 1. 将每个文字单独复制到空白的背景上，再单独进行白色连通分量的统计
// 这种思路，为了避免和其他文字的内部白色分量混淆，将文字单独复制到空白图，
// 然后，空洞数量 = 白色分量数量 - 1，是为了和背景白色做区分
// 2. Rujia Liu的思路，是通过编号来直接区分的
// 编号为1的永远是白色背景，最后再统计每个黑色分量的编号非1的白色分量邻居
// 因为不同的文字不会直接连接，所以这样内部空洞就可以和背景白色、其他文字内部的白色区分开
// 总结：如果需要独立唯一区分，那么可以尝试编号！！！（和书里前面提到的：给字符串唯一ID是一个原理）

const int M = 210, N = 210;
int m, w, n, grid[M][N], tmp[M][N];
int dx[] = {0, 0, -1, 1}, dy[] = {1, -1, 0, 0};
char word[6] = {'W', 'A', 'K', 'J', 'S', 'D'};
char line[60];

bool is_invalid(int sx, int sy) {
    return sx < 0 || sx >= m || sy < 0 || sy >= n;
}

void mark(int sx, int sy, int id) {
    if(is_invalid(sx, sy)) return;
    if(tmp[sx][sy]) return;
    tmp[sx][sy] = id;
    for(int i = 0; i < 4; i++) {
        int a = sx + dx[i], b = sy + dy[i];
        if(grid[a][b] == grid[sx][sy]) mark(a, b, id);
    }
}

void read_pic() {
    memset(grid, 0, sizeof(grid));
    memset(tmp, 0, sizeof tmp);
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

unordered_map<int, set<int>> map;

void check_nbrs(int sx, int sy) {
    for(int k = 0; k < 4; k++) {
        int a = sx + dx[k], b = sy + dy[k];
        if(!is_invalid(a, b) && grid[a][b] != 1 && tmp[a][b] != 1)
            map[tmp[sx][sy]].insert(tmp[a][b]);
    }
}

int main(void) {
    int cnt = 0;
    while(scanf("%d%d\n", &m, &w) != EOF, m) {
        read_pic();
        int num = 0;
        set<int> idset;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                if(!tmp[i][j]) {
                    // mark the component with uni-id 
                    mark(i, j, ++num);
                    // record the black component id for subsequent neighbour checking
                    if(grid[i][j]) idset.insert(num);
                }

        // count neighbours expect the background white component 
        // always has id of 1
        map.clear();
        for(auto id : idset) map[id] = set<int>();
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                if(grid[i][j]) check_nbrs(i, j);
        
        vector<char> v;
        for(auto& t: map) v.push_back(word[t.second.size()]);
        sort(v.begin(), v.end());
        printf("Case %d: ", ++cnt);
        for(auto& ch : v) putchar(ch);
        puts("");
    }
    return 0;
}