#include <iostream>

const int N = 100;
char s[N];

int main(void) {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%s", &s);
        int cur = 0;
        int tot = 0;
        for(int i = 0; s[i]; i++) {
            if(s[i] == 'O') tot += ++cur;
            else cur = 0;
        }
        printf("%d\n", tot);
    }
    return 0;
}