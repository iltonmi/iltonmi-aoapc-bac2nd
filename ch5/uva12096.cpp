#include <iostream>
#include <algorithm>
// 这题不能用unordered系列容器
// #include <unordered_set>
// #include <unordered_map>
#include <vector>
#include <map>
#include <set>
#include <stack>

using namespace std;

// 第一想法是，用一个结构体表示集合
// struct Set {int size; Set* a[N]}
// 对于pointer like class, 我们还需要重写适当的copy ctor和dtor
// 显然这很没必要
// 所以，我们可以模拟这个结构体和指针
// 用一个数组保存全部Set，idx就是Set的指针
// （这个模拟指针的方法，有很多用处，模拟HashMap，linked-list都很有用）
// 而Set中，保存了Set中子集的idx 
// 因此，利用STL中的set<int>，就可以解决复制和销毁的时候内存管理的问题
// set.size()就是cardinality

#define ALL(x) x.begin(),x.end()

typedef set<int> Set;
vector<Set> v;
// 保证同样构造的Set是唯一的
map<Set, int> set_ids;
stack<int> stk;

int id(const Set& x) {
    if(set_ids.count(x)) return set_ids[x];
    v.push_back(x);
    return set_ids[x] = v.size() - 1;
}

int main(void) {
    int w; cin >> w;
    for(int i = 0; i < w; i++) {
        int n; cin >> n;
        while(n--) {
            string cmd; cin >> cmd;
            if(cmd == "PUSH") stk.push(id(Set()));
            else if(cmd == "DUP") stk.push(id(v[stk.top()]));
            else {
                int a = stk.top(); stk.pop();
                int b = stk.top(); stk.pop();
                Set res;
                if(cmd == "UNION") 
                    set_union(ALL(v[a]), ALL(v[b]), inserter(res, res.begin()));
                else if(cmd == "INTERSECT")
                    set_intersection(ALL(v[a]), ALL(v[b]), inserter(res, res.begin()));
                else if(cmd == "ADD")
                    res = v[b], res.insert(a);
                stk.push(id(res));
            }
            printf("%d\n", v[stk.top()].size());
        }
        printf("***\n");
    }
    return 0;
}