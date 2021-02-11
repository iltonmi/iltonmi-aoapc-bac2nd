#include <iostream>
#include <cstring>

using namespace std;

const int N = 524300;
bool a[N];
int d, n;


// 超时版本。。。N * 19 = 1e7，单组用例的时间复杂度已经很高了
// 需要利用小球的序号和下落方向的关系
int drop() {
    int ans = 1;
    for(int i = 1; i < d; i++) {
        int t = ans;
        if(a[t]) ans = ans * 2 + 1;
        else ans *= 2;
        a[t] = !a[t];
    }
    return ans;
}

int main(void) {
    int T; scanf("%d", &T);
    while(T--) {
        int x;
        scanf("%d%d", &d, &x);
        memset(a, 0, sizeof a);
        for(int i = 0; i < x -1; i++) drop();
        printf("%d\n", drop());
    }
    return 0;
}