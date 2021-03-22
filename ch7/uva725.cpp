#include <iostream>
#include <cstring>

using namespace std;

bool is_uni(int n, int cnt[]) {
    // 补0
    while(n < 10000) n *= 10;
    while(n) {
        if(cnt[n % 10]++ > 0) return false;
        n /= 10;
    }
    return true;
}

void solve(int n) {
    // 枚举分母，判断是否有效
    // 通过分母 * n计算出分子，判断是否有效
    // 若分子分母都有效，则打印
    //
    // 分母的范围？01234 - 分母*n超过5位
    // 通过一个数组，记录数字的出现情况
    int cnt[10];
    bool found = false;
    for(int down = 1234; ; down++) {
        memset(cnt, 0, sizeof(cnt));
        if(!is_uni(down, cnt)) continue;
        int up = down * n;
        if(up >= 1e5) break;
        if(is_uni(up, cnt)) {
            found = true;
            printf("%05d / %05d = %d\n", up, down, n);
        }
    }
    if(!found) printf("There are no solutions for %d.\n", n);
}

int main(void) {
    int rnd = 0;
    int n;
    while(scanf("%d", &n), n) {
        if(rnd++ > 0) puts("");
        solve(n);
    }
    return 0;
}

// 除了上述思路，还可以用rujia liu的，将2个数放进数组，排序再判断唯一性