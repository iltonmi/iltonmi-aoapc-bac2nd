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
int dist[N][N][4];
State pre[N][N][4];
State entra, dest;
char maze_name[30];

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

void print_ans() {
    vector<State> v;
    auto t = dest;
    for(;;) {
        v.push_back(t);
        if(!dist[t.x][t.y][t.dir]) break;
        t = pre[t.x][t.y][t.dir];
    }
    v.push_back(entra);
    for(int j = v.size() - 1; j >= 0;) {
        printf(" ");
        for(int i = 0; i < 10 && j >= 0; i++, j--) {
            auto t = v[j];
            printf(" (%d,%d)", t.x, t.y);
        }
        puts("");
    }
}

bool inside(int r, int c) {
  return r >= 1 && r <= 9 && c >= 1 && c <= 9;
}

bool solve() {
    queue<State> q;
    memset(dist, -1, sizeof(dist));
    auto u = trans(entra, turn_id('F'));
    pre[u.x][u.y][u.dir] = entra;
    // 为什么不将entra设置为0呢？因为entra没被搜索过，实际上第一个被搜索的状态是
    // tran(entra, turn_id('F'))
    // 而且，如果将dist of entra设置为0，那么dist后面可能会被覆盖
    dist[u.x][u.y][u.dir] = 0;
    q.push(u);
    while(q.size()) {
        auto u = q.front(); q.pop();
        if(u.x == dest.x && u.y == dest.y) {
            dest.dir = u.dir; 
            return true;
        } 
        for(int i = 0; i < 3; i++) {
            if(!st[u.x][u.y][u.dir][i]) continue;
            auto v = trans(u, i);
            // dist不能改成bool类型，因为同一个点可能会被经过好多次
            // 利用pre求路线时，无法判断
            if(dist[v.x][v.y][v.dir] < 0 && inside(v.x, v.y)) {
                dist[v.x][v.y][v.dir] = dist[u.x][u.y][u.dir] + 1;
                pre[v.x][v.y][v.dir] = u;
                q.push(v);
            }
        }
    }
    return false;
}


int main(void) {
    while(scanf("%s", maze_name), strcmp(maze_name, "END") != 0) {
        int x, y; char str[5];
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

// 整个迷宫可以被视作一张图，intersection就是图中的节点
// 显然，这是一张无权图，可以用BFS求最短路
// 但是，问题在于这张图上的点，如果只用坐标来标识是不够的
// 因为，出方向被入方向所决定，点之间的关系是动态的，不是静态的
// 如何解决这个问题呢？
// 根据题目，我们知道，从某个方向进入某个点，它必然从某个固定的方向进入固定的点
// 换言之，如果我们将(r,c,dir)看作一个状态，那么它的状态转移路径是确定的
// 所以，我们可以使用BFS遍历这些状态，找到状态转移的最短路径

// while !q.empty
// for node in q
//   if q is end, break
//   for 3 dirs
//     if d[node][nextnode] enque

// dispatch uni-id for each dirs
// struct Node {int r; int c; int dir;}
// st[r][c][dir] whether (r,c) can go from dir
// how to calculate next node ?
// 
// while !q.emtpy
//   for node in q
//   for dir in 3dirs
//      if(!st[node.r][node.c][node.dir][dir]) continue;
//      nextnode = calnext(node, dir)
//      if(can_reach(nextnode.r, nextnode.c) 
//        && d[nextnode.r][nextnode.c][nextnode.dir] < 0)
//        nd = d + 1; 
//        mark the pre node;
//        enque

// 这个方案是有缺陷的，因为起点可能被经过不止一次，所以用bool类型的visited的话，无法分辨是第几次