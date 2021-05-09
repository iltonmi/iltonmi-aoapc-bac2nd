#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 20;
bool used[maxn * 10 + 10][5];
char rev[5][maxn + 1];
int tab[maxn]; // 根据陈锋老师代码，一个时间最多只有一个单元被使用...
vector<int> offset;
int n, f[11];

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

void dfs(int x, int s, int mx) {
    if(x == mx) {
        f[mx] = min(s, f[mx]);
        return;
    }
    for(auto os : offset) {
        int time = s + os;
        if(time + f[mx-x] >= f[mx]) return;
        if(!check(time)) continue;
        mark(time, true);
        dfs(x+1,time, mx);
        mark(time, false);
    }
}

int solve() {
    mark(0, true);
    offset.clear();
    for(int i = 0; i <= n; i++)
        if(check(i)) offset.push_back(i);
    
    memset(f, 0, sizeof f);
    for(int i = 1; i <= 10; i++) {
        f[i] = i * n;
        dfs(1, 0, i);
    }
    mark(0, false);
    return f[10] + n;
}

int main(void) {
    while(read_input()) {
        printf("%d\n", solve());
    }
    return 0;
}

// 看了陈锋老师的解答。。。究极版本，f[i], 一维task, 稀疏步长
// 20ms...