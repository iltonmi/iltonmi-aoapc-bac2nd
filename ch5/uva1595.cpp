#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

typedef pair<int, int> pii;
const int N = 10010;

void solve(int n) {
    int l = N, r = -N;
    set<pii> dots;
    for(int i = 0; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        dots.insert({a, b});
        if(a < l) l = a;
        if(a > r) r = a;
    }
    double mid = (l + r) / 2.0;
    for(auto& t : dots) 
        if(!dots.count({-(t.first - mid) + mid, t.second})) {
            puts("NO"); return;
        }
    puts("YES");
}

int main(void) {
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        solve(n);
    }
    return 0;
}
// 3
// 5
// -2 5
// 0 0
// 6 5
// 4 0
// 2 3
// 4
// 2 3
// 0 4
// 4 0
// 0 0
// 4
// 5 14
// 6 10
// 5 10
// 6 14