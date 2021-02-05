#include <iostream>
#include <vector>

using namespace std;

// 1
// possible move(s) of current player
// otherwise, hint
// 2
// make a move or change turns if no legal move
// 3
// quit and print

const int N = 8;
int grid[N + 1][N + 1];
int bl, wh;
int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};

void print_grid() {
    for(int i = 1; i <= N; i++) 
        for(int j = 1; j <= N; j++) 
            printf(j < N ? "%c" : "%c\n", grid[i][j]);
}

bool check_idx(int x, int y) {
    return x >= 1 && x <= 8 && y >= 1 && y <= 8;
}

bool check(int x, int y, char color) {
    for(int i = 0; i < 8; i++) {
        int tx = x + dx[i], ty = y + dy[i];
        int same = 0, diff = 0;
        while(check_idx(tx, ty) && grid[tx][ty] != '-') {
            char ch = grid[tx][ty];
            if(ch == color) {
                same = 1; break;
            } else {
                diff++;
            }
            tx += dx[i], ty += dy[i];
        }
        if(diff && same == 1) return true;
    }
    return false;
}

void list_move(char color) {
    vector<pair<int, int>> v;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            if(grid[i][j] == '-' && check(i, j, color)) 
                v.push_back({i, j});
        }
    }
    if(!v.size()) printf("No legal move.");
    for(int i = 0; i < v.size(); i++) {
        auto t = v[i];
        printf(i > 0 ? " (%d,%d)" : "(%d,%d)", t.first, t.second);
    }
    puts("");
}

void chg_color(char& color) {
    color = color == 'B' ? 'W' : 'B';
}

bool move(char color, int x, int y) {
    bool flag = false;
    int cnt = 0;
    for(int i = 0; i < 8; i++) {
        int tx = x + dx[i], ty = y + dy[i];
        int same = 0, diff = 0;
        while(check_idx(tx, ty) && grid[tx][ty] != '-') {
            char ch = grid[tx][ty];
            if(ch == color) {
                same = 1; break;
            } else diff++;
            tx += dx[i], ty += dy[i];
        }
        if(!(diff && same == 1)) continue;
        flag = true;
        tx = x + dx[i], ty = y + dy[i];
        do {
            grid[tx][ty] = color;
            tx += dx[i], ty += dy[i], cnt++;
        } while(check_idx(tx, ty) 
            && grid[tx][ty] != '-' && grid[tx][ty] != color);
    }
    if(!flag) return false;
    if(color == 'B') bl += cnt, wh -= cnt, bl++;
    else bl -= cnt, wh += cnt, wh++;
    grid[x][y] = color;
    return true;
}

int main(void) {
    int w; cin >> w;
    for(int i = 0; i < w; i++) {
        if(i > 0) puts("");
        bl = 0, wh = 0;
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                char ch; cin >> ch;
                if(ch == 'B') bl++;
                else if(ch == 'W') wh++;
                grid[i][j] = ch;
            }
        }
        char cmd;
        char color;
        cin >> color;
        while(cin >> cmd, cmd != 'Q') {
            if(cmd == 'L') list_move(color);
            else if(cmd == 'M') {
                int x, y; cin >> x;
                y = x % 10, x /= 10;
                if(!move(color, x, y)) 
                    chg_color(color), move(color, x, y);
                chg_color(color);
                printf("Black - %2d White - %2d\n", bl, wh);
            }
        }
        print_grid();
    }
    return 0;
}