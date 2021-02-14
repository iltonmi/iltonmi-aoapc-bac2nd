#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

bool g[26][26], visited[26][26];
char word[1010];
int deg[26];

bool dfs(int u) {
    bool ans = false;
    for(int i = 0; i < 26; i++)
        if(g[u][i] && !visited[u][i]) {
            visited[u][i] = true;
            ans = true;
            dfs(i);
        }
    return ans;
}

int main(void) {
    int T; scanf("%d", &T);
    while(T--) {
        int n; scanf("%d", &n);
        memset(g, 0, sizeof(g));
        memset(deg, 0, sizeof(deg));
        memset(visited, 0, sizeof(visited));
        for(int i = 0; i < n; i++) {
            scanf("%s", word);
            int size = strlen(word);
            int ch1 = word[0] - 'a', ch2 = word[size - 1] - 'a';
            g[ch1][ch2] = true;
            deg[ch1]--, deg[ch2]++;
        }
        int cnt = 0;
        for(int i = 0; i < 26; i++) 
            if(dfs(i)) cnt++;

        vector<int> v;
        for(int i = 0; i < 26; i++)
            if(deg[i] != 0) v.push_back(deg[i]);
        sort(v.begin(), v.end());
        bool flag = false;
        if(v.size() == 0) flag = true;
        if(v.size() == 2 && v[0] == -1 && v[1] == 1) flag = true;
        if(cnt != 1) flag = false;
        if(flag) puts("Ordering is possible.");
        else puts("The door cannot be opened.");
    }
    return 0;
}