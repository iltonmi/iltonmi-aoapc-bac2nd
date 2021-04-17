#define LOCAL
#include <iostream>
#include <string>

using namespace std;

int count(string& s) {
    int ans = 0;
    for(int i = 0; i < s.size(); i++) {
        if(i + 1 < s.size() && s[i + 1] != s[i] + 1) 
            ans++;
    }
    if(s.back() != ('0' + s.size())) ans++;
    return ans;
}

// int solve(string& s) {
//     unordered_map<string, int> map;
//     queue<pis> q;
//     map[s] = 0;
//     q.push({count(s), s});
//     while(q.size()) {
//         auto t = q.front(); q.pop();
//         if(t.first == 0) return map[t.second];
//         auto str = t.second;
//         for(int i = 0; i < str.size(); i++) {
//             for(int j = i + 1; j <= str.size(); j++) {
//                 auto rest = str.substr(0, i) + str.substr(j);
//                 for(int k = 1; k <= rest.size(); k++) {
//                     auto nx = rest.substr(0, k) + str.substr(i, j - i) + rest.substr(k);
//                     int d = map[str] + 1, h = count(nx);
//                     if(!map.count(nx)) {
//                         map[nx] = d;
//                         q.push({h, nx});
//                     }
//                 }
//             }
//         }
//     }
//     return -1;
// }

bool dfs(string& str, int maxd, int d) {
    int h = count(str);
    if(3 * maxd < h + 3 * d) return false;
    if(h == 0) return true;
    for(int i = 0; i < str.size(); i++) {
        for(int j = i + 1; j <= str.size(); j++) {
            auto rest = str.substr(0, i) + str.substr(j);
            for(int k = 1; k <= i; k++) {
                auto nx = rest.substr(0, k) + str.substr(i, j - i) + rest.substr(k);
                if(dfs(nx, maxd, d + 1)) return true;
            }
        }
    }
    return false;
}

int main(void) {
    #ifdef LOCAL
        freopen("uva11212.in", "r", stdin);
        freopen("uva11212.out", "w", stdout);
    #endif
    int n;
    int rnd = 0;
    while(scanf("%d", &n), n) {
        string s;
        int t;
        for(int i = 0; i < n; i++) 
            scanf("%d", &t), s += to_string(t);
        int ans = 0;
        if(count(s) != 0) {
            for(int i = 1; i < n; i++) {
                if(dfs(s, i, 0)) {
                    ans = i; break;
                }
            }
        }
        printf("Case %d: %d\n", ++rnd, ans);
        // printf("Case %d: %d\n", ++rnd, solve(s));
    }
    return 0;
}

// 看了书本
// 假设还有h个数字的后继数字无效，又每次最多3个数字恢复正常
// 所以，后续至少h / 3步
// 若h / 3 + d > maxd，则剪枝

// 字符串是一个状态state
// 对于每个state，找到连续的片段，然后找到正确的2个位置，生成2个新状态
// 对于每个状态，记录有多少个后续数字有问题