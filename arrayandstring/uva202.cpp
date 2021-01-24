#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

//     ans
// b   a
//     余数
// 每除一次，若余数不为0，则余数乘10
// 若除数重复出现，说明出现了循环

const int N = 30100;
int st[N];

// 0.(0)
// 3.(0)
// 3.04(0)
// 3.1(13)
void solve(int ia, int ib) {
    memset(st, -1, sizeof st);
    int a = ia, b = ib;
    vector<int> ans;
    int len = 0;
    while(true) {
        // 判断除数是否重复
        if(~st[a]) {
            len = ans.size() - st[a];
            break;
        }
        ans.push_back(a / b);
        st[a] = ans.size() - 1;
        a = 10 * (a % b);
    }
    printf("%d/%d = %d.", ia, ib, ans[0]);
    int i = 1;
    for(; i < st[a]; i++)
        printf("%d", ans[i]);
    int t = i;
    printf("(");
    // 注意一个细节，初始的a作为除数重复出现，那么余数应该多输出一位
    for(; i < t + len && i <= 50; i++)
        printf("%d", ans[i % ans.size()]);
    if(i >= 50) printf("...");
    printf(")\n");
    printf("   %d = number of digits in repeating cycle\n", len);
    puts("");
    // 1/3 0,1
    // 10/3 3,1
    // 10/3 3,1
}

int main(void) {
    // solve(76, 25);
    // solve(5, 43);
    // solve(1, 397);
    // solve(1, 6);
    // solve(5, 7);
    // solve(1, 250);
    // solve(300, 31);
    // solve(655, 990);
    // solve(0, 1);
    // solve(5, 5);
    int a, b;
    for(int i = 0; scanf("%d", &a) != EOF; i++) {
        scanf("%d", &b);
        solve(a, b);
    }
    return 0;
}
