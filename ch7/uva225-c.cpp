#define LOCAL
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0};
int sum[25], g[220][220];
char dirs[] = {'n','e','s','w'};
char path[20];
// 根据问题规模，走20次，其实最多也只是21 * 20 / 2 = 210
// 而要出发后往回走，意味着超过210 / 2 = 105就没有无法返回了
// 又因为可以往四个方向走，所以数组的大小是210，由于210是个边界值，为了保险起见，直接用220会更保险
// 所以完全可以用一个二维数组来保存点的状态，但要注意因为坐标可能是负数，所以还需要加一个偏移量
// 改造之后，只需要450ms，比我在洛谷看到的两个解答都更快
// 但是，直接用g来判断障碍点，会遍历很多没必要的点，又会比方式b慢100+ms
int n, k;
int tot;

bool invalid(int a, int b) {
    return abs(a) > 110 || abs(b) > 110;
}

void dfs(int sx, int sy, int dir, int step) {
    if(step == n + 1) {
        if(sx == 0 && sy == 0) {
            tot++;
            for(int i = 1; i <= n; i++) 
                printf(i < n ? "%c" : "%c\n", path[i]);
        }
        return;
    }
    for(int i = 0; i < 4; i++) {
        // 奇偶性
        if(((dir ^ i) & 1) == 0) continue;
        int a = sx + step * dx[i];
        int b = sy + step * dy[i];
        if(invalid(a, b)) continue;
        if(g[a+110][b+110]) continue;
        // 哈密顿距离，剪枝
        if (abs(a) + abs(b) > sum[20] - sum[step]) continue;
        bool flag = true;
        int fx = min(a, sx), tx = max(a, sx);
        int fy = min(b, sy), ty = max(b, sy);
        // 这种方式会更慢，因为会遍历很多没必要的点
        // 而方式b，直接判断障碍点是否在线段上，由于障碍点数量最多只有50个，比较少
        // 所以，这种方式会更慢
        for(int i = fx; i <= tx; i++)
            for(int j = fy; j <= ty; j++)
                if(g[i+110][j+110] == -1) {
                    flag = false; break;
                }
        
        if(flag) {
            // printf("%d,%d to %d,%d\n", sx, sy, a, b);
            path[step] = dirs[i];
            g[a+110][b+110] = 1;
            dfs(a, b, i, step + 1);
            g[a+110][b+110] = 0;
        }
    }
}

int main(void) {
    #ifdef LOCAL
        freopen("uva225.in", "r", stdin);
        freopen("uva225.out", "w", stdout);
    #endif
    for(int i=1;i<=20;i++) sum[i]=sum[i-1]+i;
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        memset(g, 0, sizeof(g));
        for(int i = 0; i < k; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            if(invalid(a, b)) continue;
            g[a+110][b+110] = -1;
        }
        
        tot = 0;
        // ensw
        int ta[] = {1, 0, 2, 3};
        for(auto i : ta) {
            path[1] = dirs[i];
            int a = dx[i], b = dy[i];
            if(g[a+110][b+110] == -1) continue;
            g[a+110][b+110] = 1;
            dfs(dx[i], dy[i], i, 2);
            g[a+110][b+110] = 0;
        }
        printf("Found %d golygon(s).\n\n", tot);
    }
    return 0;
}


// give n, k
// find a path from (0,0) to (0,0)
// 4 directions at 1st move, turn left or right at subsequent moves...
// blocked intersections cannot go across
// 
// time complexity: 4 * 2 ** (n-1) = 2 ** (n+1) = 2 ** (21) = 2e6
// 
// enum left or right:
// turn left or right: even <-> odd
// 0,1,2,3 -> n,e,s,w
// // 同一条路线，可以重复经过不能重复访问同一个路口又不说，醉了，uva的题目真的不止一次了。。。