#include <iostream>

using namespace std;

int main() {
    int c, q = 1;
    while(~(c = getchar())) {
        if(c == '"') printf("%s", q ? "``" : "''"), q = !q;
        else printf("%c", c);
    }
    return 0;
}