#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

#define x first
#define y second

typedef pair<int, int> pii;

int sx, sy, tx, ty;
int dist[8][8];
int dx[8] = {2, 2, 1, -1, -2, -2, -1, 1};
int dy[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

int solve() {
    memset(dist, -1, sizeof(dist));
    queue<pii> q;
    q.push({sx, sy});
    dist[sx][sy] = 0;
    while(q.size()) {
        auto t = q.front(); q.pop();
        if(t.x == tx && t.y == ty) return dist[tx][ty];
        for(int i = 0; i < 8; i++) {
            int a = t.x + dx[i], b = t.y + dy[i];
            if(a < 0 || a >= 8 || b < 0 || b >= 8) continue;
            if(dist[a][b] != -1) continue;
            dist[a][b] = dist[t.x][t.y] + 1;
            q.push({a, b});
        }
    }
    return -1;
}

int main(void) {
    char from[3], to[3];
    while(scanf("%s", from) != EOF) {
        scanf("%s", to);
        sy = from[0] - 'a', sx = from[1] - '1';
        ty = to[0] - 'a', tx = to[1] - '1';
        printf("To get from %s to %s takes %d knight moves.\n", from, to, solve());
    }
    return 0;
}