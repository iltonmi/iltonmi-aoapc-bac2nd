#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;
int cnt1[26], cnt2[26];

int main() {
    string enc;
    string ori;
    while(cin >> enc) {
        cin >> ori;
        memset(cnt1, 0, sizeof cnt1);
        memset(cnt2, 0, sizeof cnt2);
        int n = ori.size();
        for(int i = 0; i < n; i++)
            cnt1[enc[i] - 'A']++;
        for(int i = 0; i < n; i++)
            cnt2[ori[i] - 'A']++;
        sort(cnt1, cnt1 + 26);
        sort(cnt2, cnt2 + 26);
        bool flag = true;
        for(int i = 0; i < 26 && flag; i++) 
            if(cnt1[i] != cnt2[i]) flag = false;
        printf(flag ? "YES\n" : "NO\n");
    }
    return 0;
} 