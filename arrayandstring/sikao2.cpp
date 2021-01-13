#include <cstdio>
#include <cstring>
#define maxn 10000000 + 10

char s[maxn];

int main() {
    scanf("%s", s);
    int tot = 0;
    for(int i = 0; i < strlen(s); i++)
        if(s[i] == '1') tot++;
    printf("%d\n", tot);
    return 0;
}