#include <iostream>
#include <algorithm>

using namespace std;

const int N = 6;
char a[N][N];

void get_empty_pos(int *x, int * y) {
    for(int i = 0; i < 5; i++) 
        for(int j = 0; j < 5; j++)
            if(a[i][j] == ' ') {
                *x = i, *y = j;
                break;
            }
}

void get_pos(int* x, int* y, char op) {
    if(op == 'A') *x -= 1;
    else if(op == 'B') *x += 1;
    else if(op == 'L') *y -= 1;
    else if(op == 'R') *y += 1;
}

void print_matrix() {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
             printf(j < 4 ? "%c " : "%c\n", a[i][j]);
        }
    }
}

bool valid_square(char ch) {
    return ch == ' ' || isalpha(ch);
}

bool read_matrix() {
    for(int i = 0; i < 5; i++) {
        char ch;
        while(!valid_square(ch = getchar()));
        if(ch == 'Z') return false;
        a[i][0] = ch;
        for(int j = 1; j < 5; j++) a[i][j] = getchar();
    }
    return true;
}

bool solve() {
    int x = 0, y = 0;
    get_empty_pos(&x, &y);
    char op;
    bool valid = true;
    while((op = getchar()) != '0') {
        if(!isalpha(op) || !valid) continue;
        int dx = x, dy = y;
        get_pos(&dx, &dy, op);
        if(dx < 0 || dx > 4 || dy < 0 || dy > 4) valid = false;
        swap(a[x][y], a[dx][dy]);
        x = dx, y = dy;
    }
    return valid;
}

int main() {
    for(int i = 1; ; i++) {
        if(!read_matrix()) break;
        bool flag = solve();
        if(i != 1) puts("");
        printf("Puzzle #%d:\n", i);
        if(flag) print_matrix();
        else printf("This puzzle has no final configuration.\n");
    }
    return 0;
}