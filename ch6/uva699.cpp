#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int val;
    Node *left, *right;
    Node(int val) : val(val), left(NULL), right(NULL) {}
};

Node *root;
unordered_map<int, int> map;

void build(Node *u) {
    int l, r;
    scanf("%d", &l);
    if(l != -1) 
        u->left = new Node(l), build(u->left);
    scanf("%d", &r);
    if(r != -1) 
        u->right = new Node(r), build(u->right);
}

void dfs(Node* node, int x) {
    if(!node) return;
    map[x] += node->val;
    dfs(node->left, x - 1);
    dfs(node->right, x + 1);
}

int main(void) {
    for(int i = 1; ; i++) {
        int val; scanf("%d", &val);
        if(val == -1) break;
        else root = new Node(val);
        map.clear();
        build(root);
        dfs(root, 0);
        printf("Case %d:\n", i);
        vector<pair<int, int>> v;
        for(auto& t : map) v.push_back(t);
        sort(v.begin(), v.end());
        for(int i = 0; i < v.size(); i++) 
            printf(i > 0 ? " %d" : "%d", v[i].second);
        printf("\n\n");
    }
    return 0;
}