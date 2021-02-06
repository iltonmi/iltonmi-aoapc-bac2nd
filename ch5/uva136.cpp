#include <iostream>
#include <queue>
#include <unordered_set>

typedef long long ll;

using namespace std;

int main(void) {
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    unordered_set<ll> set;
    pq.push(1);
    set.insert(1);
    for(int cnt = 0; cnt < 1499; cnt++) {
        ll t = pq.top(); pq.pop();
        int a[] = {2, 3, 5};
        for(int i = 0; i < 3; i++) {
            ll val = t * a[i];
            if(!set.count(val)) set.insert(val), pq.push(val);
        }
    }
    printf("The 1500'th ugly number is %d.\n", pq.top());
    return 0;
}