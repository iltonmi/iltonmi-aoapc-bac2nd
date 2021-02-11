#include <iostream>
#include <sstream>

using namespace std;

const int N = 10010;
int por[N], ior[N], l[N], r[N];
int n;

bool read_order(int* a) {
    n = 0;
    string str;
    if(!getline(cin, str)) return false;
    stringstream ss(str);
    int val;
    while(ss >> val) a[n++] = val;
    // return n > 0 will be more robust
    return true;
}

int build(int pl, int pr, int il, int ir) {
    if(pl > pr || il > ir) return -1;
    // pr是根节点索引
    int i = il;
    for(; i <= ir; i++)
        if(ior[i] == por[pr]) break;
    int llen = i - il;
    l[pr] = build(pl, pl + llen - 1, il, i - 1);
    r[pr] = build(pl + llen, pr - 1, i + 1, ir);
    return pr;
}

int ans, idx;

void dfs(int val, int x) {
    if(x == -1) return;
    val += por[x];
    if(l[x] == -1 && r[x] == -1) {
        if(val < ans) {
            ans = val; idx = x;
        } else if(val == ans) {
            if(por[idx] > por[x]) idx = x;
        }
        return;
    }
    dfs(val, l[x]);
    dfs(val, r[x]);
}

int main(void) {
    while(read_order(ior)) {
        read_order(por);
        ans = 0x3f3f3f3f;
        build(0, n - 1, 0, n - 1);
        dfs(0, n - 1);
        printf("%d\n", por[idx]);
    }
    return 0;
}