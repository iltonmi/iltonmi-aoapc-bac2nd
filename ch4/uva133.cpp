#include <iostream>
#include <cstring>

using namespace std;

const int N = 30;
bool st[N];

int main(void) {
    int n, k, m;
    while(scanf("%d%d%d", &n, &k, &m) && n) {
        int rest = n;
        int a = 0, b = n + 1;
        memset(st, 0, sizeof st);
        st[a] = st[b] = true;
        while(rest) {
            for(int i = 0; i < k; i++) {
                while(a = a % n + 1, st[a]);
            }
            for(int i = 0; i < m; i++) {
                while(b = (b - 2 + n) % n + 1, st[b]);
            }
            if(rest != n) putchar(',');
            if(a == b) {
                rest--; printf("%3d", a);
                st[a] = true;
            } else {
                rest -= 2;
                printf("%3d%3d", a, b);
                st[a] = st[b] = true;
            }
        }
        puts("");
    }
    return 0;
}