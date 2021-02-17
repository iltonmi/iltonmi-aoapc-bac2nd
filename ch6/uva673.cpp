#define LOCAL

#include <iostream>
#include <stack>
#include <cstring>

using namespace std;

char line[150];

bool solve() {
    fgets(line, 150, stdin);
    int n = strlen(line) - 1;
    stack<char> stk;
    for(int i = 0; i < n; i++) {
        if(stk.empty()) {
            if(line[i] == ')' || line[i] == ']') return false;
            else stk.push(line[i]);
        }
        else {
            char ch = stk.top();
            if(line[i] == '(' || line[i] == '[') stk.push(line[i]);
            else if(ch == '(' && line[i] == ')') stk.pop();
            else if(ch == '[' && line[i] == ']') stk.pop();
            else return false;
        }
    }
    return stk.empty();
}

int main(void) {
    #ifdef LOCAL
        freopen("uva673.in", "r", stdin);
        freopen("uva673.out", "w", stdout);
    #endif
    int T; scanf("%d\n", &T);
    while(T--) {
        if(solve()) puts("Yes");
        else puts("No");
    }
    return 0;
}