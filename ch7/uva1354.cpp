#define LOCAL
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <ctime>

using namespace std;

typedef struct Tree {
    double L, R;
    Tree() : L(0), R(0) {}
} Tree;

const int maxn = 6;
double r;
int s, sto[maxn], sum[1 << maxn];
vector<Tree> trees[1 << maxn];
bool vis[1 << maxn];

void dfs(int subset) {
    if(vis[subset]) return;
    vis[subset] = true;
    if(!(subset&(subset - 1))) {
        trees[subset].push_back(Tree());
        return;
    }
    // 讲解一下如何用位运算枚举子集：
    // 2个核心：1. 通过left - 1不断枚举小于subset的数 2. 通过&与运算，去除冗余的状态
    // 前者保证不漏，后者保证不重
    for(int left = subset&(subset - 1); left; left = (left-1) & subset) {
        int right = subset ^ left;
        dfs(left); dfs(right);
        double dl = (double)sum[right] / sum[subset];
        double dr = (double)sum[left] / sum[subset];
        for(auto& lt : trees[left]) {
            for(auto& rt : trees[right]) {
                Tree t;
                // 小细节。。。。。。
                t.L = max(lt.L + dl, rt.L - dr);
                t.R = max(rt.R + dr, lt.R - dl);
                if(t.L + t.R < r) trees[subset].push_back(t);
            }
        }
    }
}

int main(void) {
    #ifdef LOCAL
        freopen("uva1354.in", "r", stdin);
        freopen("uva1354.out", "w", stdout);
    #endif
    int T;
    auto startt = clock();
    scanf("%d", &T);
    while(T--) {
        scanf("%lf%d", &r, &s);
        for(int i = 0; i < s; i++) scanf("%d", &sto[i]);
        // 提前计算好重量
        for(int i = 0; i < (1 << s); i++) {
            trees[i].clear();
            sum[i] = 0;
            for(int j = 0; j < s; j++)
                if(i & (1 << j)) sum[i] += sto[j];
        }
        memset(vis, 0, sizeof(vis));
        int fullset = (1 << s) - 1;
        dfs(fullset);
        double ans = -1.0;
        for(auto& val : trees[fullset])
            ans = max(ans, val.L + val.R);
        printf("%.15lf\n", ans);
    }
    auto endt = clock();
    cout << "Totle Time : " <<(double)(endt - startt) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}


// 枚举所有可能的风铃
// 一个节点，可能是石头或者风铃
// 子节点，要么有2个，要么无
// 
// 如果一个节点是石头，如何判断是否有效呢？
// 是没办法的，因为无法知道sibling的重量
// 如果一个节点是否风铃，如何判断是否有效呢？
// 也是没办法的，不仅不知道sibling的重量，甚至都无法知道自己的重量
// 
// 以上思路，听起来就很麻烦。。。
//
// 可不可以直接枚举各种可能的二叉树，然后验证二叉树的平衡性和宽度呢？
// 通过后序遍历，能够获得左右子节点的重量，由此可以判断平衡性
// 如果不平衡，则当前二叉树无效
// 如果平衡，则告知上一级重量
// 那么，宽度如何判断呢？返回左右宽度到上一级
// 上一级可以由此计算出上一级的左右宽度
// 
// 这个平衡性似乎没有意义，去掉。
// 所以就是枚举二叉树并且回溯得到宽度
// 要求是使用所有的石头，并且宽度要小于房间
// 
// 那么，如何枚举二叉树呢？
// 我确实不会做。。。确实菜。。。
// 所以去看了rujia liu的题解，以及力扣上一道叫All Possible Full Binary Trees的题目
// APFBT这道题目呢，只规定了枚举所有树的形态，但递归和子集的思想上和rujia liu的是一样的
// 那除了思想上，解法上有什么不同呢？
// 因为这道题规定的不只是树的形态，还规定了叶子节点的值必须是石头的值
// 因此不能像枚举二叉树形态一样，只需要节点数量作为参数，而是还需要知道对应的具体节点子集
// 
// 所以说，递归函数的入参，就是节点的子集
// 然后，将这个子集分为2个非空子集（非空，因为题目要求风铃的两边必须不能为空）
// 递归调用这两个非空子集，保留他们每个可能的最大左右距离（因为左右子集也是有多种形态的）
// 由于子集是已知的，就能算出当前风铃两边的长度，
// 再结合递归调用的结果，算出当前子集的所有可能性