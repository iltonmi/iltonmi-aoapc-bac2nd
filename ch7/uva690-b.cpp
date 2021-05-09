#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 20;
int used[maxn * 10 + 10][5];
char rev[5][maxn + 1];
vector<int> tab[maxn];
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
    for(int time = s; time <= s + n; time++) {
        // 剩下k个任务，由于第一个任务步长是0，所以只需要k-1个步
        if(time + (10-x-1) * minstep >= lastpos) return;
        if(!check(time)) continue;
        mark(time, x);
        dfs(x+1,time);
        mark(time, -1);
    }
}

int solve() {
    memset(used, -1, sizeof used);
    lastpos = 9 * n;
    mark(0, 0);
    for(int i = 0; i <= n; i++)
        if(check(i)) {minstep = i; break;}
    dfs(1,0);
    return lastpos + n;
}

int main(void) {
    while(read_input()) {
        printf("%d\n", solve());
    }
    return 0;
}

// vector版本，310ms... 将min(s+n, lastpos)改成s+n，280ms更快...
// 1. 如果f(i)使用递归算出来的，那么f(i)是会比i*minstep小的，
// 这样反而容易导致 time + f(i) >= lastpos的条件没那么容易触发，反而更慢。。。
// 2. 但是一味的将f(i)变大也是没有根据的，会导致错误的结果