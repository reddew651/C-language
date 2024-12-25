#include<stdio.h>
#include<memory.h>
const int maxn=401;
int edge[maxn][maxn];  
int color[maxn];      //0: uncolored.   -1 +1  : colored black or white.
int n;

int r, f;
int list[maxn + 1];

bool bfs(int u){
	f = 0; r = 1; 
	list[0] = u; color[u] = 1;
	while (f<r){
		u = list[f++];
		for (int v = 1; v<=n; v++)
			if (edge[u][v] == 1){
				if (color[v] == color[u]) return false;
				if (color[v] == 0){
					color[v] = -color[u];
					list[r++] = v;
				}
			}
	}
	return true; 
}

int main(){
    int k;
    scanf("%d",&k);
    for(int m=1;m<=k;m++){
    	scanf("%d",&n);
    	memset(edge,0,sizeof(edge));
        memset(color,0,sizeof(color));
    	for(int i=1;i<=n;i++)
    		for(int j=1;j<=n;j++)
    			scanf("%d",&edge[i][j]);
		bool flag=false;
		for(int i=1;i<=n;i++){
			if(!color[i]){
				if(!bfs(i)){
				    printf("No\n");
					flag=true;
					break;
				}
			} 
		}
		if(!flag) printf("Yes\n");
	}
	return 0;
}
