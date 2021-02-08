#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

// 很显然这题只能枚举了，但是枚举的方法有2种
// 1. 将字典中的词，全部22组合，时间复杂度达到了1e10，爆定了
// 2. 枚举全部词，对每个词进行分割，然后查询分割后的2部分是否都在字典中，最坏情况下，如果每个字符串长度都是
// 1e5，时间复杂度才会达到1e10
int main(void) {
    vector<string> v;
    unordered_set<string> set;
    string t;
    while(cin >> t) v.push_back(t), set.insert(t);
    for(auto& s : v) {
        for(int i = 0; i < s.size(); i++) 
            if(set.count(s.substr(0, i)) && set.count(s.substr(i))) {
                puts(s.c_str()); break;
            }
    }
    return 0;
}