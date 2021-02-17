#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

struct Node {
    char val;
    Node *left, *right;
    Node(char val) : val(val), left(NULL), right(NULL) {}
};

char po[27], io[27];


void post_dfs(Node* root) {
    if(!root) return;
    post_dfs(root->left);
    post_dfs(root->right);
    putchar(root->val);
}

auto rebuild(int pl, int pr, int il, int ir) -> Node* {
    if(pl > pr) return NULL;
    auto ans = new Node(po[pl]);
    // pl是根节点索引
    int i = il;
    for(; i <= ir; i++)
        if(io[i] == po[pl]) break;
    int llen = i - il;
    ans->left = rebuild(pl + 1, pl + llen, il, i - 1);
    ans->right = rebuild(pl + llen + 1, pr, i + 1, ir);
    return ans;
}

int main(void) {
    while(scanf("%s", po) != EOF) {
        scanf("%s", io);
        auto root = rebuild(0, strlen(po) - 1, 0, strlen(po) - 1);
        post_dfs(root);
        printf("\n");
    }
    return 0;
}