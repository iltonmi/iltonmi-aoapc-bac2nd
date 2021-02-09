#include <iostream>
#include <queue>
#include <sstream>
#include <cstring>

using namespace std;


// 模拟不超过10个程序，在单CPU系统的并发执行
// 程序可能的2种状态：running, ready
// running中的程序会被分配quantum，即允许执行的time unit
// 
// 单个程序不超过25条指令，不包括最后的end指令
// 有5种指令
// var是小写字母，const是小于100的unsigned
// 系统中只有26种变量，并且在程序之间共享，变量的初始值都是0
// ready queue, blocked queue
int a[26];
bool locked;
int tunit;
int n, inst_time[5];
queue<int> bq;
deque<int> rq;

// getline和sstream都可以优化，特别是sstream
void run() {
    queue<string> progs[11];
    for(int i = 1; i <= n; i++) {
        string t;
        do getline(cin, t), progs[i].push(t); while(t != "end");
    }
    for(int i = 1; i <= n; i++) rq.push_back(i);
    memset(a, 0, sizeof a);
    locked = false;

    while(rq.size()) {
        int pid = rq.front(); rq.pop_front();
        bool flag = true;
        for(int i = 0; i < tunit; ) {
            stringstream ss(progs[pid].front());
            string cmd; ss >> cmd;
            // cout << "inst : " << cmd << endl;
            if(cmd == "print") {
                char ch; ss >> ch;
                printf("%d: %d\n", pid, a[ch - 'a']);
                i += inst_time[1];
            } else if(cmd == "lock") {
                if(locked) {
                    bq.push(pid), flag = false; break;
                } else locked = true;
                i += inst_time[2];
            } else if(cmd == "unlock") {
                locked = false;
                if(bq.size()) rq.push_front(bq.front()), bq.pop();
                i += inst_time[3];
            } else if(cmd == "end") {
                i += inst_time[4];
                progs[pid].pop();
                flag = false;
                break;
            } else {
                string t; ss >> t;
                int val; ss >> val;
                a[cmd[0] - 'a'] = val;
                i += inst_time[0];
            }
            progs[pid].pop();
        }
        if(flag) rq.push_back(pid);
    }
}

int main(void) {
    int T; scanf("%d", &T);
    for(int i = 0; i < T; i++) {
        if(i > 0) puts("");
        scanf("%d", &n);
        for(int i = 0; i < 5; i++) scanf("%d", &inst_time[i]);
        scanf("%d", &tunit);
        for(char ch = getchar(); ch != '\n'; ch = getchar());
        run();
    }
    return 0;
}