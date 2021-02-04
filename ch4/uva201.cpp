#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

// n * n点矩阵
// m条边
// 枚举每个点，从0 ... n - 1
// 以每个点为左上角，枚举边长 1 ... min(n - 1 - x, n - 1 - y)
// 对于每个左上角(x, y)和边长len确定的正方形，判断是否所有边都存在

const int N = 15;
bool st[N * N][N * N];
int n, m;

int idx(int x, int y) {
    return x * n + y;
}

bool check_edge(int x, int y, int len, bool is_x_axis) {
    int fx = x, fy = y, tx = x + (is_x_axis ? 0 : 1), ty = y + (is_x_axis ? 1 : 0);
    for(int i = 0; i < len; i++) {
        if(!st[idx(fx, fy)][idx(tx,ty)]) return false;
        if(is_x_axis) fy++, ty++;
        else fx++, tx++;
    }
    return true;
}

bool check(int x, int y, int len) {
    // up, left, right, down
    int fx = x, fy = y;
    if(!check_edge(fx, fy, len, true)) return false; 
    if(!check_edge(fx, fy, len, false)) return false; 
    fx = x, fy = y + len;
    if(!check_edge(fx, fy, len, false)) return false; 
    fx = x + len, fy = y;
    if(!check_edge(fx, fy, len, true)) return false;
    return true;
}

void solve(int cnt) {
    map<int, int> map;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int len = 1; len <= min(n - i, n - j); len++) 
                if(check(i, j, len)) map[len]++;
        }
    }
    if(cnt != 1) printf("\n**********************************\n\n");
    printf("Problem #%d\n\n", cnt);
    if(!map.size()) printf("No completed squares can be found.\n");
    for(auto p : map) {
        printf("%d square (s) of size %d\n", p.second, p.first);
    }
}

int main(void) {
    int cnt = 1;
    while(scanf("%d%d", &n, &m) != EOF) {
        memset(st, 0, sizeof st);
        for(int k = 0; k < m; k++) {
            char type;
            int i, j;
            cin >> type >> i >> j;
            if(type == 'H') {
                int a = idx(i, j), b = idx(i, j + 1);
                st[a][b] = st[b][a] = true;
            } else if(type == 'V') {
                int a = idx(j, i), b = idx(j + 1, i);
                st[a][b] = st[b][a] = true;
            }
        }
        solve(cnt);
        cnt++;
    }
    return 0;
}