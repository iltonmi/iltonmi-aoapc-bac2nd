#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 20;
bool used[maxn * 10 + 10][5];
char rev[5][maxn + 1];
int tab[maxn]; // 根据陈锋老师代码，一个时间最多只有一个单元被使用...
vector<int> offset;
int n;

bool read_input() {
    if(scanf("%d\n", &n) == EOF || n == 0) return false;
    for(int i = 0; i < 5; i++)
        scanf("%s", &rev[i]);
    memset(tab, -1, sizeof tab);
    for(int j = 0; j < n; j ++)
        for(int i = 0; i < 5; i++) {
            if(rev[i][j] == 'X') tab[j] = i;
        }
    return true;
}

void mark(int time, bool val) {
    for(int j = 0; j < n; j++) {
        if(tab[j] != -1) used[time+j][tab[j]] = val;
    }
}

bool check(int time) {
    for(int j = 0; j < n; j++) {
        if(tab[j] != -1 && used[time+j][tab[j]]) return false;
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
    for(auto os : offset) {
        int time = s + os;
        if(time + (9-x) * minstep >= lastpos) return;
        if(!check(time)) continue;
        mark(time, true);
        dfs(x+1,time);
        mark(time, false);
    }
}

int solve() {
    lastpos = 9 * n;
    mark(0, true);
    offset.clear();
    for(int i = 0; i <= n; i++)
        if(check(i)) offset.push_back(i);
    minstep = offset[0];
    dfs(1,0);
    mark(0, false);
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