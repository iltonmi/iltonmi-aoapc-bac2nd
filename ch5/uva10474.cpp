#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int main(void) {
    int n, q;
    for(int cnt = 1; cin >> n >> q && n; cnt++) {
        vector<int> v;
        for(int i = 0, t; i < n; i++)
            cin >> t, v.push_back(t);
        sort(v.begin(), v.end());
        printf("CASE# %d:\n", cnt);
        for(int i = 0; i < q; i++) {
            int t; cin >> t;
            auto itr = find(v.begin(), v.end(), t);
            if(itr == v.end()) printf("%d not found\n", t);
            else printf("%d found at %d\n", t, (itr - v.begin()) + 1);
        }
    }
    return 0;
}