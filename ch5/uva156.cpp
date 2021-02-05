#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

// 重要的是，如何判断2个字符是否互为anangrams
// 变为小写字母，并排序
string normalize(string& str) {
    string ans;
    for(int i = 0; i < str.size(); i++) 
        ans += tolower(str[i]);
    sort(ans.begin(), ans.end());
    return ans;
}

int main(void) {
    string str;
    vector<string> v;
    unordered_map<string, int> map;
    while(cin >> str, str != "#") {
        v.push_back(str);
        map[normalize(str)]++;
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++)
        if(map[normalize(v[i])] == 1)
            cout << v[i] << endl;
    return 0;
}