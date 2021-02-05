#include <iostream>
#include <sstream>
#include <set>

using namespace std;

set<string> dict;

// 也可以用cin >> str后，将str中非字母修改成space
// 再将str扔进stringstream, 然后ss >> str
bool read_word() {
    string word;
    char ch;
    while((ch = getchar()) != EOF && !isalpha(ch));
    if(ch == EOF) return false;
    do word += tolower(ch); 
    while(ch = getchar(), isalpha(ch));
    if(word.size()) dict.insert(word);
    return word.size();
}

bool read_word2() {
    string word; cin >> word;
    for(int i = 0; i < word.size(); i++) 
        if(isalpha(word[i])) word[i] = tolower(word[i]);
        else word[i] = ' ';
    stringstream ss(word);
    bool flag = false;
    while(ss >> word) flag = true, dict.insert(word);
    return flag;
}

int main(void) {
    string str;
    while(read_word());
    for(auto& str : dict)
        cout << str << endl;
    return 0;
}