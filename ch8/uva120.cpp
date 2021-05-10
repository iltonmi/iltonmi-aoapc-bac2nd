#include <iostream>
#include <algorithm>
#include <queue>
#include <sstream>
using namespace std;

const int maxn = 100;
int n;
int arr[maxn+1];

void flip(int i) {
    int l = i, r = n;
    while(l < r) swap(arr[l++], arr[r--]);
}

bool read_input() {
    string s;
    if(!getline(cin, s)) return false;
    cout << s << endl;
    stringstream ss(s);
    int t;
    n = 0;
    while(ss >> t) arr[++n] = t;
    flip(1);
    return true;
}

void solve() {
    // find unprocessed max val
    // its pos has 3 conditions:
    // 1. at correct pos: do nothing
    // 2. at top: flip to correct pos
    // 3. at mid: flip to top, then flip to correct pos
    priority_queue<int> heap;
    for(int i = 1; i <= n; i++) heap.push(arr[i]);
    for(int i = 1; i <= n; i++) {
        int t = heap.top(); heap.pop();
        int k = i;
        while(arr[k] != t) k++;
        if(k != i) {
            if(k == n) flip(i), printf("%d ", i);
            else flip(k), flip(i), printf("%d %d ", k, i);
        }
    }
    printf("0\n");
}

int main(void) {
    while(read_input()) solve();
    return 0;
}