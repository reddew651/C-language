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
            if(color[v]==c){
            	return false;
			}
				//add some code here   (Hint: we can conlude that the graph is not bipartite now, as both u v are should be colored with c!)
            if(!color[v]){
            	color[v]=-c;
            	dfs(v,-c);
			}
				//add some code here.  (Hint: call dfs on v)
        }
        return true;
	//add a return setence here.
}

int main(){
    int k;
    scanf("%d",&k);
    for(int m=1;m<=k;m++){
    	scanf("%d",&n);
    	memset(edge,0,sizeof(edge));
        memset(color,0,sizeof(color));
        
        for (int i=1;i<=n;i++){
        	for (int j=1;j<=n;j++){
        		scanf("%d",&edge[i][j]);
			}
		}
		bool flag = true;
		for (int i=1;i<=n;i++){
			flag=flag && dfs(i,1);
		}
		if (flag) printf("Yes\n");
		else printf("No\n");
		//Fill this part
	}
	return 0;
}



