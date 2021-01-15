#include <iostream>
#include <cctype>
#include <cstring>

const int N = 100;
char s[N];

double solve() {
    double res = 0;
    for(int i = 0; s[i]; i++) {
        char c = s[i];
        double val;
        if(c == 'C') val = 12.01;
        else if(c == 'H') val = 1.008;
        else if(c == 'O') val = 16.00;
        else if(c == 'N') val = 14.01;
        int cnt = 0;
        while(s[i + 1] && isdigit(s[i + 1]))
            cnt = cnt * 10 + (s[++i] - '0');
        if(!cnt) cnt = 1;
        res += val * cnt;
    }
    return res;
}

int main(void) {
    int T;
    scanf("%d", &T);
    while(T--) {
        memset(s, 0, sizeof s);
        scanf("%s", &s);
        // printf("%s\n", s);
        printf("%.3lf\n", solve());
    }
    return 0;
}