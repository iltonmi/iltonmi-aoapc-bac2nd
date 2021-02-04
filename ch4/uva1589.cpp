 #include <iostream>
 #include <cstring>
 #include <vector>
 #include <cmath>
 #include <unordered_map>

 using namespace std;

 // 对于每组问题：
 // 枚举black general能走到的有效位置(x, y)
 // 枚举全部red pieces，判断是否能走到(x, y)
 
 // capture rules:
 // G - general:
 // no pieces between 2 general
 // y1 == y2 && (x1 - 1 ... x2 + 1, y1)上没有任何pieces
 // R - chariot:
 // (x1 == x2 && y1 < y2 && (x1, y1 + 1 ... y2 - 1)上没有任何pieces)
 // || (y1 == y2 && x1 < x2 && (x1 + 1 ... x2 - 1, y1)上没有任何pieces)
 // C - cannon:
 // (x1 == x2 && y1 < y2 && (x1, y1 + 1 ... y2 - 1)只有1个piece)
 // || (y1 == y2 && x1 < x2 && (x1 + 1 ... x2 - 1, y1)只有1个piece)
 // H - horse:
 // 枚举（最多8个）有效位置，注意蹩马腿

typedef pair<int, int> pii;

typedef bool(*check_fp)(int, int, int, int);

const int N = 11;
char grid[N][N];
vector<pii> v;
unordered_map<char, check_fp> fn_map;

bool check_idx(int x, int y) {
    return x >= 1 && x <= 10 && y >= 1 && y <= 9;
}

bool check_g_idx(int x, int y) {
    return x >= 1 && x <= 3 && y >= 4 && y <= 6;
}

bool check_g(int x, int y, int gx, int gy) {
    if(x == gx && y == gy) return false;
    if(y != gy) return false;
    for(int i = gx + 1; i <= x - 1; i++) 
        if(grid[i][y]) return false;
    return true;
}

bool check_r(int x, int y, int gx, int gy) {
    if(x == gx && y == gy) return false;
    if(x == gx) {
        int from = min(y, gy) + 1, to = max(y , gy) - 1;
        for(int j = from; j <= to; j++)
            if(grid[x][j]) return false;
        return true;
    }
    if(y == gy) {
        int from = min(x, gx) + 1, to = max(x, gx) - 1;
        for(int i = from; i <= to; i++)
            if(grid[i][y]) return false;
        return true;
    }
    return false;
}

bool check_c(int x, int y, int gx, int gy) {
    if(x == gx && y == gy) return false;
    if(x == gx) {
        int from = min(y, gy) + 1, to = max(y , gy) - 1;
        int cnt = 0;
        for(int j = from; j <= to && cnt <= 1; j++)
            if(grid[x][j]) cnt++;
        if(cnt == 1) return true;
    }
    if(y == gy) {
        int from = min(x, gx) + 1, to = max(x, gx) - 1;
        int cnt = 0;
        for(int i = from; i <= to && cnt <= 1; i++)
            if(grid[i][y]) cnt++;
        if(cnt == 1) return true;
    }
    return false;
}

bool check_h(int x, int y, int gx, int gy) {
    if(x == gx && y == gy) return false;
    // up, right, down, left
    int dy[8] = {-1, 1, 2, 2, 1, -1, -2, -2};
    int dx[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
    for(int i = 0; i < 8; i++) {
        int tx = x + dx[i], ty = y + dy[i];
        if(!check_idx(tx, ty)) continue;
        if(i / 2 == 0 && grid[x - 1][y]) continue;
        else if(i / 2 == 1 && grid[x][y + 1]) continue;
        else if(i / 2 == 2 && grid[x + 1][y]) continue;
        else if(i / 2 == 3 && grid[x][y - 1]) continue;
        if(tx == gx && ty == gy) return true;
    }
    return false;
}

bool check_mate(int x, int y) {
    for(auto t : v) {
        int tx = t.first, ty = t.second;    
        char type = grid[tx][ty];
        if((*fn_map[type])(tx, ty, x, y)) return true;
    }
    return false;
}


int main(void) {
    fn_map['G'] = check_g;
    fn_map['H'] = check_h;
    fn_map['R'] = check_r;
    fn_map['C'] = check_c;
    while(true) {
        int n, x , y; cin >> n >> x >> y;
        if(!x) break;
        memset(grid, 0, sizeof grid);
        v.clear();
        for(int i = 0; i < n; i++) {
            char type;
            int tx, ty;
            cin >> type >> tx >> ty;
            grid[tx][ty] = type;
            v.push_back({tx, ty});
        }
        int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
        bool flag = true;
        for(int i = 0; i < 4; i++) {
            int tx = x + dx[i], ty = y + dy[i];
            if(check_g_idx(tx, ty) && !check_mate(tx, ty)) {
                flag = false; break;
            }
        }
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}