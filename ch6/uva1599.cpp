#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int N = 1e5 + 10, M = 4e5 + 10;

int h[N], e[M], ne[M], color[M], idx;
int n, m;
int dist[N];
bool used[N];

void init() {
    memset(h, -1, sizeof(h));
    idx = 0;
    memset(dist, -1, sizeof(dist));
}

void insert(int a, int b, int c) {
    e[idx] = b, color[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void rev_bfs() {
    memset(used, 0, sizeof(used));
    dist[n] = 0;
    used[n] = true;
    queue<int> q;
    q.push(n);
    while(q.size()) {
        auto t = q.front(); q.pop();
        for(int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if(!used[j]) {
                dist[j] = dist[t] + 1;
                used[j] = true;
                q.push(j);
            }
        }
    }    
}

void bfs() {
    vector<int> ans;
    vector<int> v;
    v.push_back(1);
    memset(used, 0, sizeof(used));
    used[1] = true;
    for(int i = 0; i < dist[1]; i++) {
        // 因为我们需要的是color而已，所以即使在某一层有多条边的color相同
        // 也不影响当前层结果
        // 只需要将所有边color相同的终点保存起来，以便寻找下一层的最小color
        int minc = 1e9 + 1;
        for(int k = 0; k < v.size(); k++) {
            int t = v[k];
            for(int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if(dist[j] == dist[t] - 1 && color[i] < minc) {
                    minc = color[i];
                }
            }
        }
        ans.push_back(minc);
        vector<int> v2;
        int tsize = v.size();
        for(int k = 0; k < v.size(); k++) {
            int t = v[k];
            for(int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if(dist[j] == dist[t] - 1 && !used[j] && color[i] == minc) 
                    used[j] = true, v2.push_back(j);
            }
        }
        v = v2;
    }
    printf("%d\n", ans.size());
    for(int i = 0; i < ans.size(); i++) 
        printf(i > 0 ? " %d" : "%d", ans[i]);
    puts("");  
}

int main(void) {
    while(scanf("%d%d", &n, &m) == 2) {
        init();
        for(int i = 0; i < m; i++) {
            int a, b, c; scanf("%d%d%d", &a, &b, &c);
            insert(a, b, c), insert(b, a, c);
        }
        rev_bfs();
        bfs();
    }
    return 0;
}

// 无权最短路，第一反应是BFS
// 按照题目要求，要找出所有的最短路
// BFS的停止条件是，全部点都已经遍历过了
// BFS进入队列的条件是，点到起点的距离未被更新

// 下一个问题是：如何找到字典序最小的路径呢？
// 第一反应：按照层次遍历，每次只选择dist + 1的点中字典序最小的一个
// 问题是：很可能存在一条到达其他点的路径，比到达终点的路径字典序更小
// 因此，寻找路径的时候，应该从终点开始，每次只选择dist - 1的点中，字典序更大还是更小的一个呢？
// 没有意义，因为我们需要比较的是从起点开始的字典序，而不是终点开始的

// 反过来想一想，BFS从1到N和从N到1，1和N之间的最短路是不变的
// 如果从N到1做BFS，然后从1开始层次遍历，每次只选择dist + 1的点中，字典序更小的一个，就看可以找到答案了

// 自作聪明地想了很久，如何只需要一次BFS？浪费了很多时间都没想出来，还是功力不够。。。
// 还是要注意控制时间，不然就失去了做题的意义