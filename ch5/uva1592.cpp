#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

const int N = 10010, M = 20;
int n, m;
int tab[N][M];
unordered_map<string, int> idmap;
int strid;

int ID(string& str) {
    if(!idmap.count(str)) {
        idmap[str] = ++strid;
    }
    return idmap[str];
}

void readrow(int row) {
    string tmp;
    int ch;
    while(ch = getchar(), !(ch >= ' ' && ch <= '~'));
    tmp += ch;
    for(int i = 1; i <= m; i++) {
        for(;;) {
            ch = getchar();
            if(ch == ',') {tab[row][i] = ID(tmp); tmp.clear(); break;}
            if(ch == '\n' || ch == '\r') {
                tab[row][i] = ID(tmp);
                // cout << tmp << endl;
                return;
            }
            tmp += ch;
        }
    }
}

void solve() {
    for(int i = 1; i <= m; i++) {
        for(int j = i + 1; j <= m; j++) {
            // unordered_map不能够用PII作为key
            map<pii, int> d;
            for(int k = 1; k <= n; k++) {
                pii t = {tab[k][i], tab[k][j]};
                // cout << t.first << ":" << t.second << endl;
                if(d.count(t)) {
                    puts("NO");
                    printf("%d %d\n", d[t], k);
                    printf("%d %d\n", i, j);
                    return;
                }
                d[t] = k;
            }
        }
    }
    printf("YES\n");
}

int main(void) {
    while(cin >> n >> m) {
        strid = 0;
        idmap.clear();
        for(int i = 1; i <= n; i++)
            readrow(i);
        solve();
    }
    return 0;
}