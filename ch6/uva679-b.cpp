#include <iostream>

using namespace std;

// 方向，取决于是第几个进入该子树的小球
// 奇数次则向左，偶数次则向右
// 第一层：奇数向左，偶数向右
// 第二层：进入第一层的x个球中，有x/2+1个向左进入第二层，有x/2个向又进入第二层，
// 根据新计算出的序数，计算出从哪个方向进入第三层，以此类推。。。
int main(void) {
    int T; scanf("%d", &T);
    int d, x;
    while(T--) {
        int x;
        scanf("%d%d", &d, &x);
        int t = 1;
        for(int i = 1; i < d; i++) {
            if(x & 1) t *= 2, x = x / 2 + 1;
            else t = t * 2 + 1, x /= 2;
        }
        printf("%d\n", t);
    }
    return 0;
}