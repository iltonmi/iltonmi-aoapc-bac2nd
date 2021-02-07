#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

const int N = 1010;

vector<string> tab[N];
int width[100];

int main(void) {
    string line;
    int row = 0;
    while(getline(cin, line)) {
        stringstream ss(line);
        string word;
        int col = 0;
        while(ss >> word) {
            if(word.size() > width[col])
                width[col] = word.size();
            tab[row].push_back(word);
            col++;
        }
        row++;
    }
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < tab[i].size(); j++) {
            if(j > 0) printf(" ");
            auto& word = tab[i][j]; cout << word;
            for(int k = 0; j < tab[i].size() - 1 
                    && k < width[j] - word.size(); k++)
                printf(" ");
        }
        puts("");
    }
    return 0;
}

