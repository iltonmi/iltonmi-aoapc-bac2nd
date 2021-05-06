#define LOCAL
#include <iostream>
#include <set>
#include <cmath>

using namespace std;

typedef pair<int, int> pii;

#define FOR_CELL(c, p) for(auto c = (p).begin(); c != (p).end(); ++c)
#define x first
#define y second

const int maxn = 11;
int ans[maxn][maxn][maxn];
int dx[] = {0,0,-1,1}, dy[] = {-1,1,0,0};
int n, w, h;
set<set<pii>> poly[maxn];

set<pii> normalize(const set<pii>& p) {
    int minX = 11, minY = 11;
    FOR_CELL(c, p) minX = min(minX, c->x), minY = min(minY, c->y);
    set<pii> ans;
    FOR_CELL(c, p) ans.insert({c->x - minX, c->y - minY});
    return ans;
}

set<pii> rotate(const set<pii>& p) {
    set<pii> ans;
    // inspired by from Rujia Liu
    // 经过笔算，确实有旋转效果。。。
    // 每次只需要交换横纵坐标位置，并且将纵坐标取相反数，就有逆时针旋转的后果
    // 而经我试验，每次交换横纵坐标位置，并且将横坐标取相反数，就有逆时针旋转的效果
    FOR_CELL(c, p) ans.insert({-c->y, c->x});
    return normalize(ans);
}

set<pii> flip(const set<pii>& p) {
    set<pii> ans;
    FOR_CELL(c, p) ans.insert({c->x, -c->y});
    return normalize(ans);
}

void check_unique(const set<pii>& p0, const pii cell) {
    auto p = p0;
    p.insert(cell);
    int n = p.size();
    p = normalize(p);
    for(int i = 0; i < 4; i++) {
        if(poly[n].count(p)) return;
        p = rotate(p);
    }
    p = flip(p);
    for(int i = 0; i < 4; i++) {
        if(poly[n].count(p)) return;
        p = rotate(p);
    }
    poly[n].insert(p);
}

void generate() {
    set<pii> s = {{0,0}};
    poly[1].insert(s);
    for(int i = 2; i <= 10; i++) {
        for(auto p = poly[i-1].begin(); p != poly[i-1].end(); p++) {
            FOR_CELL(c, *p) {
                for(int i = 0; i < 4; i++) {
                    pii cell = {c->x + dx[i], c->y + dy[i]};
                    if(!p->count(cell)) check_unique(*p, cell);
                }
            }
        }
    }
    for(int n = 1; n <= 10; n++) {
        for(int w = 1; w <= 10; w++) {
            for(int h = 1; h <= 10; h++) {
                int cnt = 0;
                for(auto p = poly[n].begin(); n <= w*h && p != poly[n].end(); p++) {
                    int maxX = 0, maxY = 0;
                    FOR_CELL(c, *p) maxX = max(maxX, c->x), maxY = max(maxY, c->y);
                    if(min(maxX, maxY) < min(h, w) && max(maxX, maxY) < max(h, w)) cnt++;
                }
                ans[n][w][h] = cnt;
            }
        }
    }
}

 int main(void) {
     #ifdef LOCAL
        freopen("uva1602.in", "r", stdin);
        freopen("uva1602.out", "w", stdout);
     #endif
     generate();
     while(scanf("%d%d%d",&n,&w,&h) == 3) 
        printf("%d\n", ans[n][w][h]);
     return 0;
 }

 // 又是学习如何建模的一天。。。这次的内容是俄罗斯方块
 // 用{x,y}表示一个方块，用方块的set代表一个状态
 // 枚举的时候，从n-1个方块组成的状态中，增加一个方块
 // 去重的时候
 // 1. 首先要规范化，将一个状态中的所有方块移动到第一象限; 查看已有的同数量方块中，有没有一样的
 // 2. 4个方向旋转，并规范化，查看有没有一样的
 // 3. 翻转，并4个方向旋转，查看有没有一样的
 // 4. 如果都没有，那么把他添加到n个方块组成的状态的集合中

 // 枚举n,w,h, 查看符合要求的状态数量, 提前存起来

 