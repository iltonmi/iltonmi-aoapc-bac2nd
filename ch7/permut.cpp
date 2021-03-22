#include <iostream>
#include <algorithm>

using namespace std;

// a子集
// cur子集元素数量
// n总元素数量
// ele集合
// 复杂度：O(选择s的复杂度) * O(2**n)
void print_subset(int ele[], int tmp[], int n, int cur) {
    for(int i = 0; i < cur; i++) printf(i < cur - 1 ? "%d" : "%d\n", tmp[i]);
    // 枚举元素编号
    // 如果是散列，则s = cur ? map[tmp[cur - 1]] + 1 : 0;
    int s = cur ? find(ele, ele + n, tmp[cur - 1]) - ele + 1 : 0;
    // printf("s : %d\n", s);
    for(int i = s; i < n; i++) {
        tmp[cur] = ele[i];
        // printf("choose index : %d, val : %d\n", i, ele[i]);
        print_subset(ele, tmp, n, cur + 1);
    }
}

int main(void) {
    int set[] = {1, 2, 3, 4};
    int tmp[4] = {0};
    print_subset(set, tmp, 4, 0);
    return 0;
}