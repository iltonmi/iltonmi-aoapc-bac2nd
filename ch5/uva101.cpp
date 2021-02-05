#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// 用vector array模拟操作
// 用一个array保存block当前所在的位置
// 所有的操作，可以分解为以下的操作
// 1. 将block i上方的block move to original pos
// 2. 移动block i到指定位置
// 3. 移动block i及其上方的block到指定位置
// 无论如何移动，只在放置的时候更新pos
// 解析命令：
// move or pile决定了a上方的block是否需要还原
// onto or over决定了b上方的block是否需要还原
// 先读取move or pile
// if move, pop的过程中，还原上方block(update pos)
// if pile, pop的过程中，用stack存储
// 读取onto or over
// if onto, pop的过程中，还原上方block(update pos)
// if over, 不用动b所在的pile
// finally, pop stack, push_back to vector and update pos

const int N = 30;
int pos[N];
vector<int> a[N];
stack<int> stk;
int n;

void recover_above(int pi, int x) {
    for(int t = a[pi].back(); t != x; t = a[pi].back()) {
        a[pi].pop_back();
        a[t].push_back(t), pos[t] = t;
    }
}

int main(void) {
    cin >> n;
    for(int i = 0; i < n; i++)
        a[i].push_back(i), pos[i] = i;
    string cmd1, cmd2;
    while(cin >> cmd1, cmd1 != "quit") {
        int from, to;
        cin >> from >> cmd2 >> to;
        int pf = pos[from], pt = pos[to];
        if(from == to || pf == pt) continue;
        if(cmd1 == "move") {
            recover_above(pf, from); 
            stk.push(a[pf].back()); 
            a[pf].pop_back();
        } else if(cmd1 == "pile") {
            while(true) {
                int t = a[pf].back(); a[pf].pop_back();
                stk.push(t);
                if(t == from) break;
            }
        }
        if(cmd2 == "onto") recover_above(pt, to);
        while(stk.size()) {
            int t = stk.top(); stk.pop();
            a[pt].push_back(t), pos[t] = pt;
        }
    }
    for(int i = 0; i < n; i++) {
        printf("%d:", i);
        for(int j = 0; j < a[i].size(); j++)
            printf(" %d", a[i][j]);
        puts("");
    }
    return 0;
}