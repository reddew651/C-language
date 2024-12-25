#include<stdio.h>

const int maxn = 2000;
const int maxm = 20000;
const int MAXINT = 10000;

int m, n; //n代表顶点，m代表边数
int a[maxm + 1];
int b[maxm + 1];
int c[maxm + 1];
int linkto[maxm + 1];
int cost[maxm + 1];
int f[maxm + 2];
int dist[maxn + 1];

void input_data() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &a[i], &b[i],&c[i]);
	}
	for (int i = 1; i <= m; i++) {
		f[a[i]]++;
	}
	for (int i = 2; i <= n; i++) {
		f[i] = f[i] + f[i - 1];
	}
	f[n + 1] = f[n];
	for (int i = 1; i <= m; i++) {
		//add sth. here
	}
}

void Bellman_ford() {
	for (int i = 1; i <= n; i++) {
		dist[i] = MAXINT;
	}
	dist[1] = 0;
	for (int i = 1; i <= n - 1; i++) {
		//add sth. here
	}
}


int main() {
	input_data();
	Bellman_ford();
	for (int i = 2; i <= n; i++) {
		printf("%d ", dist[i]);
	}
	return 0;
}
