#include <iostream>

using namespace std;

// 正常情况下，0是头节点
// inv的情况下，n + 1是头节点
// 那么：
// 1和2互换就好了，其他无区别

// 不需要元素，因为指定位置的元素是确定的
const int M = 100010;
int l[M], r[M], n, m;
bool inv;

void print() {
    if(inv) {
        for(int i = l[n+1], cnt = 1; i != 0; i = l[i], cnt++) 
            printf("%d ", i);
    } else {
        for(int i = r[0], cnt = 1; i != n + 1; i = r[i], cnt++) 
            printf("%d ", i);
    }
    puts("");
}

void init() {
    r[0] = 1, l[n + 1] = n;
    for(int i = 1; i <= n; i++)
        l[i] = i - 1, r[i] = i + 1;
    inv = false;
}

void swap_pos(int x, int y) {
    // assert x != y
    int t = l[x]; l[x] = l[y]; l[y] = t;
    r[l[x]] = x; r[l[y]] = y;
    t = r[x]; r[x] = r[y]; r[y] = t;
    l[r[x]] = x; l[r[y]] = y;
}

void move_left(int x, int y) {
    r[l[x]] = r[x], l[r[x]] = l[x];
    l[x] = l[y], r[x] = y, r[l[y]] = x, l[y] = x;
}

void solve(int op) {
    if(op == 4) {inv = !inv; return;}
    int x, y; scanf("%d%d", &x, &y);
    if(op == 3) swap_pos(x, y);
    else {
        if(op == 1 && x != (inv ? r[y] : l[y]))
            move_left(x, inv ? r[y] : y);
        else if(op == 2 && x != (inv ? l[y] : r[y])) 
            move_left(x, inv ? y : r[y]);
    }
}

int main(void) {
    int cnt = 0;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 0; i < m; i++) {
            // cout << ":::" << i << endl;
            int a; scanf("%d", &a);
            solve(a);
            // print();
        }
        long long sum = 0;
        if(inv) {
            for(int i = l[n+1], cnt = 1; i != 0; i = l[i], cnt++) 
                if(cnt & 1) sum += i;
        } else {
            for(int i = r[0], cnt = 1; i != n + 1; i = r[i], cnt++) 
                if(cnt & 1) sum += i;
        }
        printf("Case %d: %lld\n", ++cnt, sum);
    }
    return 0;
}