#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

typedef pair<int, string> PIS;

const int N = 15;
int r, c;
char grid[N][N];
int number[N][N];

bool verify(char ch) {
    return ch == '*' || isalpha(ch);
}

bool read_puzzle() {
    scanf("%d", &r);
    if(r == 0) return false;
    scanf("%d\n", &c);
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++) {
            char ch;
            while(!verify(ch = getchar()));
            grid[i][j] = ch;
        }
    return true;
}

bool check_idx(int x, int y) {
    return x >= 0 && x <= r && y >= 0 && y <= c;
}

void numbering() {
    int num = 0;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if(grid[i][j] == '*') continue;
            int ax = i - 1, ay = j;
            int lx = i, ly = j - 1;
            if(!check_idx(ax, ay) || grid[ax][ay] == '*' 
            || !check_idx(lx, ly) || grid[lx][ly] == '*')
                number[i][j] = ++num;
        }
    }
}

void solve() {
    printf("Across\n");
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; ) {
            while(j < c && grid[i][j] == '*') j++;
            if(j >= c) break;
            int num = number[i][j];
            string t;
            while(j < c && grid[i][j] != '*') t += grid[i][j++];
            printf("%3d.%s\n", num, t.c_str());
        }
    }
    vector<PIS> v;
    for(int j = 0; j < c; j++) {
        for(int i = 0; i < r; ) {
            while(i < r && grid[i][j] == '*') i++;
            if(i >= r) break;
            string t;
            int num = number[i][j];
            while(i < r && grid[i][j] != '*') t += grid[i++][j];
            v.push_back({num, t});
        }
    }
    sort(v.begin(), v.end());
    printf("Down\n");
    for(int i = 0; i < v.size(); i++) {
        printf("%3d.%s\n", v[i].first, v[i].second.c_str());
    }
}

int main() {
    for(int i = 1; ; i++) {
        if(!read_puzzle()) break;
        memset(number, 0, sizeof number);
        numbering();
        if(i != 1) puts("");
        printf("puzzle #%d:\n", i);
        solve();
    }
    return 0;
}