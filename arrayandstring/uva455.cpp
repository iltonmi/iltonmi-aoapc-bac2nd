#include <iostream>

using namespace std;

bool verify(string& s, int p) {
    int n = s.size();
    if(n % p) return false;
    for(int i = 0; i < n; i += p)
        if(s.substr(0, p) != s.substr(i, p)) return false;
    return true;
}

void solve() {
    string s; cin >> s;
    for(int i = 1; i <= s.length(); i++) 
        if(verify(s, i)) {
            printf("%d\n", i);
            break;
        }
}

int main() {
    int n; scanf("%d", &n);
    while(n--) {
        solve();
        if(n) puts("");
    }
    return 0;
}