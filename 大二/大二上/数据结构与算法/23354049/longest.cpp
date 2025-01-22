#include <cstdio>
#include <algorithm>
using namespace std;

const int maxm = 100000;

struct treeNode {
    int val;
    int depth = 1;
    int numNodes = 1;
    int pos;    
    int dp;         
    treeNode* parent = NULL;
    treeNode* lchild = NULL;
    treeNode* rchild = NULL;
} *root;

int computeBF(treeNode* x) {
    return (x->rchild == NULL ? 0 : x->rchild->depth) - 
           (x->lchild == NULL ? 0 : x->lchild->depth);
}

void update(treeNode* x) { 
    int a = x->rchild == NULL ? 0 : x->rchild->depth;
    int b = x->lchild == NULL ? 0 : x->lchild->depth;
    x->depth = (a > b ? a : b) + 1;
    
    int c = x->rchild == NULL ? 0 : x->rchild->numNodes;
    int d = x->lchild == NULL ? 0 : x->lchild->numNodes;
    x->numNodes = c + d + 1;
}

void rebalance(treeNode* x) {
    int BF = computeBF(x);
    while (BF <= 1 && BF >= -1) {
        if (x == root) return;
        x = x->parent;
        update(x);
        BF = computeBF(x);
    }

    treeNode* p = x->parent;
    treeNode* y, * z;
    if (BF == 2)
        if (computeBF(x->rchild) == 1) { 
            y = x->rchild;
            x->rchild = y->lchild;
            if (x->rchild) x->rchild->parent = x;
            y->lchild = x;
            x->parent = y;
            update(x); update(y);
            x = y;
        }
        else { 
            y = x->rchild;
            z = y->lchild;
            y->lchild = z->rchild;
            if (y->lchild) y->lchild->parent = y;
            x->rchild = z->lchild;
            if (x->rchild) x->rchild->parent = x;
            z->rchild = y;
            z->lchild = x;
            y->parent = z;
            x->parent = z;
            update(x);
            update(y);
            update(z);
            x = z;
        }
    else
        if (computeBF(x->lchild) == -1) {
            y = x->lchild;
            x->lchild = y->rchild;
            if (x->lchild) x->lchild->parent = x;
            y->rchild = x;
            x->parent = y;
            update(x);
            update(y);
            x = y;
        }
        else {
            y = x->lchild;
            z = y->rchild;
            y->rchild = z->lchild;
            if (y->rchild) y->rchild->parent = y;
            x->lchild = z->rchild;
            if (x->lchild) x->lchild->parent = x;
            z->lchild = y;
            z->rchild = x;
            y->parent = z;
            x->parent = z;
            update(x);
            update(y); 
            update(z);
            x = z;
        }

    if (p == NULL) root = x; 
    else if (x->val > p->val) p->rchild = x;
    else p->lchild = x;
    x->parent = p;
}

int getMaxDP(treeNode* p, int val, int pos) {
    if (!p) return 0;
    
    int ans = 0;
    if (p->val < val && p->pos < pos) ans = p->dp;

    int leftMax = getMaxDP(p->lchild, val, pos);
    int rightMax = getMaxDP(p->rchild, val, pos);
    
    return max(ans, max(leftMax, rightMax));
}

int getMaxDP(int val, int pos) {
    return getMaxDP(root, val, pos);
}

void insert(int val, int pos, int dp_val) {
    treeNode* node = new treeNode();
    node->val = val;
    node->pos = pos;
    node->dp = dp_val;
    
    if (root == NULL) {
        root = node;
        return;
    }
    
    treeNode* p = root;
    treeNode* q = NULL;
    
    while (p != NULL) {
        q = p;
        q->numNodes++;
        if (val < p->val) 
            p = p->lchild;
        else 
            p = p->rchild;
    }
    
    if (val < q->val)
        q->lchild = node;
    else
        q->rchild = node;
    node->parent = q;
    
    rebalance(node);
}

int main() {
    root = NULL;
    int n;
    scanf("%d", &n);
    
    int arr[maxm];
    int dp[maxm];  
    int maxLen = 1;

    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        dp[i] = 1; 
    }
    for(int i = 0; i < n; i++) {
        dp[i] = getMaxDP(arr[i], i) + 1;
        maxLen = max(maxLen, dp[i]);
        insert(arr[i], i, dp[i]);
    }
    
    printf("%d\n", maxLen);
    return 0;
}