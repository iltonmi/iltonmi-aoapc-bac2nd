#include <iostream>

using namespace std;

int solve() {
    int w1, d1, w2, d2;
    scanf("%d%d%d%d", &w1, &d1, &w2, &d2);
    if(!w1) w1 = solve();
    if(!w2) w2 = solve();
    if(w1 == -1 || w2 == -1) return -1;
    if(w1 * d1 == w2 * d2) return w1 + w2;
    else return -1;
}

int main(void) {
    int n; scanf("%d", &n);
    while(n--) {
        if(solve() != -1) puts("YES");
        else puts("NO");
        if(n) puts("");
    }
    return 0;
}
