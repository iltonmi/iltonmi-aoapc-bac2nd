#include <iostream>
#include <list>

using namespace std;

int main(void) {
    string str;
    while(cin >> str) {
        list<char> list;
        bool tail = true;
        auto itr = list.end();
        for(int i = 0; i < str.size(); i++) {
            char ch = str[i];
            if(ch == '[') itr = list.begin();
            else if(ch == ']') itr = list.end();
            else list.insert(itr, ch);
        }
        for(auto& ch : list) {
            putchar(ch);
        }
        puts("");
    }
    return 0;
}