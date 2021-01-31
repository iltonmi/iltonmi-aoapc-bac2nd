#include <iostream>
#include <cstring>

using namespace std;

int chance, rest;
bool win, lose;

void guess(string& str1, string& str2, int idx) {
    char ch = str2[idx];

    bool valid = false;
    for(int i = 0; i < str1.size(); i++) 
        if(ch == str1[i]) rest--, str1[i] = ' ', valid = true;
    
    if(!valid) chance--;
    if(!rest) win = true; 
    if(!chance) lose = true;
}

int main() {
    int rnd;
    while(cin >> rnd, rnd != -1) {
        string str1, str2;
        cin >> str1 >> str2;
        win = lose = false;
        chance = 7, rest = str1.size();
        for(int i = 0; i < str2.size(); i++) {
            guess(str1, str2, i);
            if(win || lose) break;
        }
        string ans;
        printf("Round %d\n", rnd);
        if(win) ans = "You win.";
        else if(lose) ans = "You lose.";
        else ans = "You chickened out.";
        cout << ans << endl;
    }
    return 0;
}