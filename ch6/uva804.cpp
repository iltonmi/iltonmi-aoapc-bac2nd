#define LOCAL

#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Trans {
    map<int, int> inputs;
    map<int, int> outputs;
};

const int N = 110;
int places[N];
int nf, n, nt, restf;
Trans tarr[N];

bool is_fireable(const Trans& trans) {
    for(auto& t : trans.inputs) 
        if(places[t.first] < t.second) return false;
    return true;
}

void fire(const Trans& trans) {
    for(auto& t : trans.inputs)
        places[t.first] -= t.second;
    for(auto& t : trans.outputs)
        places[t.first] += t.second;
}

bool solve() {
    while(restf--) {
        bool dead = true;
        for(int i = 0; i < nt; i++)
            if(is_fireable(tarr[i])) {
                fire(tarr[i]); dead = false; break;
            }
        if(dead) return false;
    }
    return true;
}


int main(void) {
    #ifdef LOCAL
    freopen("uva804.in", "r", stdin);
    freopen("uva804.out", "w", stdout);
    #endif
    int cnt = 0;
    while(scanf("%d", &n), n) {
        for(int i = 1; i <= n; i++)
            scanf("%d", &places[i]);
        scanf("%d", &nt);
        for(int i = 0; i < nt; i++) {
            int t;
            tarr[i] = Trans();
            while(scanf("%d", &t), t) {
                if(t < 0) tarr[i].inputs[-t]++;
                else tarr[i].outputs[t]++;
            }
        }
        scanf("%d", &nf); restf = nf;
        if(solve()) printf("Case %d: still live after %d transitions\n", ++cnt, nf);
        else printf("Case %d: dead after %d transitions\n", ++cnt, nf - restf - 1);
        printf("Places with tokens:");
        for(int i = 1; i <= n; i++) 
            if(places[i] > 0) printf(" %d (%d)", i, places[i]);
        printf("\n\n");
    }
    return 0;
}

// 这题算是一道大模拟
// 需要一个数组，记录每个place 的token数量
// trans, 需要记录input place 和output place
// 问题在于， trans如何被触发呢？
// 主动轮询，遍历每个trans，判断input place的token是否足够