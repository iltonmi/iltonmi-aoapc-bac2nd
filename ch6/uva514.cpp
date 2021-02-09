#include <iostream>
#include <stack>

using namespace std;

const int N = 1010;
int a[N];
int n;

bool solve() {
    stack<int> stk;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        int t = a[i];
        if((stk.size() && stk.top() != t) && cnt > t) return false;
        while(cnt < t) stk.push(++cnt);
        if(stk.size() && stk.top() == t)  stk.pop();
    }
    return true;
}

int main(void) {
    bool first = true;
    while(scanf("%d", &n), n) {
        while(true) {
            int t; scanf("%d", &t);
            if(!t) break;
            a[0] = t;
            for(int i = 1; i < n; i++)
                scanf("%d", &t), a[i] = t;
            if(solve()) puts("Yes");
            else puts("No");
        }
        puts("");
    }
    return 0;
}