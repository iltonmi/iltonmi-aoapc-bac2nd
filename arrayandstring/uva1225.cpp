#include <iostream>
#include <cstring>

const int N = 10;
int ans[N];

void solve(int n) {
    while(n) {
        ans[n % 10]++;
        n /= 10;
    }
}

int main () {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n; scanf("%d", &n);
        memset(ans, 0, sizeof ans);
        for(int i = 1; i <= n; i++) {
            solve(i);
        }
        for(int i = 0; i < N; i++)
            printf(i < N - 1 ? "%d " : "%d\n", ans[i]);
    }
    return 0;
}