#define LOCAL
#include <iostream>

using namespace std;

int n, L, cnt;
char str[100];

void print_ans(int n) {
    for(int i = 0; i < n; ) {
        for(int j = 0; j < 16 && i < n; j++) {
            if(j > 0) putchar(' ');
            for(int k = 0; k < 4 && i < n; k++, i++) {
                putchar(str[i]);
            }
        }
        puts("");
    }
    printf("%d\n", n);
}

bool is_hard(int n) {
    for(int i = 1; 2 * i <= n; i++) {
        bool same = true;
        for(int j = n - 1; j > n - 1 - i; j--) {
            if(str[j] != str[j - i]) {
                same = false; break;
            }
        }
        if(same) return false;
    }
    return true;
}

void dfs(int idx) {
    for(int i = 0; cnt < n && i < L; i++) {
        str[idx] = 'A' + i;
        if(is_hard(idx + 1)) {
            if(++cnt == n) {
                print_ans(idx + 1);
            }
            dfs(idx + 1);
        }
    }
}

int main(void) {
    #ifdef LOCAL
        freopen("uva129.in", "r", stdin);
        freopen("uva129.out", "w", stdout);
    #endif
    while(scanf("%d%d", &n, &L), n) {
        cnt = 0;
        dfs(0);
    }
    return 0;
}

// 从前L个字母中，选取字符组成hard seq
// 求字母升序的第n大的seq
// hard seq: 相邻的sub seq不相同
// 使用递归枚举，每增加一个字符s[i]，就要判断以这个字符结尾的
// 长度为偶数的字符串，逐个比较前后2部分，如果不符合，那么回溯，如果符合那么打印并且继续
// 这个判断，可以优化吗？emmmm，先不管优化了哈哈哈