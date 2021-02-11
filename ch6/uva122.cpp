#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

// 将path排个序，可以发现，左子树的node会在右子树前面，而且父节点会在子节点前面
// path长度相同的在同一层
// 长度相同的排个序，就是正确的层次遍历顺序
// 如何判断path给了重复值？path相同
// 如何判断path没给？某个path的前缀不存在

// 1. psi存起来
// 2. 扔进set查重
// 3. 枚举前缀
// if complete
// 排序输出
// else print "not complete"
#define x first
#define y second
typedef pair<string, int> psi;

// 长度小的层次比较浅
// 长度相同的，比字典序
int cmp(const psi& t1, const psi& t2) {
    if(t1.x.size() != t2.x.size()) return t1.x.size() < t2.x.size();
    else return t1.x < t2.x;
}

bool solve() {
    vector<psi> v;
    for(;;) {
        char ch;
        while(ch = getchar(), isspace(ch));
        if(ch == EOF) return false;
        ch = getchar();
        if(ch == ')') break;
        int val = ch - '0';
        while(ch = getchar(), ch != ',') 
            val = val * 10 + (ch - '0');
        string path;
        while(ch = getchar(), ch != ')')
            path += ch;
        v.push_back({path, val});
    }
    // for(int i = 0; i < v.size(); i++) 
    //     cout << v[i].first << ":" << v[i].second << ' ';
    // cout << endl;
    set<string> pset;
    for(int i = 0; i < v.size(); i++) {
        auto& t = v[i].x;
        if(pset.count(t)) {
            puts("not complete");
            return true;
        }
        pset.insert(t);
    }
    for(int i = 0; i < v.size(); i++) {
        auto& t = v[i].x;
        for(int len = 0; len < t.size(); len++)
            if(!pset.count(t.substr(0, len))) {
                puts("not complete");
                return true;
            }
    }
    sort(v.begin(), v.end(), cmp);
    for(int i = 0; i < v.size(); i++) {
        auto& t = v[i];
        printf(i > 0 ? " %d" : "%d", v[i].y);
    }
    puts("");
    return true;
}

int main(void) {
    while(solve());
    return 0;
}