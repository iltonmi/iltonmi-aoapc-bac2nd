#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int p[26], deg[26];
bool used[26];
char word[1010];

char find(int x) {
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void union_set(int a, int b) {
    p[find(a)] = p[find(b)];
}

void init() {
    for(int i = 0; i < 26; i++) p[i] = i;
    memset(used, 0, sizeof(used));
    memset(deg, 0, sizeof(deg));
}

int main(void) {
    int T; scanf("%d", &T);
    while(T--) {
        int n; scanf("%d", &n);
        init();
        int cnt = 26;
        for(int i = 0; i < n; i++) {
            scanf("%s", word);
            int size = strlen(word);
            int ch1 = word[0] - 'a', ch2 = word[size - 1] - 'a';
            if(find(ch1) != find(ch2)) cnt--, union_set(ch1, ch2);
            used[ch1] = used[ch2] = true;
            deg[ch1]--, deg[ch2]++;
        }
        for(int i = 0; i < 26; i++)
            if(!used[i]) cnt--;
        // printf("cnt : %d\n", cnt);
        vector<int> v;
        for(int i = 0; i < 26; i++)
            if(deg[i] != 0) v.push_back(deg[i]);
        sort(v.begin(), v.end());
        // for(int i = 0; i < v.size(); i++) 
        //     printf("%d\n", v[i]);
        bool flag = false;
        if(v.size() == 0) flag = true;
        if(v.size() == 2 && v[0] == -1 && v[1] == 1) flag = true;
        if(cnt != 1) flag = false;
        if(flag) puts("Ordering is possible.");
        else puts("The door cannot be opened.");
    }
    return 0;
}

// 这道题，要求将全部单词首尾相接
// 首先，全部相接 ，说明这些词共同组成一个连通分量
// 第二，要确保整个连通分量，单词之间在数量上，按照首尾相接的要求一一对应

// 1. 统计连通分量数量，可以用DFS或者并查集
// 2. 这是一个经典的欧拉道路问题，也叫“一笔画”，
// 在有向图中，它的充分条件是：
// 1. 忽略边的方向时，图是连通的
// 2. 有且只有2个点的出度不等于入度，一个出度比入度大1，另一个出度比入度小1

// 方案1：并查集
// 将26个字母看作一个点，单词看作有向边
// 初始有26个连通分量
// union被边连接的点
// 最终连通分量数量 = 连通分量数量 - 孤点数量

// 构建并查集的过程中，记录每个点的出度和入度
// 最后，统计出入度之差非0的点的数量

// 方案2：DFS
// 统计连通分量：DFS一次任意点，判断是否存在未被遍历的点
// 统计出入度：构建图时，统计出入度