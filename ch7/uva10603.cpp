#define LOCAL
#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

const int maxn = 205;
int vis[maxn][maxn], ans[maxn], cap[3];

struct Node {
    int jug[3], dist;
    bool operator<(const Node& rhs) const {
        return this->dist > rhs.dist;
    }
};

Node trans(Node& node, int from, int to) {
    if(!node.jug[from] || node.jug[to] == cap[to]) return node;
    int tmp = min(node.jug[from], cap[to] - node.jug[to]);
    Node ans = node;
    ans.jug[from] -= tmp, ans.jug[to] += tmp;
    ans.dist += tmp;
    return ans;
}

void solve(int a, int b, int c, int d) {
    memset(vis, 0, sizeof(vis));
    memset(ans, -1, sizeof(ans));
    cap[0] = a, cap[1] = b, cap[2] = c;
    priority_queue<Node> q;
    ans[c] = 0, ans[0] = 0;
    vis[0][0] = 1;
    q.push({0, 0, c, 0});
    while(q.size()) {
        auto t = q.top(); q.pop();
        for(int i = 0; i < 3; i++) {
            int td = t.jug[i];
            if(ans[td] < 0 || t.dist < ans[td]) 
                ans[td] = t.dist;
        }
        if(ans[d] >= 0) break;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(i == j) continue;
                Node next = trans(t, i, j);
                int na = next.jug[0], nb = next.jug[1];
                if(vis[na][nb]) continue;
                vis[na][nb] = 1;
                // dont update answer here
                // cause it may cause an early termination of the loop 
                // with incorrect answer
                // for example, d liter water appear with a dist bigger than the answer
                q.push(next);
            }
        }
    }
    while(d >= 0) {
        if(ans[d] >= 0) {
            printf("%d %d\n", ans[d], d);
            return;
        }
        d--;
    }
}

int main(void) {
    #ifdef LOCAL
        freopen("uva10603.in", "r", stdin);
        freopen("uva10603.out", "w", stdout);
    #endif
    int T, a, b, c, d;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        solve(a, b, c, d);
    }
    return 0;
}

// 计算出倒出d liter water的最小转移量
// 若无法导出d liter water，计算出最接近d liter水量时的最小倒水量
// 3 jugs represent a state together.
// 1 state -> many states, record the poured amount to each state
// every time the state transists, check if the gereated liter is new or poured amount is less
// 
// because the total amount is certain, so we can use 2 dimension to represent 3 jugs, that is the state
// use array to record liter -> minimum poured water