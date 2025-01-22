#include<stdio.h>


const int maxm = 100000;
int m;
int res[maxm + 1]; //返回3、4的查询结果
int h[maxm + 1]; //保存每次操作的树的深度

struct treeNode {
	int val;
	int depth = 1;
	int numNodes = 1;  
	treeNode* parent = NULL;
	treeNode* lchild = NULL;
	treeNode* rchild = NULL;
} * root;

int computeBF(treeNode* x) {
	return (x->rchild == NULL ? 0 : x->rchild->depth) - 
	    (x->lchild == NULL ? 0 : x->lchild->depth);
}

void update(treeNode* x) { //更新深度和包含结点数
	int a = x->rchild == NULL ? 0 : x->rchild->depth;
	int b = x->lchild == NULL ? 0 : x->lchild->depth;
	int c = x->rchild == NULL ? 0 : x->rchild->numNodes;
	int d = x->lchild == NULL ? 0 : x->lchild->numNodes;
	x->depth = (a > b ? a : b) + 1;
	x->numNodes = c + d + 1;
}

void rebalance(treeNode* x) {
	int BF = computeBF(x);
	while (BF <= 1 && BF >= -1) {
		if (x == root) return;
		x =  x -> parent;
		update(x);
		BF = computeBF(x);
	} //得到最深的不平衡的点 x;
	
	treeNode* p = x->parent; //将待平衡点的父亲结点进行保存
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
			y=x->rchild;
			z=y->lchild;
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
			//Fill this by your self.
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
			//Fill this by your self.
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
			//Fill this by your self.
		}

	if (p == NULL) root = x; //如果改变的是根结点，需要更新root结点的指向。
	else if (x->val > p->val) p->rchild = x;
	else p->lchild = x;
	x->parent = p;
}

void insert(int x) {
	treeNode* node = new treeNode();
	node->val = x;
	if (root == NULL) root = node;
	else {
		treeNode* p = root, * q = NULL; //q指向p的父亲结点
		while (p != NULL) {
			q = p; q->numNodes++; 
			if (x < p->val) 
				p = p->lchild;
			else p = p->rchild;
		}
		if (x < q->val) q->lchild = node;
		else q->rchild = node;
		node->parent = q;
	}
	rebalance(node);
}

int rank(int x) {
	treeNode* q = root;
	int cnt = 0;
	while (true){
		int n = (q->lchild == NULL? 0 : q -> lchild -> numNodes);
		if (x > q->val) { 
			cnt += n + 1; 
			q = q->rchild;
		}
		else if (x < q->val)
			q = q->lchild;
		else return cnt + n + 1;
	}	
}

int get(int k) {
	treeNode* p = root;
	int i=1;
	while(i){
		int leftnodes;
		if(p->lchild == NULL) leftnodes = 0;
		else leftnodes = p->lchild->numNodes;
		if (k == leftnodes + 1) return p->val;
		else if (k <= leftnodes) p = p->lchild;
		else {
			k -= leftnodes + 1;
			p = p->rchild;
		}
	}
	//Fill this part by yourself.
	//Hint: similar to rank(int x).
}

int main() {
	root = NULL;
	scanf("%d", &m);
	int j = 1;
	int x, y;  //x表示操作, y为对应的数
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &x, &y);
		if (x == 1) insert(y);
		else if (x == 3) res[j++] = rank(y);
		else res[j++] = get(y);
		h[i] = root->depth;
	}
	for (int i = 1; i < j; i++) printf("%d ", res[i]);
	printf("\n");
	for (int i = 1; i <= m; i++) printf("%d ", h[i]);
	return 0;
}
