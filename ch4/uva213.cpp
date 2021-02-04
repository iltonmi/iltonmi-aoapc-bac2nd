#include <iostream>
#include <cmath>

using namespace std;

int read_len() {
    int len = 0;
    for(int i = 0; i < 3; i++) {
        char ch;
        while(ch = getchar(), ch != '0' && ch != '1');
        len = len * 2 + (ch - '0');
    }
    return len;
}

int get_idx(string& pat) {
    int cnt = 0;
    for(int i = 1; i < pat.size(); i++) {
        for(int j = 0; j < (int)pow(2, i) - 1; j++)
            cnt++;
    }
    int num = 0;
    for(int i = 0; i < pat.size(); i++)
        num = num * 2 + (pat[i] - '0');
    return num + cnt;
}

bool read_header(string& header) {
    char ch;
    while(ch = getchar(), ch == '\n' || ch == '\r');
    if(ch == EOF) return false;
    header += ch;
    while(ch = getchar(), ch != '\n' && ch != '\r') {
        header += ch;
    }
    return true;
}

int main(void) {
    string header;
    while(read_header(header)) {
        cout << header << endl;
        int len = 0;
        string ans;
        while(len = read_len(), len) {
            while(true) { 
                string pat;
                bool flag = false;
                for(int i = 0; i < len; i++) {
                    char ch;
                    while(ch = getchar(), ch != '0' && ch != '1');
                    pat += ch;
                    if(ch == '0') flag = true;
                }
                if(flag) ans += header[get_idx(pat)];
                else break;
            }
        }
        cout << ans << endl;
        header.clear();
    }
    return 0;
}
