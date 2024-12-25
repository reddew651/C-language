#include<stdio.h>
#include<memory.h>
const int maxn=401;

int edge[maxn][maxn];   //邻接矩阵
int color[maxn];      //0: uncolored.   -1 +1  : colored black or white.
int n;

bool dfs(int u,int c){
    color[u]=c;     //对u点进行染色操作 
    for(int v=1;v<=n;v++)//遍历与u点相连的点
        if(edge[u][v]==1){
            if(color[v]==c) 
				//add some code here   (Hint: we can conlude that the graph is not bipartite now, as both u v are should be colored with c!)
            if(!color[v])
				//add some code here.  (Hint: call dfs on v)
        }
	//add a return setence here.
}

int main(){
    int k;
    scanf("%d",&k);
    for(int m=1;m<=k;m++){
    	scanf("%d",&n);
    	memset(edge,0,sizeof(edge));
        memset(color,0,sizeof(color));

		//Fill this part
	}
	return 0;
}



