#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 20;
int used[maxn * 10 + 10][5];
char rev[5][maxn + 1];
vector<int> tab[maxn];
int f[11];
int n;

bool read_input() {
    if(scanf("%d\n", &n) == EOF || n == 0) return false;
    for(int i = 0; i < 5; i++)
        scanf("%s", &rev[i]);
    for(int j = 0; j < n; j++) tab[j].clear();
    for(int j = 0; j < n; j ++)
        for(int i = 0; i < 5; i++) {
            if(rev[i][j] == 'X') tab[j].push_back(i);
        }
    return true;
}

void mark(int time, int x) {
    for(int j = 0; j < n; j++) {
        for(auto i : tab[j]) used[time+j][i] = x;
    }
}

bool check(int time) {
    for(int j = 0; j < n; j++) {
        for(auto i : tab[j]) 
            if(used[time+j][i] != -1) return false;
    }
    return true;
}

int lastpos;
int minstep;

void dfs(int x, int s) {
    if(s >= lastpos) return;
    if(x == 10) {
        lastpos = s;
        return;
    }
    for(int time = s; time <= min(s + n, lastpos); time++) {
        if(time + f[9-x] >= lastpos) return;
        if(!check(time)) continue;
        f[x+1] = min(f[x+1], time);
        mark(time, x);
        dfs(x+1,time);
        mark(time, -1);
    }
}

int solve() {
    memset(used, -1, sizeof used);
    lastpos = 9 * n;
    mark(0, 0);
    for(int i = 0; i < n; i++)
        if(check(i)) {minstep = i; break;}
    for(int i = 1; i <= 10; i++) f[i] = i * minstep;
    dfs(1,0);
    return lastpos + n;
}

int main(void) {
    while(read_input()) {
        printf("%d\n", solve());
    }
    return 0;
}

// 用vector拯救f(i)估值1750ms...
// 也试过搜索前直接用dfs计算出f[1..10]，但因为f(i)只能小于等于i*f(1)，所以结果反而更差