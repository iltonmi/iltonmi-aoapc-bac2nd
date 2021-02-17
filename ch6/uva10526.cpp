#define LOCAL
#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 210;
int n;
char buf[maxn][maxn];

bool is_node_label(char ch) {
    // emmmm，题目数据和题面不一样，题目数据是允许#表示节点的
    return isprint(ch) && ch != ' ' && ch != '-' && ch != '|';
}

void dfs(int sx, int sy) {
    printf("%c(", buf[sx][sy]);
    if(sx + 1 >= n || buf[sx + 1][sy] != '|') {putchar(')'); return;}
    int x = sx + 2, y = sy;
    while(y - 1 >= 0 && buf[x][y - 1] == '-') y--;
    while(buf[x][y] == '-' && buf[x + 1][y]) {
        char ch = buf[x + 1][y];
        if(is_node_label(ch)) dfs(x + 1, y);
        y++;
    }
    putchar(')');
}

void solve() {
    n = 0;
    for(;;) {
        fgets(buf[n], maxn, stdin);
        if(buf[n][0] == '#') break;
        else n++;
    }
    putchar('(');
    if(n) {
        for(int i = 0; i < strlen(buf[0]); i++)
            if(buf[0][i] != ' ') {dfs(0, i); break;}
    }
    printf(")\n");
}

int main(void) {
    #ifdef LOCAL
        freopen("uva10526.in", "r", stdin);
        freopen("uva10526.out", "w", stdout);
    #endif
    int T;
    fgets(buf[0], maxn, stdin);
    sscanf(buf[0], "%d", &T);
    while(T--) solve();
    return 0;
}

// 构建一颗多叉树做DFS
// 如何将文本解析为一棵树

// 方案1：构建树后做DFS
// 读取节点，读取节点下一行
// 如果节点下一行的首字符是#，说明这棵树构建完成
// 否则，说明这一层的节点，有孩子节点
// 记录下方有竖线的节点！！！
// 读取一行横线，一行字符
// 第x段横线下的字符，对应第x个下方有竖线的节点的子节点

// 初始化，将根节点放入队列
// 队列保存，从左到右有孩子的上层节点
// 读取后续3行，遍历当前队列中的元素，对每个元素做以下的事情：
// 在第一行中确定一段横线的范围，在第二行中读入横线下的字符作为子节点
// 如果第3行首字符不是#，那么还要判断每个子节点下方是否竖线，如果有说明有子节点，放入队列

// 方案2 from Rujia Liu：读取每棵树到2-d数组，递归处理数组，生成字符串