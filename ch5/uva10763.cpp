#include <iostream>
#include <map>
using namespace std;

typedef pair<int, int> pii;

map<int, int> cntmap;
int n;

void solve() {
    for(int i = 0; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        cntmap[b]++, cntmap[a]--;
    }
    for(auto& t : cntmap)
        if(t.second != 0) {puts("NO"); return;}
    puts("YES");
}

int main(void) {
    while(scanf("%d", &n), n)
        cntmap.clear(), solve();
    return 0;
}