#include<stdio.h>
#include<memory.h>
#include<stdlib.h>

const int maxn=5001;

int *A[maxn];
int *B[maxn];
bool visited[maxn];
int d[maxn], n, counter;

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
				B[u][i] = 1;
				for (int j = 1; j<=d[v];j++)
					if (A[v][j]==u) B[v][j] = 1;
				counter ++;
				visited[v] = true;
				list[r++] = v;
				//add something here.  Most importantly, you should add "v" into the list (which is a queue).
				// Reminder: You have to change two entries of B when you select the edge (u,v).
				// Reminder: Increase counter by 1
			}
		}
	}
}
void printAns(){
	printf("%d\n",counter);
	for(int i=1;i<=n;i++){
		printf("%d", d[i]);
		for (int j = 1; j<=d[i]; j++) printf(" %d",B[i][j]);
		printf("\n");
		//add something here for print.
	} 
}
int main(){
	scanf("%d",&n);
	memset(visited, 0, sizeof(visited));
	for(int i=1;i<=n;i++){
		scanf("%d",&d[i]);
		A[i]=(int*)malloc(sizeof(int)*(d[i]+1));
		B[i]=(int*)malloc(sizeof(int)*(d[i]+1));
		for (int j=1; j<=d[i]; j++){
			scanf("%d",&A[i][j]);
			B[i][j] = 0;
		}
		// Add some code here. It inputs the data A[i][j] and assign B[i][j] = 0 for 1<=j<= d[i].
	}
	for(int i=1;i<=n;i++) 
		if (!visited[i]) bfs(i);   // Comment: In the last exercise, we used dfs(i).  Here, we use the alternative procedure bfs(i).
	printAns();
	return 0;
}
