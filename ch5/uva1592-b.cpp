#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

const int N = 10010, M = 20;
int n, m;
// 这个超慢的。。。
map<pii, int> maparr[N][M];
string row[M];
map<string, int> idmap;
int strid;

int ID(string& str) {
    if(idmap.count(str)) return idmap[str];
    idmap[str] = strid;
    return strid++;
}

void readrow() {
    string tmp;
    int ch;
    while(ch = getchar(), !(ch >= ' ' && ch <= '~'));
    tmp += ch;
    for(int i = 1; i <= m; i++) {
        for(;;) {
            ch = getchar();
            if(ch == ',') {row[i] = tmp; tmp.clear(); break;}
            if(ch == '\n' || ch == '\r') {
                row[i] = tmp; return;
            }
            tmp += ch;
        }
    }
}

bool check(int cur_row) {
    for(int i = 1; i <= m; i++) {
        for(int j = i + 1; j <= m; j++) {
            pii t = {ID(row[i]), ID(row[j])};
            // string t = ID(row[i]) + "," + ID(row[j]);
            // cout << t << endl;
            if(maparr[i][j].count(t)) {
                puts("NO");
                printf("%d %d\n", maparr[i][j][t], cur_row);
                printf("%d %d\n", i, j);
                return false;
            }
           maparr[i][j][t] = cur_row;
        }
    }
    return true;
}

int main(void) {
    while(cin >> n >> m) {
        bool flag = true;
        for(int i = 0; i < M; i++)
            for(int j = 0; j < M; j++) maparr[i][j].clear();
        for(int i = 1; i <= n; i++) {
            readrow();
            if(flag && !check(i)) flag = false;
        }
        if(flag) printf("YES\n");
    }
    return 0;
}