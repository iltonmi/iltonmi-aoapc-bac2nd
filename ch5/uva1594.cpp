#include <iostream>
#include <vector>

using namespace std;

// 1. 直接枚举1000次，最后判断是否全为0，复杂度1e6
// 2. 每走一步，判断一次是否全为0（或者和第一个序列相同）
int main(void) {
    int T; int n;
    cin >> T;
    while(T--) {
        cin >> n;
        vector<int> v(n);
        for(int i = 0; i < n; i++) cin >> v[i];
        for(int i = 0; i < 1000; i++) {
            int t = v[0];
            for(int j = 0; j < n - 1; j++) {
                v[j % n] = abs(v[j % n] - v[(j + 1) % n]);
            }
            v[n - 1] = abs(v[n - 1] - t);
        }
        bool zeroflag = true;
        for(int i = 0; i < n; i++) 
            if(v[i] != 0) {puts("LOOP"), zeroflag = false; break;}
        if(zeroflag) puts("ZERO");
    }
    return 0;
}