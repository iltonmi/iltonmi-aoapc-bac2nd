#include <iostream>
#include <unordered_set>
#include <cmath>
#include <vector>

using namespace std;

int n;

bool is_complete(unordered_set<int>& set, int from, int step, int n) {
    for(int i = from; i < from + n; i += step)
        if(set.count(i)) return false;
    return true;
}

bool has_square(unordered_set<int>& set, int n) {
    for(int r = 0; r < n; r++) {
        for(int c = 1; c <= n; c++) {
            int x = r * (2*n+1) + c;
            int mlen = max(n-x%(2*n+1)+1, n-(x+n)/(2*n+1));
            for(int k = 1; k <= mlen; k++) {
                if(is_complete(set, x, 1, k) 
                && is_complete(set, x + n, 2*n+1, k) 
                && is_complete(set, x + k + n, 2*n+1, k) 
                && is_complete(set, x + k*(2*n+1), 1, k))
                     return true;
            }
        }
    }
    return false;
}

bool dfs(int d, int maxd, int s, vector<int>& v, unordered_set<int>& set) {
    if(d == maxd) {
        if(has_square(set, n)) return false;
        else {
            for(auto t : set) cout << t << ' ';
            cout << endl;
            printf("%d\n", d);
            return true;
        }
    }
    for(int i = s; i < v.size(); i++) {
        set.insert(v[i]);
        if(dfs(d+1, maxd, i+1, v, set)) return true;
        set.erase(v[i]);
    }
    return false;
}

int main(void) {
    int T; scanf("%d", &T);
    while(T--) {
        int k;
        scanf("%d%d", &n, &k);
        unordered_set<int> set;
        for(int i = 0; i < k; i++) {
            int t; scanf("%d", &t);
            set.insert(t);
        }
        vector<int> v;
        for(int i = 1; i <= 2*n*(n+1); i++)
            if(!set.count(i)) v.push_back(i);
        for(int maxd = 0; ; maxd++)
            if(dfs(0, maxd, 0, v, set)) break;
    }
    return 0;
}

// 枚举要拆除的边，最后验证是否存在正方形
// 边长为n的格子，竖的n(n+1)，横的n(n+1), 总共2n(n+1), 编号从1到2n(n+1)
// 通过已经被拆除的边集合，判断是否存在正方形
// 如何判断是否存在square?
// 枚举所有正方形，逐个检查
// 枚举所有正方形第一行的第一条边
// 第0行的有1...n
// 第1行n+(n+1)+1...2n+(n+1)
// 第2行2n+2(n+1)+1...3n+2(n+1)
// 以此类推
// 对于每条边，我们枚举所有可能的大小，去检查
// 对于长度为k的正方形
// 横的上边从左往右+1，竖的边从上往下+(2n+1)
// 横的下边从左往右+1
// 左竖边的第一条边，是上横第一条边+n
// 右竖边的第一条边，是上横第一条边+k-1+n+1=+k+n
// 下横边的第一条边，是上横第一条边的k(2n+1)
// 
// 对于边x，它所代表的正方形，边长范围是多少呢？
// 取决于它是某一行的第几条边。只需要x % (n+n+1)，横的最大长度是n-x%(2n+1)+1
// 竖的最大长度，首先左竖边的编号是x+n, 它处于第几行呢？(x+n)/(2n+1), 竖的最大长度是n-(x+n)/(2n+1)
// 所以边长范围是[1..max(n-x%(2n+1)+1, n-(x+n)/(2n+1))]
// 这个版本暴力超时了，先放着