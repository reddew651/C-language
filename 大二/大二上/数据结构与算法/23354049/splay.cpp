#include<stdio.h>
#pragma comment(linker, "/STACK:1073741824")

const int null = 0;
const int maxm = 100001;
int m_count;  //表示当前在处理第几个操作。 

/* 以下五个数组用来存splay 树。numNodes是附加信息：用来存子树的节点数，方便执行Get和Rank操作 */
int parent[maxm];	//父亲
int lchild[maxm];	//左孩子
int rchild[maxm];	//右孩子
int val[maxm];		//数据
int numNodes[maxm];	//以该点为根的结点个数

int splay[maxm]; //记录每次操作splay的次数.即输出的第2行。 

int m, root = null, count = 0;//count为最新节点的序号。 

inline void update(int x) {  //更新结点数
	numNodes[x] = numNodes[lchild[x]] + numNodes[rchild[x]] + 1;
}

void splayTree(int x) {
	int f = parent[x];
	if (f == null) return;
	splay[m_count]++; //第m_count次的splay的次数
	
	int g = parent[f];
	if (g == null) { /*zig or zag*/
		if (lchild[f] == x) { /*zig*/
	   		parent[x] = null;
            parent[f] = x;
            lchild[f] = rchild[x];
            if (rchild[x] != null) parent[rchild[x]] = f;
            rchild[x] = f;

			//add sth. here
		}
		else {                /*zag*/
	    	parent[x] = null;
            parent[f] = x;
            rchild[f] = lchild[x];
            if (lchild[x] != null) parent[lchild[x]] = f;
            lchild[x] = f;

			//add sth. here
		}
		update(f); update(x);
		parent[x] = null; root = x;
		return; 
	}

	int h = parent[g];
	if (lchild[g] == f && lchild[f] == x) {		
        parent[g] = f;
        lchild[g] = rchild[f];
        if (rchild[f] != null) parent[rchild[f]] = g;
        parent[f] = x;
        lchild[f] = rchild[x];
        if (rchild[x] != null) parent[rchild[x]] = f;
        rchild[f] = g;
        rchild[x] = f;
			/*zig-zig*/
		//add sth. here
	}
	else if (rchild[g] == f && rchild[f] == x) {
        parent[g] = f;
        rchild[g] = lchild[f];
        if (lchild[f] != null) parent[lchild[f]] = g;
        parent[f] = x;
        rchild[f] = lchild[x];
        if (lchild[x] != null) parent[lchild[x]] = f;
        lchild[f] = g;
        lchild[x] = f;
			/*zag-zag*/
		// add. sth. here
	}
	else if (lchild[g] == f && rchild[f] == x) {
        parent[x] = g;
        parent[f] = x;
        parent[g] = x;
        rchild[f] = lchild[x];
        lchild[g] = rchild[x];
        if (lchild[x] != null) parent[lchild[x]] = f;
        if (rchild[x] != null) parent[rchild[x]] = g;
        lchild[x] = f;
        rchild[x] = g;	/*zig-zag*/
		//add sth. here
	}
	else if (rchild[g] == f && lchild[f] == x) {
		parent[x] = g;
        parent[f] = x;
        parent[g] = x;
        lchild[f] = rchild[x];
        rchild[g] = lchild[x];
        if (rchild[x] != null) parent[rchild[x]] = f;
        if (lchild[x] != null) parent[lchild[x]] = g;
        rchild[x] = f;
        lchild[x] = g;
			/*zag-zig*/
		//add sth. here
	}

	update(g); update(f); update(x);
	if (h == null) {
		root = x; parent[root] = null;  //更新根节点
	}
	else{
		parent[x] = h;
		if (val[x] < val[h]) lchild[h] = x;
		else rchild[h] = x;
		splayTree(x);
	}
}

int search(int x){ //调用search时确保root!=null 
	int p = root;
	while (val[p] != x) {
		if (x < val[p]){
			p = lchild[p];
			//add sth. here
		}
		else{
			  p = rchild[p];
			//add sth. here
		}
	}
	return p; 
}

void Insert(int x) {
	count++; numNodes[count]++;
	val[count] = x; //创建结点，count为其索引
	lchild[count] = rchild[count] = null;
	if (root == null) {   //根节点为空
		root = count; parent[root] = null;
 	}
	else { 
		 int p = root;
		 bool flag = true;
        while (flag) {
            if (x < val[p]) {
                if (lchild[p] == null) {
                    lchild[p] = count;
                    parent[count] = p;
                    break;
                }
                p = lchild[p];
            } 
			else {
                if (rchild[p] == null) {
                    rchild[p] = count;
                    parent[count] = p;
                    break;
                }
                p = rchild[p];
            }
        }
        splayTree(count);
	// add sth. here
	}
}

void Delete(int p){
	if (lchild[p] != null && rchild[p] != null) {  //待删除节点2个孩子 
		int s = lchild[p];
		while (rchild[s] != null) s = rchild[s];
		//add sth here.  //此时待删除节点变为了s。f仍然是p的父亲。 p只有<=1个孩子了。 
	}
	int f = parent[p], s = lchild[p] + rchild[p]; // s是空(当p为叶子）或者是p的唯一的孩子 
	if (f == null) { /*删除的节点p是根节点*/
		root = s; parent[root] = null;
	}
	else{
		if (p == lchild[f]) lchild[f] = s;
        else rchild[f] = s;
        if (s != null) parent[s] = f;
        splayTree(f);
	    //add sth. here
	}
}

int Rank(int x) {
	int q = root;
	int cnt = 0; 
	while (true) {
		int n = numNodes[lchild[q]];
		if (x > val[q]) {
			 cnt =cnt+ n + 1;
            q = rchild[q];
			//add sth. here
		}
		else if (x < val[q])  q = lchild[q];
		    //add sth. here
		else{
			splayTree(q);
			cnt = cnt+n + 1;
            return cnt;
			//add sth. here
		}
	}
}

int Get(int k) {//找第k小的数 
	int q = root;
	while (true) {
		int n = numNodes[lchild[q]];
		if (k > n + 1) {
			k -= n + 1;
            q = rchild[q];
		    //add sth. here
		}
		else if (k <= n)  q = lchild[q];
		//add sth.here
		else {
			splayTree(q);
            return val[q];
			//add sth. here
		}
	}
}

int result[maxm];

int main() {
	int kind, x, t_rank_get = 0;//kind表示操作类型  x表示操作参数
	scanf("%d", &m);
	for (m_count = 1; m_count <= m; m_count++) {
		scanf("%d %d", &kind, &x);
		if (1 == kind) Insert(x);
		else if (2 == kind) Delete(search(x));
		else if (3 == kind) result[++t_rank_get] = Rank(x);
		else result[++t_rank_get] = Get(x);
	}
	for (int i = 1; i <= t_rank_get; i++) printf("%d ", result[i]);
	printf("\n");
	for (int i = 1; i <= m; i++) printf("%d ", splay[i]);
	return 0;
}

