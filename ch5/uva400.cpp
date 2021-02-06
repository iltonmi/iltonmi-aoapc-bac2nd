#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// L = longest filename
// C = 1 + (60 - L) / (L + 2)
// R = N / C + (N % C ? 1 : 0) = (N - 1) / C + 1;
// 用vector存储文件名，排序
// 每行输出最多 C 个filename
// 左对齐，宽度L+2，最后一列宽度L
// 设idx为filename索引
// 文件输出会被分成2个部分，左边比右边的行数更多
// 左边：c = idx / R, r = idx % R
// 因此，idx = (idx / R * R) + idx % R = c * R + r
// 右边：c = (idx - 左边) / (R - 1) + 左边列数, r = (idx - 左边) % (R - 1)
// 因此，idx = (c - 左边列数) * (R-1) + r + 左边
// 左边列数 = N % C,左边 = 左边列数 * R
// 因此，idx = (c - 左边列数) * (R - 1) + r + 左边列数 * R,
// idx = c * (R - 1) + r + 左边列数
// 你也以为是这样做？那么就错了。。。
// 你以为是这样？
// 1 4 6
// 2 5 7
// 3
// 其实是这样
// 1 4 7 
// 2 5
// 3 6

const int W = 60; 

int main(void) {
    int n;
    string s_line(W, '-');
    while(cin >> n) {
        vector<string> v(n);
        int L = 0;
        for(int i = 0; i < n; i++) {
            cin >> v[i];
            if(v[i].size() > L) L = v[i].size();
        }
        sort(v.begin(), v.end());
        int C = 1 + (W - L) / (L + 2);
        int R = (n - 1) / C + 1;
        int l_col = n % C;
        cout << s_line << endl;
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                int idx = j * R + i;
                if(idx >= n) break;
                printf("%s", v[idx].c_str());
                int t = (j < C - 1 ? L + 2 : L) - v[idx].size();
                for(int i = 0; i < t; i++) putchar(' ');
            }
            puts("");
        }
    }
    return 0;
}