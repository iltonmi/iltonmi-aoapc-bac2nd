#include <iostream>

using namespace std;

int main(void) {
    // 数据范围小，直接暴力O(n^2)，当然还有其他做法：前缀和O(n^2)
    // 但是这道题在这本教材的定位，是暴力
    int a[20], n;
    int cnt = 0;
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        // 注意用int会溢出
        long long ans = 0;
        for(int i = 0; i < n; i++) {
            // 注意用int会溢出
            long long t = 1;
            for(int j = i; j < n; j++) {
                t *= a[j];
                if(t > ans) ans = t;
            }
        }
        printf("Case #%d: The maximum product is %lld.\n\n", ++cnt, ans);
    }
    return 0;
}