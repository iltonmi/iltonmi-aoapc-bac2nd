#include <iostream>
#include <queue>

using namespace std;

void solve(int n) {
    deque<int> dq;
    vector<int> dis;
    for(int i = 1; i <= n; i++) dq.push_back(i);
    while(dq.size() > 1) 
        dis.push_back(dq.front()), dq.pop_front(), dq.push_back(dq.front()), dq.pop_front();
    printf("Discarded cards:");
    for(int i = 0; i < n - 1; i++) {
        if(i > 0) putchar(',');
        printf(" %d", dis[i]);
    }
    printf("\n");
    printf("Remaining card: %d\n", dq.front());
}

int main(void) {
    int n;
    while(cin >> n, n) {
        solve(n);
    }
    return 0;
}