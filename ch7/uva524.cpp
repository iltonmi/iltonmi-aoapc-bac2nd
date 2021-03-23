#define LOCAL
#include <iostream>

using namespace std;

int n, arr[20];
bool used[20];

// 判断素数可以优化
bool is_prime(int x) {
    if(x == 1) return false;
    for(int i = 2; i * i <= x; i++)
        if(x % i == 0) return false;
    return true;
}

void solve(int idx) {
    if(idx == n) {
        if(!is_prime(1 + arr[n - 1])) return;
        for(int i = 0; i < n; i++) 
            printf(i ? " %d" : "%d", arr[i]);
        puts("");
        return;
    }
    for(int i = 1; i <= n; i++) {
        if(!used[i] && is_prime(arr[idx - 1] + i)) {
            used[i] = true;
            arr[idx] = i;
            solve(idx + 1);
            used[i] = false;
        }
    }
}

int main(void) {
    #ifdef LOCAL
        freopen("uva524.in", "r", stdin);
        freopen("uva524.out", "w", stdout);
    #endif
    int cnt = 0;
    arr[0] = 1;
    while(~scanf("%d", &n)) {
        if(cnt) puts("");
        used[1] = true;
        printf("Case %d:\n", ++cnt);
        solve(1);
    }
    return 0;
}

// DFS