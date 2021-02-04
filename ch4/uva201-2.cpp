#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

const int N = 15;
bool h[N][N], v[N][N];
int n, m;

// n * n点矩阵
// m条边
// 枚举每个点，从0 ... n - 1
// 以每个点为左上角，枚举边长 1 ... min(n - 1 - x, n - 1 - y)
// 对于每个左上角(x, y)和边长len确定的正方形，判断是否所有边都存在

bool check_edge(int x, int y, int len, bool is_hori) {
    for(int i = 0; i < len; i++) {
        bool flag = is_hori ? h[x][y] : v[y][x];
        if(!flag) return false;
        if(is_hori) y++;
        else x++;
    }
    return true;
}

bool check(int x, int y, int len) {
    // up , left, right, down
    int dx[4] = {0, 0, len, 0};
    int dy[4] = {0, 0, 0, len};
    for(int i = 0; i < 4; i++) {
        int tx = x + dx[i], ty = y + dy[i];
        if(!check_edge(tx, ty, len, (i + 1) & 1)) 
            return false;
    }
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
        memset(h, 0, sizeof h);
        memset(v, 0, sizeof v);
        for(int k = 0; k < m; k++) {
            char type;
            int i, j;
            cin >> type >> i >> j;
            if(type == 'H') h[i][j] = true;
            else if(type == 'V') v[i][j] = true;
        }
        solve(cnt);
        cnt++;
    }
    return 0;
}