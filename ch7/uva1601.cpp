#define LOCAL
#include <iostream>
#include <cctype>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

const int maxn = 20;
pair<int, int> pos[maxn * maxn];
vector<int> map[maxn * maxn];
unordered_map<int, int> dist;
int id[maxn][maxn];
int start, dest;
int dx[] = {0, 0, -1, 1, 0}, dy[] = {-1, 1, 0, 0, 0};

bool is_conflict(int a, int b, int na, int nb) {
    return na == nb || (a == nb && b == na);
}

int bfs() {
    queue<int> q;
    dist.clear();
    q.push(start);
    dist[start] = 0;
    while(q.size()) {
        int t = q.front(); q.pop();
        // id -> pos, pos -> npos, npos -> nid
        int a = t & 255, b = (t >> 8) & 255, c = (t >> 16) & 255;
        // printf("%d %d %d\n", a, b, c);
        for(int i = 0; i < map[a].size(); i++) {
            int na = map[a][i];
            for(int j = 0; j < map[b].size(); j++) {
                int nb = map[b][j];
                if(is_conflict(a, b, na, nb)) continue;
                for(int k = 0; k < map[c].size(); k++) {
                    int nc = map[c][k];
                    if(is_conflict(a, c, na, nc)) continue;
                    if(is_conflict(b, c, nb, nc)) continue;
                    // printf("%d %d %d\n", na, nb, nc);
                    int next = 0;
                    next |= na, next |= (nb << 8), next |= (nc << 16);
                    if(dist.count(next)) continue;
                    if(next == dest) return dist[t] + 1;
                    dist[next] = dist[t] + 1;
                    q.push(next);
                }
            }
        }
        // printf("\n");
    }
    return -1;
}

int main(void) {
    #ifdef LOCAL
        freopen("uva1601.in", "r", stdin);
        freopen("uva1601.out", "w", stdout);
    #endif

    int w, h, n;
    char g[20][20];
    while(scanf("%d%d%d", &w, &h, &n), n) {
        scanf("\n");
        for(int i = 0; i < h; i++) fgets(g[i], 20, stdin);
        // for(int i = 0; i  < h; i++)
        //     printf("%s", g[i]);
        int cnt = 0;
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                if(g[i][j] != '#') 
                    pos[cnt] = {i, j}, id[i][j] = cnt++;
            }
        }
        start = dest = 0;
        for(int i = 0; i < cnt; i++) {
            map[i].clear();
            int a = pos[i].first, b = pos[i].second;
            for(int j = 0; j < 5; j++) {
                int ta = a + dx[j], tb = b + dy[j];
                if(ta < 0 || ta >= h || tb < 0 || tb >= w) continue;
                int ch = g[ta][tb], tid = id[ta][tb];
                if(ch == '#') continue;
                if(islower(ch)) start |= (tid << (ch - 'a') * 8);
                if(isupper(ch)) dest |= (tid << (ch - 'A') * 8);
                map[i].push_back(tid);
            }
        }
        if(n <= 2) map[cnt].push_back(cnt), start |= cnt << 16, dest += cnt << 16, cnt++;
        if(n <= 1) map[cnt].push_back(cnt), start |= cnt << 8, dest += cnt << 8, cnt++;
        printf("%d\n", bfs());
    }
    return 0;
}

// for this problem,
// every ghost has a start point and an end point.
// our job is to move the ghost with least steps
// let notice some crucial detail:
// 1. treat all ghosts' position as a whole, it turns to be a state search problem
// but the problem is, every ghost 256 status, all ghost may have 256 ** 3 status
// and each status has 5 ** 3 which is 125 possiblity of next status,
// so the time complexity whould be 1e8 * 1e2, 1e10 will exceed the 1s time limitation.
// conclusion 1: we need to reduce the searched status
//
// 2.  Any 2*2 area on any map has at least one sharp
// There are 1/4 sharps, if we ignore them, all ghost may have 144 ** 3 status
// which is totallly 3e6, the time complexity is effectively decreased
// 
// 3. All corridor cells in a map are connected
// so we can ignore the sharps, without affect the result
//
// untill now, we can confirm that the state space is mostly 64 ** 3 * 125 = 3e8
// and of course we can cut the branch when the ghost movement is illegal to decrease the state space again
// 
// now we should consider how to model the status and the grid
// lets see the valid state transition rule:
// 1. No more than one ghost occupies one position at the end of the step.
// 2. No pair of ghosts exchange their positions one another in the step.
// we should check whether they occupy the same positon or swap position
// so how to model the position? give them an id or use the (x,y) diretly?
// firstly, we must keep the (x,y) in order to calculate the move.
// secondly, we can assign an id to each position so we can treat the grid as a map
// contains of nodes with id and edge
// 
// 1. we assign each pos an id and preprocess the connect corridor cells to a connected map
// 2. we consider the pos of (at most) 3 ghosts as a whole, since there are at most 144 status
// we can store the id into a 8 bit uint, so we can store pos of 3 ghost into a 32 bit int
// 3. the valid transition rule : for ghost a to na, ghost b to nb, na != nb && (a != nb || b != na)
// 4. for state transition consisitency, we will always have 3 ghost, add fake ghost if less than 3.

// for each case:
// give the empty space an id
// for each node , add an edge if it can connect to 4 neighbours
// while add edge, save the pos of ghost and the end point
// if ghosts is less than 3, than add fake ghost, assign each an id and add it to the map
// use bfs search to travase states

// compare to Rujia Liu's solutions: a struct can be split to several arrays each represent a field
// what i learn from this question: when necessary or state transitions are complicated,
// we can build a implict graph, assign each state an id, transform state transition to graph traversal