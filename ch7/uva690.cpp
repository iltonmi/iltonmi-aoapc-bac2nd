#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 20;
int used[maxn * 10 + 10][5];
char rev[5][maxn + 1];
int n;

bool read_input() {
    if(scanf("%d\n", &n) == EOF || n == 0) return false;
    for(int i = 0; i < 5; i++)
        scanf("%s", &rev[i]);
    return true;
}

void mark(int time, int x) {
    for(int j = 0; j < n; j++) {
        for(int i = 0; i < 5; i++) {
            if(rev[i][j] == 'X') used[time+j][i] = x;
        }
    }
}

bool check(int time) {
    for(int j = 0; j < n; j++) {
        for(int i = 0; i < 5; i++) {
            if(rev[i][j] == 'X' && used[time+j][i] != -1) 
                return false;
        }
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
        // 即使time这一步能够成功，那么剩下10-x-1=9-x步
        if(time + (9-x) * minstep >= lastpos) return;
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
    // 预测最小步长
    for(int i = 0; i < n; i++)
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

// 810ms...
// 如果前面有2个任务已经放置了，那么第三个的位置必然大于等于2*minstep，
// 而不可能小于2*minstep，所以更新f(i)是纯粹增加开销。。。