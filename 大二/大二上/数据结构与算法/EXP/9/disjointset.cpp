#include <stdio.h>
#include <stdlib.h>
#define MAXN 7000000
int fa[MAXN], rank[MAXN];
int find(int x)
{
	if(x==fa[x]){
		return x;
	}else{
		fa[x] = find(fa[x]);
        //please finish the following parts
	}
}
void merge(int i, int j)
{
    int x = find(i), y = find(j);
    if(x==y) return; 
    if(rank[x] < rank[y]){
    	fa[x] = y;
	}else if (rank[x] > rank[y]){
		fa[y] =x ;
	}else {
		fa[y] =x;
		rank[x]++;
	}
    //please finish the following parts

}
int main()
{
     int T,n,m,u,v,i,sum;
     sum=0;
     scanf("%d%d",&n,&m);
     for(i=1;i<=n;i++)
     {
     	fa[i] = i;
     	rank[i] = 0;
         //please finish the following parts ³õÊ¼»¯ 

      }
     for(i=0;i<=m-1;i++)
     {
         scanf("%d%d",&u,&v);
         merge(u,v);
         }
     for(i=1;i<=n;i++)
     {
         if(fa[i]==i)
         {
         	sum ++;
               //please finish the following parts

             }
         }
     printf("%d\n",sum);
     return 0;
}

