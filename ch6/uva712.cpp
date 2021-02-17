#define LOCAL

#include <iostream>
#include <cmath>

using namespace std;

// 根据x后的序数取数字，这个好办
// 问题是：如何根据变量，决定答案的位置呢？
// 其实也不难，给满二叉树编号
// 叶子节点从左到右的编号是2 ** n ... 2 ** (n + 1)

int order[10];
char str[10];
char leafs[130];

int main(void) {
    #ifdef LOCAL
        freopen("uva712.in", "r", stdin);
        freopen("uva712.out", "w", stdout);
    #endif
    int n, m;
    int casenum = 0;
    while(cin >> n, n) {
        for(int i = 1; i <= n; i++) {
            scanf("%s", str);
            order[i] = str[1] - '0';
        }
        scanf("%s%d\n", leafs, &m);
        string ans;
        for(int i = 0; i < m; i++) {
            int num = 1;
            scanf("%s", str);
            for(int j = 1; j <= n; j++) {
                if(str[order[j] - 1] == '0') num *= 2;
                else num = num * 2 + 1;
            }
            ans += leafs[num - (int)pow(2, n)];
        }
        printf("S-Tree #%d:\n%s\n\n", ++casenum, ans.c_str());
    }
    return 0;
}