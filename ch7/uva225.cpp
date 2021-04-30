#define LOCAL
#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

typedef pair<int, int> pii;

int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0};
int sum[25];
char dirs[] = {'n','e','s','w'};
char path[20];
unordered_map<int, vector<int>> xy;
unordered_map<int, vector<int>> yx;
auto phash = [](const pii& p){ return (size_t)(p.first * 31 + p.second); };
unordered_set<pii, decltype(phash)> set(10, phash);
int n, k;
int tot;

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
        if(set.count({a, b})) continue;
        if (abs(a) + abs(b) > sum[20] - sum[step]) continue;
        bool flag = true;
        if(i & 1) {
            int from = min(a, sx), to = max(a, sx);
            for(auto x : yx[sy]) {
                if(from <= x && x <= to) {
                    flag = false; break;
                }
            }
        } else {
            int from = min(b, sy), to = max(b, sy);
            for(auto y : xy[sx]) {
                if(from <= y && y <= to) {
                    flag = false; break;
                }
            }
        }
        if(flag) {
            // printf("%d,%d to %d,%d\n", sx, sy, a, b);
            path[step] = dirs[i];
            set.insert({a, b});
            dfs(a, b, i, step + 1);
            set.erase({a, b});
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
        xy.clear(), yx.clear();
        for(int i = 0; i < k; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            xy[a].push_back(b), yx[b].push_back(a);
        }
        
        tot = 0;
        // ensw
        int ta[] = {1, 0, 2, 3};
        for(auto i : ta) {
            path[1] = dirs[i];
            set.insert({dx[i], dy[i]});
            dfs(dx[i], dy[i], i, 2);
            set.erase({dx[i], dy[i]});
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
// 同一条路线，不能重复访问同一个路口又不说，醉了，uva的题目真的不止一次了。。。