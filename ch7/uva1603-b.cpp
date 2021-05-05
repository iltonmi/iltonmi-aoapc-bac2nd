#include <iostream>
#include <cstring>
#include <cmath>

const int maxn = 60, maxm = 61;
int size[maxn], fullsize[maxn];
bool contains[maxn][maxm], exists[maxm];
int n, sqcnt;

int rowstick(int i, int j) {
    return (2*n+1)*i+j+1;
}

int colstick(int i, int j) {
    return n+1+(2*n+1)*i+j;
}

int fullstickamount(int n) {
    return 2*n*(n+1);
}

void init() {
    int k;
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= fullstickamount(n); i++) exists[i] = true;
    for(int i = 0; i < k; i++) {
        int t; scanf("%d", &t);
        exists[t] = false;
    }
    memset(contains, false, sizeof contains);
    sqcnt = 0;
    // 枚举大小从小到大，很重要
    // 如果先按左上坐标，再按长度需要300ms+-
    // 先按长度，再按左上坐标，只需要20ms+-
    for(int len = 1; len <= n; len++) {
        for(int i = 0; i <= n - len ; i++) {
            for(int j = 0; j <= n - len; j++) {
                size[sqcnt] = 0;
                fullsize[sqcnt] = 4 * len;
                for(int k = 0; k < len; k++) {
                    int arr[] = {rowstick(i, j+k), rowstick(i+len, j+k), colstick(i+k, j), colstick(i+k, j+len)};
                    for(int t = 0; t < 4; t++) {
                        if(exists[arr[t]]) size[sqcnt]++;
                        contains[sqcnt][arr[t]] = true;
                    }
                }
                sqcnt++;
            }
        }
    }
}

int find_square() {
    for(int i = 0; i < sqcnt; i++)
        if(size[i] == fullsize[i]) return i;
    return -1;
}

int ans;

void dfs(int d) {
    if(d >= ans) return;
    int k = find_square();
    if(k == -1) {
        ans = d;
        return;
    }
    // 遍历每条边
    for(int i = 1; i <= fullstickamount(n); i++) {
        if(contains[k][i]) {
            for(int j = 0; j < sqcnt; j++)
                if(contains[j][i]) size[j]--;
            dfs(d+1);
            for(int j = 0; j < sqcnt; j++)
                if(contains[j][i]) size[j]++;
        }
    }
}

int main(void) {
    int T; scanf("%d", &T);
    while(T--) {
        init();
        ans = 10000;
        dfs(0);
        printf("%d\n", ans);
    }
    return 0;
}

// 看了Rujia Liu的题解，这建模有点复杂，但是解是真的简洁优雅。。。
// 每一步首先找到最小的完整正方形，因为小的必然破坏大的，但是大的不一定破坏小的
// 枚举所有边，每次只拆掉一条，并且递归，递归结束后恢复现场
// 最多有2*5*6 = 60个正方形，编号
// 1. 为了快速知道正方形是否完整，可以维护正方形的当前存在边的总数，以及完整时边的总数
// 2. 遍历每条边的时候，需要修改包含这条边的正方形的存在边的总数，
//  需要通过正方形编号，查询正方形是否包含某条边

// 1. size[n], fullsize[n]
// 2. contains[n][2*n(n+1)]

// 最大的收获可能是建模吧。。。