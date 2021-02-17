#define LOCAL

#include <iostream>
#include <unordered_map>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// 输出：
// 所有命令都需要echo
// INSTALL命令：1. 按照依赖逆序installing; 2. alredy installed
// REMOVE命令：1. 按照依赖顺序Removing; 3. still needed
// 被implictly installed的软件，不能使用REMOVE命令显示删除

// 为每个软件分配一个ID
// status表示软件的安装状态
// 保存 被依赖软件 -> 依赖软件 的图，INSTALL的时候可以用来按顺序检查和安装所需的软件
// REMOVE需要逆序删除，因此需要保存 依赖软件 -> 被依赖软件的图

const int N = 10010;

unordered_map<string, int> itemidmap;
vector<string> vec;

vector<int> depend[N];
int depcnt[N], status[N];
vector<int> installed;

int ID(string s) {
    if(!itemidmap.count(s)) vec.push_back(s), itemidmap[s] = vec.size() - 1;
    return itemidmap[s];
}

void add_dep(int a, int b) {
    depend[a].push_back(b);
}

// 
void install(int id, int st) {
    if(status[id]) return;
    for(int i = 0; i < depend[id].size(); i++) {
        int tid = depend[id][i];
        if(!status[tid]) install(tid, 2);
        depcnt[tid]++;
    }
    status[id] = st;
    printf("   Installing %s\n", vec[id].c_str());
    installed.push_back(id);
}

// 未安装的软件被显式删除，提示未安装
// 安装的软件被显式删除，如果depcnt > 0，删除失败
// 安装的软件被隐式删除，如果depcnt == 0，status == 2
void remove(int id, int st) {
    // 显式删除，需要检查depcnt，如果 > 0，删除失败
    // 否则，删除，并且更新那些被当前软件依赖的软件
    // 若某个被依赖软件 --depcnt == 0 && status == 2，那么递归的删除这个软件
    if(depcnt[id] > 0 || !status[id]) return;
    status[id] = 0;
    installed.erase(remove(installed.begin(), installed.end(), id), installed.end());
    printf("   Removing %s\n", vec[id].c_str());
    for(int i = 0; i < depend[id].size(); i++) {
        int tid = depend[id][i];
        if(--depcnt[tid] == 0 && status[tid] == 2) remove(tid, 2);
    }
}

void list_items() {
    for(auto& t : installed)
        printf("   %s\n", vec[t].c_str());
}

int main(void) {
    #ifdef LOCAL
        freopen("uva506.in", "r", stdin);
        freopen("uva506.out", "w", stdout);
    #endif
    string cmd;
    string iname;
    string line;
    while(getline(cin, line)) {
        cout << line << endl;
        stringstream ss(line);
        ss >> cmd;
        if(cmd[0] == 'E') break;
        if(cmd[0] == 'D') {
            ss >> iname;
            int aid = ID(iname);
            while(ss >> iname) {
                int bid = ID(iname);
                add_dep(aid, bid);
            }
        } else if(cmd[0] == 'I') {
            ss >> iname;
            int id = ID(iname);
            if(status[id]) printf("   %s is already installed.\n", vec[id].c_str());
            else install(id, 1);
        } else if(cmd[0] == 'R') {
            ss >> iname;
            int id = ID(iname);
            if(!status[id]) printf("   %s is not installed.\n", vec[id].c_str());
            else if(depcnt[id] > 0) printf("   %s is still needed.\n", vec[id].c_str());
            else remove(id, 1);
        } else if(cmd[0] == 'L') {
            list_items();
        }
    }
    return 0;
}