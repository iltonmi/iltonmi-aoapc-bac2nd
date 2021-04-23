#define LOCAL
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

//        0,    1
//        2,    3
// 4 , 5, 6, 7, 8, 9,10
//       11,  ,12
// 13,14,15,16,17,18,19
//       20    21
//       22    23

int bd[24];
int map[8][7] = {
    {0, 2, 6, 11, 15, 20, 22},
    {1, 3, 8, 12, 17, 21, 23},
    {10, 9, 8, 7, 6, 5, 4},
    {19, 18, 17, 16, 15, 14, 13}
};

int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};

const int rev[8] = {5, 4, 7, 6, 1, 0, 3, 2};

vector<char> ans(1000);

void move(int i) {
    int t = bd[map[i][0]];
    for(int j = 1; j < 7; j++) bd[map[i][j-1]] = bd[map[i][j]];
    bd[map[i][6]] = t;
}

int diff(int x) {
    int ans = 0;
    for(int i = 0; i < 8; i++) 
        if(bd[center[i]] != x) ans++;
    return ans;
}

int h() {
    return min(diff(1), min(diff(2), diff(3)));
}

bool found() {
    for(int i = 0; i < 8; i++)
    if (bd[center[i]] != bd[center[0]]) return false;
    return true;
}

bool dfs(int d, int maxd) {
    if(found()) {
        for(int i = 0; i < d; i++) putchar(ans[i]);
        printf("\n");
        return true;
    }
    if(d + h() > maxd) return false;
    for(int i = 0; i < 8; i++) {
        move(i);
        if(ans.size() < d + 1) ans.push_back('A' + i);
        else ans[d] = 'A' + i;
        if(dfs(d + 1, maxd)) return true;
        move(rev[i]);
    }
    return false;
}

int main(void) {
    #ifdef LOCAL
        freopen("uva1343.in", "r", stdin);
        freopen("uva1343.out", "w", stdout);
    #endif
    for(int i = 4; i < 8; i++)
        for(int j = 0; j < 7; j++) 
            map[i][j] = map[rev[i]][6-j];
    
    while(scanf("%d", &bd[0]), bd[0]) {
        for(int i = 1; i  < 24; i++) 
            scanf("%d", &bd[i]);
        
        if(found()) {
            printf("No moves needed\n");
        } else {
            for(int maxd = 1; ; maxd++)
                if(dfs(0, maxd)) break;
        }
        printf("%d\n", bd[6]);
    }
    return 0;
}

// 这题，对于这种异形状态的建模是重点，利用了映射的思想