#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

int g[52][52];

// 0 undicovered, 1 discovered, 2 processed
int st[52];

int ID(char a1, char a2) {
  return (a1 -'A') * 2 + (a2 == '+' ? 0 : 1);
}

void connect(char a1, char a2, char b1, char b2) {
    if(a1 == '0' || b1 == '0') return;
    int u = ID(a1, a2), v = ID(b1, b2) ^ 1; // u 能转换为 v符号相反的标号
    // printf("u:%d;v:%d\n", u, v);
    g[u][v] = true;
}

// return false if graph is not DAG
// means the topsort failed
bool dfs(int u) {
    st[u] = 1;
    for(int i = 0; i < 52; i++) 
        if(g[u][i]) {
            if(st[i] == 1) return false;
            if(!st[i] && !dfs(i)) return false;
        }
    st[u] = 2;
    return true;
}

bool is_cycle_exist() {
    memset(st, 0, sizeof(st));
    for(int i = 0; i < 52; i++) 
        if(!st[i]) if(!dfs(i)) return true;
    return false;
}

int main() {
  int n;
  while(scanf("%d", &n) != EOF && n) {
    memset(g, 0, sizeof(g));
    while(n--) {
      char s[10];
      scanf("%s", s);
      for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++) if(i != j)
          connect(s[i*2], s[i*2+1], s[j*2], s[j*2+1]);
    }
    if(is_cycle_exist()) puts("unbounded");
    else puts("bounded");
  }
  return 0;
}

 // 这道题，需要判断是否能组成无限大的结合物
// 不同的原子相连的条件是：字母相同，电性相反
// 观察几种集合物无限大的状况：
// 1. 一个原子在直线上自相连
// 2. 存在多个原子成同一直线自相连，其中一部分是循环（可能是两端，也可能是中间）
// 特别说明：不是连通分量的数量不必须是1，只要有其中一个连通分量无限大就够了
// 题目有个条件：正方形可以旋转或者翻转
// 有了这个条件，即便互相吸引的边缘，分布在相邻位置而不是相对位置，一个单原子也能自相连
// 所以，集合物无限大的情况就改变了：
// 1. 一个原子循环
// 2. 存在多个原子成同一直线自相连，其中一部分是循环（可能是两端，也可能是中间）
// 3. 存在多个原子相连，其中一部分是循环（可能是两端，也可能是中间）
// 显然，3种情况都有一个充分条件，存在循环！！！
// 也就是一个标号通过循环之后，转换成了自己

// 如何建模呢？
// 我们继续观察，例如，一个A+00A-00原子，它能通过自循环，无限扩大
// 原因是，A+ A- 能够连上 A+
// 也就是说，对于一对标号(x, y)，x能够连上的标号，或者说能够转换成的标号，由y决定

