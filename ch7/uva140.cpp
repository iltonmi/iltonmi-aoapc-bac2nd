#define LOCAL
#include <iostream>
#include <cstring>
#include <map>

using namespace std;

bool g[10][10];
int nnode, ans;
char names[10];
map<char, int> nums;
string path, fpath;
bool used[10];

// 依然是编号的思想，很重要很重要
int NO(char c) {
    if(nums.count(c)) return nums[c];
    names[nnode] = c;
    nums[c] = nnode;
    return nnode++;
}

bool handle_input() {
    nums.clear();
    nnode = 0;
    memset(g, 0, sizeof(g));
    int ch;
    while(ch = getchar(), !isalpha(ch) && ch != '#');
        ;
    if(ch == '#') return false;
    do {
        int no = NO(ch);
        getchar();
        while((ch = getchar()) != ';' && !isspace(ch)) {
            int to = NO(ch);
            g[no][to] = g[to][no] = true;
        }
        if(ch == ';') ch = getchar();
    } while(isalpha(ch));
    return true;
}

void dfs(int x, int pre) {
    if(used[x]) return;
    int t = 0;
    int n = path.size();
    for(int j = 0; j < n; j++) {
        int y = NO(path[j]);
        if(g[x][y] && n - j > t) 
            t = n - j;
    }
    if(t > ans) return;
    
    if(t > pre) pre = t;
    used[x] = true;
    path.push_back(names[x]);
    if(path.size() == nnode) {
        if(pre < ans) ans = pre, fpath = path;
        if(pre == ans && path < fpath) fpath = path;
    }
    // 如果是等待再下一次递归再记录path，会导致不必要的递归
    for(int i = 0; path.size() < nnode && i < nnode; i++)
        dfs(i, pre);
    used[x] = false;
    path.pop_back();
}

int main(void) {
    #ifdef LOCAL
        freopen("uva140.in", "r", stdin);
        freopen("uva140.out", "w", stdout);
    #endif
    while(handle_input()) {
        ans = nnode;
        memset(used, 0, sizeof(used));
        path.clear();
        for(int i = 0; i < nnode; i++)
            dfs(i, 0);
        for(int i = 0; i < nnode; i++)
            printf(i > 0 ? " %c" : "%c", fpath[i]);
        printf(" -> %d\n", ans);
    }
    return 0;
}

// DFS穷举(不是哈密顿路径), 计算并比较bandwith of ordering, 保存最小的
// 剪枝条件：1. 当前bandwith已经等于min val 2. 当前节点的未访问节点数 + 当前bandwith = min val
// 给每个节点一个编号
// 稀疏图，用邻接链表表示
// 枚举所有的节点编号为起点，遍历记录path，中途剪枝，最后记录