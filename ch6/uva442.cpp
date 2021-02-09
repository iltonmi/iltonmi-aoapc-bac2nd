#include <iostream>
#include <stack>

using namespace std;


typedef pair<int, int> pii;
typedef long long ll;
pii arr[26];

void solve(string& expr) {
    stack<pii> stk;
    if(expr[0] != '(') {puts("0"); return;}
    ll ans = 0;
    for(int i = 0; i < expr.size(); i++) {
        char ch = expr[i];
        if(ch == ')') {
            auto b = stk.top(); stk.pop();
            auto a = stk.top(); stk.pop();
            stk.pop();
            if(a.second != b.first) {
                puts("error");
                return;
            } else ans += (ll)a.first * a.second * b.second;
            stk.push({a.first, b.second});
        } else if(ch == '(') stk.push({-1, -1});
        else stk.push(arr[ch - 'A']);
    }
    printf("%lld\n", ans);
}

int main(void) {
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        char a; int b, c;
        cin >> a >> b >> c;
        arr[a - 'A'] = {b, c};
    }
    string expr;
    while(cin >> expr) {
        solve(expr);
    }
    return 0;
}