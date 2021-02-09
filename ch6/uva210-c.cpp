#include <iostream>
#include <queue>
#include <sstream>
#include <cstring>

using namespace std;

int a[26], pc[11];
bool locked;
int tunit;
int n, inst_time[5];
queue<int> bq;
deque<int> rq;
string progs[11][30];

void run() {
    for(int i = 1; i <= n; i++) {
        string t;
        int cnt = 0;
        do {
            t.clear();
            int ch;
            while(ch = getchar(), ch == '\n' || ch == '\r');
            t += ch;
            while(ch = getchar(), ch != '\n' && ch != '\r')
                t += ch;
            // cout << "::::" << t << endl;
            progs[i][cnt++] = t;
        } while(t != "end");
    }
    for(int i = 1; i <= n; i++) rq.push_back(i);
    memset(a, 0, sizeof a);
    memset(pc, 0, sizeof pc);
    locked = false;

    while(rq.size()) {
        int pid = rq.front(); rq.pop_front();
        bool flag = true;
        for(int i = 0; i < tunit; ) {
            string p = progs[pid][pc[pid]];
            int ch = p[2];
            if(ch == '=') {
                a[p[0] - 'a'] = isdigit(p[5]) ? (p[4] - '0') * 10 + p[5] - '0' : p[4] - '0';
                i += inst_time[0];
            } else if(ch == 'i') {
                printf("%d: %d\n", pid, a[p[6] - 'a']);
                i += inst_time[1];
            } else if(ch == 'c') {
                if(locked) {
                    bq.push(pid), flag = false; break;
                } else locked = true;
                i += inst_time[2];
            } else if(ch == 'l') {
                locked = false;
                if(bq.size()) rq.push_front(bq.front()), bq.pop();
                i += inst_time[3];
            } else if(ch == 'd') {
                i += inst_time[4];
                pc[pid]++;
                flag = false;
                break;
            }
            pc[pid]++;
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