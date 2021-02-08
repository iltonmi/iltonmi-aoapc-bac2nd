#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cstring>
#include <unordered_map>

using namespace std;

typedef pair<string, string> pss;
// 用链表，达到常量时间的插入和删除
list<int> shelf;
// idx即字符串id
vector<pss> v;
// 临时保存归还但未返架的图书
vector<int> returned;
// 根据字符串查id
unordered_map<string, int> map;

bool read_title(string& p) {
    int ch;
    while(ch = getchar(), ch != '\"' || ch != 'E') {
        if(ch == 'E') {getchar(), getchar(); return false;}
        else if(ch == '\"') break;
    }
    while(ch = getchar(), ch != '\"')
        p += ch;
    return true;
}

bool read_book() {
    int ch;
    string title;
    if(!read_title(title)) return false;
    string aut_name;
    while(ch = getchar(), ch != 'y');
    while(ch = getchar(), !isalpha(ch));
    aut_name += ch;
    while(ch = getchar(), ch != '\n' && ch != '\r')
        aut_name += ch;
    // cout << title << ":" << aut_name << endl;
    v.push_back({aut_name, title});
    return true;
}

void init_shelf() {
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++) {
        string title = v[i].second;
        shelf.push_back(i);
        map[title] = i;
    }
}

void borrow(const string& title) {
    int id = map[title];
    auto itr = find(shelf.begin(), shelf.end(), id);
    shelf.erase(itr);
}

void ret(const string& title) {
    returned.push_back(map[title]);
}

void shelve(int id) {
    auto itr = upper_bound(shelf.begin(), shelf.end(), id);
    if(itr == shelf.begin()) {
        printf("Put \"%s\" first\n", v[id].second.c_str()); 
        shelf.insert(itr, id);
    } else {
        printf("Put \"%s\" after \"%s\"\n", v[id].second.c_str(), v[*(--itr)].second.c_str());
        shelf.insert(++itr, id);
    }
}

void shelve_all() {
    sort(returned.begin(), returned.end());
    for(int i = 0; i < returned.size(); i++)
        shelve(returned[i]);
    returned.clear();
    puts("END");
}

// pss肯定要用来排序的，这个毫无疑问
int main(void) {
    while(read_book());
    init_shelf();
    char cmd[10];
    for(;;) {
        memset(cmd, 0, sizeof cmd);
        scanf("%s", cmd);
        if(cmd[0] == 'E') break;
        string p;
        if(cmd[0] == 'B') read_title(p), borrow(p);
        else if(cmd[0] == 'R') read_title(p), ret(p);
        else if(cmd[0] == 'S') shelve_all();
    }
    return 0;
}