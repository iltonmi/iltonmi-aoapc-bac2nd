#include <iostream>
#include <cstring>

using namespace std;

const int N = 32;
int buf[N][N], cnt;

void draw(string& s, int& p, int r, int c, int len) {
    char ch = s[p++];
    if(ch == 'p') {
        len /= 2;
        draw(s, p, r, c + len, len);
        draw(s, p, r, c, len);
        draw(s, p, r + len, c, len);
        draw(s, p, r + len, c + len, len);
    } else if(ch == 'f') {
        for(int i = r; i < r + len; i++)
            for(int j = c; j < c + len; j++)
                if(!buf[i][j]) buf[i][j] = 1, cnt++;
    }
}

// 来自紫书的思路：不构造树，直接模拟画画
int main(void) {
    int T; scanf("%d\n", &T);
    while(T--) {
        memset(buf, 0, sizeof(buf));
        cnt = 0;
        for(int i = 0; i < 2; i++) {
            string s;
            getline(cin, s);
            int p = 0;
            draw(s, p, 0, 0, N);
        } 
        printf("There are %d black pixels.\n", cnt);
    }
    return 0;
}