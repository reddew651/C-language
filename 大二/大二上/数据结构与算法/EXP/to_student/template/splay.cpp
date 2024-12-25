#include<stdio.h>
#pragma comment(linker, "/STACK:1073741824")

const int null = 0;
const int maxm = 100001;
int m_count;  //��ʾ��ǰ�ڴ���ڼ��������� 

/* �����������������splay ����numNodes�Ǹ�����Ϣ�������������Ľڵ���������ִ��Get��Rank���� */
int parent[maxm];	//����
int lchild[maxm];	//����
int rchild[maxm];	//�Һ���
int val[maxm];		//����
int numNodes[maxm];	//�Ըõ�Ϊ���Ľ�����

int splay[maxm]; //��¼ÿ�β���splay�Ĵ���.������ĵ�2�С� 

int m, root = null, count = 0;//countΪ���½ڵ����š� 

inline void update(int x) {  //���½����
	numNodes[x] = numNodes[lchild[x]] + numNodes[rchild[x]] + 1;
}

void splayTree(int x) {
	int f = parent[x];
	if (f == null) return;
	splay[m_count]++; //��m_count�ε�splay�Ĵ���
	
	int g = parent[f];
	if (g == null) { /*zig or zag*/
		if (lchild[f] == x) { /*zig*/
			//add sth. here
		}
		else {                /*zag*/
			//add sth. here
		}
		update(f); update(x);
		parent[x] = null; root = x;
		return; 
	}

	int h = parent[g];
	if (lchild[g] == f && lchild[f] == x) {			/*zig-zig*/
		//add sth. here
	}
	else if (rchild[g] == f && rchild[f] == x) {	/*zag-zag*/
		// add. sth. here
	}
	else if (lchild[g] == f && rchild[f] == x) {	/*zig-zag*/
		//add sth. here
	}
	else if (rchild[g] == f && lchild[f] == x) {	/*zag-zig*/
		//add sth. here
	}

	update(g); update(f); update(x);
	if (h == null) {
		root = x; parent[root] = null;  //���¸��ڵ�
	}
	else{
		parent[x] = h;
		if (val[x] < val[h]) lchild[h] = x;
		else rchild[h] = x;
		splayTree(x);
	}
}

int search(int x){ //����searchʱȷ��root!=null 
	int p = root;
	while (val[p] != x) {
		if (x < val[p]){
			//add sth. here
		}
		else{
			//add sth. here
		}
	}
	return p; 
}

void Insert(int x) {
	count++; numNodes[count]++;
	val[count] = x; //������㣬countΪ������
	lchild[count] = rchild[count] = null;
	if (root == null) {   //���ڵ�Ϊ��
		root = count; parent[root] = null;
 	}
	else { 
	// add sth. here
	}
}

void Delete(int p){
	if (lchild[p] != null && rchild[p] != null) {  //��ɾ���ڵ�2������ 
		int s = lchild[p];
		while (rchild[s] != null) s = rchild[s];
		//add sth here.  //��ʱ��ɾ���ڵ��Ϊ��s��f��Ȼ��p�ĸ��ס� pֻ��<=1�������ˡ� 
	}
	int f = parent[p], s = lchild[p] + rchild[p]; // s�ǿ�(��pΪҶ�ӣ�������p��Ψһ�ĺ��� 
	if (f == null) { /*ɾ���Ľڵ�p�Ǹ��ڵ�*/
		root = s; parent[root] = null;
	}
	else{
	    //add sth. here
	}
}

int Rank(int x) {
	int q = root;
	int cnt = 0; 
	while (true) {
		int n = numNodes[lchild[q]];
		if (x > val[q]) {
			//add sth. here
		}
		else if (x < val[q])
		    //add sth. here
		else{
			//add sth. here
		}
	}
}

int Get(int k) {//�ҵ�kС���� 
	int q = root;
	while (true) {
		int n = numNodes[lchild[q]];
		if (k > n + 1) {
		    //add sth. here
		}
		else if (k <= n) //add sth.here
		else {
			add sth. here
		}
	}
}

int result[maxm];

int main() {
	int kind, x, t_rank_get = 0;//kind��ʾ��������  x��ʾ��������
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

