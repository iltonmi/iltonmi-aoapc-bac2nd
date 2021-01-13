#include <iostream>

using namespace std;

char s[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";

int main() {
    int c;
    while(~(c = getchar())) {
        int i;
        for(i = 0; s[i] && s[i] != c; i++);
        if(s[i]) putchar(s[i - 1]);
        else putchar(c);
    }
    return 0;
}