//Kruskal algorithm
#include<stdio.h>

const int maxn = 100000;
const int maxm = 500000;

int edge[maxm + 1][3];
int parent[maxn + 1];
int rank[maxn + 1];
int hash[maxm + 1]; 
int m, n;

int Find(int x) { //Â·¾¶Ñ¹Ëõ
	if (x != parent[x]) 
		parent[x] = Find(parent[x]);
	return parent[x];
}

void Union(int r, int s) { //link by rank
	if (rank[s] > rank[r]) parent[r] = s;
	else if (rank[s] < rank[r]) parent[s] = r;
	else{ parent[s] = r; rank[r]++; }
}

void swap(int &a, int &b) {
	int tmp = a; a = b; b = tmp;
}

int partition(int l, int r) {
	int i = l;
	for (int j = l; j < r; j++) 
		if (edge[hash[j]][2] < edge[hash[r]][2])
			swap(hash[j], hash[i++]);		
	swap(hash[i], hash[r]);
	return i;
}

void Qsort(int l, int r) {
	int k = partition(l, r);
	if (l < k - 1) Qsort(l, k - 1);
	if (k + 1 < r) Qsort(k + 1, r);
}

int kruskal() {
	int sumCost = 0;
	int cnt = 0;
	for (int i = 1; i <= m; i++) {
		int x = Find(edge[hash[i]][0]);
		int y = Find(edge[hash[i]][1]);
		if (x != y) {
			Union(x, y); cnt++;
			sumCost += edge[hash[i]][2];
		}
	}
	if (cnt != n - 1) printf("some thing is wrong");
	return sumCost;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) 
		scanf("%d %d %d", &edge[i][0], &edge[i][1], &edge[i][2]);
	for (int i = 1; i <= n; i++) { //makeset
		parent[i] = i; rank[i] = 0;
	}
	for (int i = 1; i <= m; i++) hash[i] = i;
	Qsort(1, m);
	int res = kruskal();
	printf("%d", res);
	return 0;
}
