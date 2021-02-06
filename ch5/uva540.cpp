#include <iostream>
#include <unordered_map>
#include <cstring>
#include <queue>

using namespace std;

int main(void) {
    int t;
    int cnt = 0;
    while(scanf("%d", &t) != EOF, t) {
        unordered_map<int, int> idmap;
        for(int i = 0; i < t; i++) {
            int k; cin >> k;
            for(int j = 0; j < k; j++) {
                int ele; cin >> ele;
                idmap[ele] = i;
            }
        }
        // 这题，也可以为每个team都声明一个queue，放在数组中
        // 然后队列只需要保存queue的arr idx
        queue<queue<int>*> q;
        char cmd[10];
        unordered_map<int, queue<int>> qmap;
        cnt++;
        printf("Scenario #%d\n", cnt);
        for(;;) {
            char cmd[10];
            scanf("%s", cmd);
            if(cmd[0] == 'S') break;
            if(cmd[0] == 'E') {
                int x; cin >> x;
                int id = idmap[x];
                if(qmap.count(id)) {
                    qmap[id].push(x);
                } else {
                    qmap[id] = queue<int>();
                    q.push(&qmap[id]);
                    q.back()->push(x);
                }
            } else if(cmd[0] == 'D') {
                auto& tq = *q.front();
                int ele = tq.front();
                if(tq.size() == 1) q.pop(), qmap.erase(idmap[ele]);
                else tq.pop();
                printf("%d\n", ele);
            }
        }
        puts("");
    }
    return 0;
}