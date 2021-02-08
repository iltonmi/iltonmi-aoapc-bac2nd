#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int n, m;
int a[10];

bool is_prior(int priority) {
    for(int i = priority + 1; i <= 9; i++)
        if(a[i]) return false;
    return true;
}

void solve() {
    queue<int> q;
    memset(a, 0, sizeof a);
    for(int i = 0; i < n; i++) {
        int t; cin >> t; q.push(t);
        a[t]++;
    } 
    int cnt = 0;
    while(true) {
        // cout << cnt << ":" << m << endl;
        int t = q.front();
        if(!is_prior(t)) q.pop(), q.push(t);
        else {
            ++cnt;
            if(m == 0) {printf("%d\n", cnt); return;}
            q.pop(); a[t]--;
        }
        m = (m - 1 + q.size()) % q.size();
    }
}

int main(void) {
    int T; scanf("%d", &T);
    while(T--) {
        // cout << endl;
        scanf("%d%d", &n, &m); solve();
    }
    return 0;
}