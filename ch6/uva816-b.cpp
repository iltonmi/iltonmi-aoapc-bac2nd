#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

struct State {
    int x;
    int y;
    int dir;
};

const int N = 10;
bool st[N][N][4][3];
bool visited[N][N][4];
State pre[N][N][4];
queue<State> q;
State entra, dest;
char maze_name[24];

const string dirs = "NESW";
const string turns = "FLR";

int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int dir_id(char ch) {
    for(int i = 0; i < 4; i++)
        if(dirs[i] == ch) return i;
    return -1;
}

int turn_id(char ch) {
    for(int i = 0; i < 3; i++)
        if(turns[i] == ch) return i;
    return -1;
}

State trans(const State& u, int turn) {
    int dir = u.dir;
    if(turn == 1) dir = (dir - 1 + 4) % 4;
    if(turn == 2) dir = (dir + 1) % 4;
    return State {u.x + dx[dir], u.y + dy[dir], dir};
}

bool inside(int r, int c) {
  return r >= 1 && r <= 9 && c >= 1 && c <= 9;
}

void print_ans() {
    vector<pair<int, int>> v;
    int x = dest.x, y = dest.y, dir = dest.dir;
    v.push_back({x, y});
    do {
        auto& state = pre[x][y][dir];
        v.push_back({state.x, state.y});
        x = state.x, y = state.y, dir = state.dir;
    } while(x != entra.x || y != entra.y);
    for(int j = v.size() - 1; j >= 0;) {
        printf(" ");
        for(int i = 0; i < 10 && j >= 0; i++, j--) {
            auto t = v[j];
            printf(" (%d,%d)", t.first, t.second);
        }
        puts("");
    }
}

bool solve() {
    memset(visited, 0, sizeof visited);
    auto t = trans(entra, turn_id('F'));
    pre[t.x][t.y][t.dir] = entra;
    visited[t.x][t.y][t.dir] = true;
    queue<State> q;
    q.push(t);
    while(q.size()) {
        auto u = q.front(); q.pop();
        if(u.x == dest.x && u.y == dest.y) {
            dest.dir = u.dir;
            return true;
        }
        for(int i = 0; i < 3; i++) {
            if(!st[u.x][u.y][u.dir][i]) continue;
            auto v = trans(u, i);
            if(!visited[v.x][v.y][v.dir] && inside(v.x, v.y)) {
                visited[v.x][v.y][v.dir] = true;
                pre[v.x][v.y][v.dir] = u;
                q.push(v);
            }
        }
    }
    return false;
}


int main(void) {
    while(scanf("%s", maze_name), strcmp(maze_name, "END") != 0) {
        int x, y; char str[10];
        memset(st, 0, sizeof(st));
        scanf("%d%d%s", &x, &y, str);
        entra = State{x, y, dir_id(str[0])};
        scanf("%d%d", &x, &y);
        dest = {x, y, 0};
        while(scanf("%d", &x), x) {
            scanf("%d", &y);
            while(scanf("%s", str), strcmp(str, "*") != 0) {
                int dir = dir_id(str[0]);
                for(int i = 1; i < strlen(str); i++) {
                    st[x][y][dir][turn_id(str[i])] = true;
                }
            }
        }
        printf("%s\n", maze_name);
        if(solve()) print_ans();
        else puts("  No Solution Possible");
    }
    return 0;
}