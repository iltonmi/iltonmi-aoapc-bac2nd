#include <iostream>

using namespace std;

struct Node {
    char val;
    Node* child[4];
    Node(char val) : val(val) {}
};

Node *root1, *root2;
int sum;

char readchar() {
    char ch;
    while(ch = getchar(), !isalpha(ch));
    return ch;
}

// assert u != NULL
void build(Node* u) {
    if(!u || u->val != 'p') return;
    for(int i = 0; i < 4; i++) {
        u->child[i] = new Node(readchar());
        build(u->child[i]);
    }
}

void make_empty_child(Node* u) {
    for(int i = 0; i < 4; i++) {
        u->child[i] = new Node('e');
    }
}

void solve(Node *u, Node *v, int val) {
    // 其中一个是黑，则全黑，sum += val, return
    // 其中一个p，另一个白，则为白的分配4个白色子节点，开始子节点的匹配
    // 2个白，直接return
    // 2个p，开始子节点的匹配
    if(u->val == 'f' || v->val == 'f') {sum += val; return;}
    if(u->val == 'e' && v->val == 'e') return;
    if(u->val == 'e') make_empty_child(u);
    if(v->val == 'e') make_empty_child(v);
    for(int i = 0; i < 4; i++) {
        solve(u->child[i], v->child[i], val / 4);
    }
}

int main(void) {
    int T; scanf("%d", &T);
    while(T--) {
        root1 = new Node(readchar());
        build(root1);
        root2 = new Node(readchar());
        build(root2);
        sum = 0;
        solve(root1, root2, 1024);
        printf("There are %d black pixels.\n", sum);
    }
    return 0;
}