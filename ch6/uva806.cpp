#define LOCAL

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 70;
int n, num;
char g[N][N];
vector<int> treenums;

bool is_2color(int r, int c, int len) {
    char color = g[r][c];
    for(int i = r; i < r + len; i++)
        for(int j = c; j < c + len; j++)
            if(g[i][j] != color) return true;
    return false;
}

void img2tree(int r, int c, int len, vector<int>& path) {
    if(!is_2color(r, c, len)) {
        if(g[r][c] == '0') return;
        int base = 1;
        int ans = 0;
        for(int i = 0; i < path.size(); i++) {
            ans += path[i] * base;
            base *= 5;
        }
        treenums.push_back(ans);
        return;
    }
    len >>= 1;
    path.push_back(1);
    img2tree(r, c, len, path);
    path.back() = 2;
    img2tree(r, c + len, len, path);
    path.back() = 3;
    img2tree(r + len, c, len, path);
    path.back() = 4;
    img2tree(r + len, c + len, len, path);
    path.pop_back();
}

void tree2img(int r, int c, int len, vector<int>& path, int depth) {
    if(depth == path.size()) {
        for(int i = r; i < r + len; i++)
            for(int j = c; j < c + len; j++) g[i][j] = '*';
        return;
    }
    len >>= 1;
    int t = path[depth++];
    if(t == 1) tree2img(r, c, len, path, depth);
    else if(t == 2) tree2img(r, c + len, len, path, depth);
    else if(t == 3) tree2img(r + len, c, len, path, depth);
    else if(t == 4) tree2img(r + len, c + len, len, path, depth);
}

void init_img(char ch) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) g[i][j] = ch;
}

int main(void) {
    #ifdef LOCAL
    freopen("uva806.in", "r", stdin);
    freopen("uva806.out", "w", stdout);
    #endif
    int cnt = 0;
    while(scanf("%d", &n), n) {
        if(cnt > 0) printf("\n");
        printf("Image %d\n", ++cnt);
        if(n > 0) {
            for(int i = 0; i < n; i++)
                scanf("%s", g[i]);

            vector<int> path;
            treenums.clear();
            img2tree(0, 0, n, path);
            sort(treenums.begin(), treenums.end());
            for(int i = 0; i < treenums.size(); ) {
                for(int j = 0; j < 12 && i < treenums.size(); i++, j++)
                    printf(j > 0 ? " %d" : "%d", treenums[i]);
                printf("\n");
            }
            printf("Total number of black nodes = %d\n", treenums.size());
        } else {
            n *= -1;
            int t; scanf("%d", &t);
            if(t == 0) init_img('*'), scanf("%d", &t);
            else if(t == -1) init_img('.');
            else {
                init_img('.');
                do {
                    vector<int> path;
                    while(t) path.push_back(t % 5), t /= 5;
                    tree2img(0, 0, n, path, 0);
                } while(scanf("%d", &t), t != -1);
            }
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) putchar(g[i][j]);
                printf("\n");
            }
        }
    }
    return 0;
}