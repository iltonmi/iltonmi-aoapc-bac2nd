#include <iostream>
#include <unordered_map>
#include <stack>
#include <cmath>

using namespace std;

typedef long long ll;

void solve(string& str) {
    stack<char> stk;
    unordered_map<ll, int> map;
    ll tmp = 0;
    for(int i = 0; i < str.size(); i++) {
        char ch = str[i];
        if(ch == '[') stk.push(ch);
        else if(ch == ',') {
            if(tmp != 0) {
                map[tmp * (ll)pow(2, stk.size())]++;
                tmp = 0;
            }
        } else if(ch == ']') {
            if(tmp != 0) {
                map[tmp * (ll)pow(2, stk.size())]++;
                tmp = 0;
            }
            stk.pop();
        } else if(isdigit(ch)) tmp = tmp * 10 + (ch - '0');
    }
    int maxcnt = 0, cnt = 0;
    for(auto& t : map) {
        if(t.second > maxcnt) maxcnt = t.second;
        cnt += t.second;
    }
    printf("%d\n", cnt - maxcnt);
}

int main(void) {
    int T; scanf("%d\n", &T);
    while(T--) {
        string str; 
        getline(cin, str);
        solve(str);
    }
    return 0;
}

// https://www.luogu.com.cn/blog/goucw/solution-uva12166
// 用m代替最小的质量，画出几个天平，观察发现：
// 在一个平衡的天平中，所有物品的重量weight 乘 2 ** depth之后，数值相等
// 问题就变成了，寻找weight 乘 2 ** depth之后，数值相等的数量
// 这个数量就是满足要求的数量，那么总数量 - 数值相等的数量 = 答案：需要修改重量的数量
// 这道题的关键是，通过作图，观察到平衡的天平里物品重量之间的关系
// 如果问最小重量，那么就是数值 / 2 ** max depth

// 启发：所以说动手画图真的很重要！！！

// 那么问题来了：如何解析表达式，准确找到每个数值的深度呢？
// [[1, 2], 6]
// [[[1, 2], 2], 3]
// [[[1, 2], [3, [2, 6]]], 7]
// 使用栈，遍历表达式字符
// 遇到[直接入栈
// 遇到整数，depth == stk.size
// 遇到,跳过
// 遇到]，stk.pop()