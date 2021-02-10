#include <iostream>
#include <cstring>

using namespace std;

const int N = 100010;
char a[N];
int ne[N], tt, cur, idx = 1;
char str[N];

// 太奇怪了，将ne[0]设置为-1，会比设置为0快10ms...
int main(void) {
    while(scanf("%s", str) != EOF) {
        int len = strlen(str);
        ne[0] = -1;
        cur = tt = 0, idx = 1;
        for(int i = 0; i < len; i++) {
            char ch = str[i];
            if(ch == '[') cur = 0;
            else if(ch == ']') cur = tt;
            else {
                a[idx] = ch, ne[idx] = ne[cur], ne[cur] = idx;
                if(cur == tt) tt = idx;
                cur = idx, idx++;
            }
        }
        for(int i = ne[0]; i != -1; i = ne[i])
            putchar(a[i]);
        puts("");
    }
    return 0;
}