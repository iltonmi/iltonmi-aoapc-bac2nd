#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
// 动态创建节点思路
struct Node {
    bool has_val;
    int val;
    Node *left, *right;
    Node() : has_val(false), left(NULL), right(NULL) {}
};

Node *root;
bool failed;
queue<Node*> freenodes;
Node nodes[260];
// 内存池技术
void init() {
    for(int i = 0; i < (sizeof(nodes)) / (sizeof(Node)); i++) 
        freenodes.push(&nodes[i]);
}

auto newnode() -> Node* {
    auto ans = freenodes.front(); freenodes.pop();
    ans->left = ans->right = NULL, ans->has_val = false;
    return ans;
}

void remove_tree(Node *u) {
    if(!u) return;
    remove_tree(u->left);
    remove_tree(u->right);
    freenodes.push(u);
}

bool add_node(const string& path, int val) {
    auto u = root;
    for(int i = 0; i < path.size(); i++) {
        char ch = path[i];
        if(ch == 'L') {
            if(!u->left) u->left = newnode();
            u = u->left;
        } else if(ch == 'R') {
            if(!u->right) u->right = newnode();
            u = u->right;
        }
    }
    if(u->has_val) return false;
    u->val = val;
    u->has_val = true;
    return true;
}

bool read_tree() {
    root = newnode();
    for(;;) {
        char ch;
        while(ch = getchar(), isspace(ch));
        if(ch == EOF) return false;
        ch = getchar();
        if(ch == ')') break;
        int val = ch - '0';
        while(ch = getchar(), ch != ',') 
            val = val * 10 + (ch - '0');
        string path;
        while(ch = getchar(), ch != ')')
            path += ch;
        if(!add_node(path, val)) failed = true;
    }
    return true;
}

bool bfs(Node* root) {
    if(failed) return false;
    queue<Node*> q;
    q.push(root);
    vector<int> ans;
    while(q.size()) {
        int len = q.size();
        for(int i = 0; i < len; i++) {
            auto u = q.front(); q.pop();
            if(!u->has_val) return false;
            ans.push_back(u->val);
            if(u->left) q.push(u->left);
            if(u->right) q.push(u->right);
        }
    }
    for(int i = 0; i < ans.size(); i++) 
        printf(i > 0 ? " %d" : "%d", ans[i]);
    puts("");
    return true;
}

int main(void) {
    init();
    while(read_tree()) {
        if(!bfs(root)) puts("not complete");
        remove_tree(root);
        failed = false;
    }
    return 0;
}