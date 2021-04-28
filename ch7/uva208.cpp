#define LOCAL
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 25;
int dest, path[maxn];
bool used[maxn];
int tot;
vector<int> map[maxn];

bool check_connectivity() {
    queue<int> q;
    memset(used, false, sizeof(used));
    q.push(1);
    used[1] = true;
    while(q.size()) {
        auto t = q.front(); q.pop();
        if(t == dest) return true;
        for(auto next : map[t]) 
            if(!used[next]) {
                used[next] = true;
                q.push(next);
            }
    }
    return false;
}

void dfs(int x, int cur) {
    if(used[x]) return;
    if(x == dest) {
        tot++;
        path[cur] = x;
        for(int i = 0; i <= cur; i++)
            printf(i > 0 ? " %d" : "%d", path[i]);
        puts("");
        return;
    }
    used[x] = true;
    path[cur] = x;
    for(auto next : map[x]) dfs(next, cur + 1);
    used[x] = false;
}

void enum_routes() {
    memset(used, false, sizeof(used));
    dfs(1, 0);
}

int main(void) {
    #ifdef LOCAL
        freopen("uva208.in", "r", stdin);
        freopen("uva208.out", "w", stdout);
    #endif
    int cnt = 0;
    while(scanf("%d", &dest) != EOF) {
        int a, b;
        for(int i = 0; i < maxn; i++) map[i].clear();
        while(scanf("%d%d", &a, &b), a) 
            map[a].push_back(b), map[b].push_back(a);
        for(int i = 0; i < maxn; i++) sort(map[i].begin(), map[i].end());
        printf("CASE %d:\n", ++cnt);
        tot = 0;
        if(check_connectivity()) enum_routes();
        printf("There are %d routes from the firestation to streetcorner %d.\n", tot, dest);
    }
    return 0;
}