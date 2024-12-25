#include<stdio.h>
#include<memory.h>
#include<stdlib.h>

const int maxn=5001;

int *A[maxn];
int *B[maxn];
bool visited[maxn];
int d[maxn], n, edges;

int f, r;
int list[maxn + 1];

int bfs(int u){
	f = 0; r = 0;
	visited[u]=true; list[r++] = u;

	while (f < r){
		u = list[f++];
		for (int i=1; i<=d[u]; i++){
			int v=A[u][i];
			if(!visited[v]){
				B[u][i]=1;
				for (int j=1; j<=d[v]; j++)
					if (A[v][j]==u) B[v][j]=1;
				edges++;
				visited[v] = true; list[r++] = v; 
			}
		}
	}
}
void printAns(){
	printf("%d\n",edges);
	for(int i=1;i<=n;i++){
		printf("%d",d[i]);
		for(int j=1;j<=d[i];j++) printf(" %d", B[i][j]);
		printf("\n");
	} 
}
int main(){
	scanf("%d",&n);
	memset(visited, 0, sizeof(visited));
	for(int i=1;i<=n;i++){
		scanf("%d",&d[i]);
		A[i]=(int*)malloc(sizeof(int)*(d[i]+1));
		B[i]=(int*)malloc(sizeof(int)*(d[i]+1));
		for(int j=1;j<=d[i];j++){
			scanf("%d", &A[i][j]);
			B[i][j]=0; 
		}
	}
	for(int i=1;i<=n;i++) 
		if (!visited[i]) bfs(i);
	printAns();
	return 0;
}
