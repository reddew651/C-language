#include <stdio.h>
const int maxn =100000;
const int maxm =500000;
int edge[maxm+1][3];
int par[maxn+1];
int rank[maxn+1];
int ind[maxm+1];
int m,n;

int Find(int x){
	if(x!=par[x]) par[x]=Find(par[x]);
	return par[x];
}

void Union(int r, int s){
	if(rank[s]>rank[r]) par[r]=s;
	else if(rank[s]<rank[r]) par[s]=r;
	else {
		par[s]=r;
		rank[r]++;
	} 
}

void swap(int &a, int &b){
	int tem=a;a=b;b=tem;
} 

int partition(int l, int r){
	int i=l;
	for(int j=l;j<r;j++){
		if(edge[ind[j]][2]<edge[ind[r]][2]) swap(ind[j],ind[i++]);
	}
	swap(ind[i],ind[r]);
	return i;
}

void qsort(int l, int r){
	int k=partition(l,r);
	if (l<k-1) qsort(l,k-1);
	if (k+1<r) qsort(k+1,r);
}

int krusal(){
	for (int i=1;i<=n;i++){
		par[i]=i;
		rank[i]=0;
	}
	int sumcost=0,cnt=0;
	for(int i=1;i<=m;i++){
		int a=edge[ind[i]][0],b=edge[ind[i]][1],c=edge[ind[i]][2];
		if(Find(a)!=Find(b)){
			Union(Find(a),Find(b));
			sumcost+=c;
			cnt++;
		}	
	}
	if(cnt!=n-1) printf("WRONG");
	return sumcost;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d %d",&edge[i][0],&edge[i][1],&edge[i][2]);
	}
	for (int i=1;i<=m;i++){
		ind[i]=i;
	}
	qsort(1,m);
		int red=krusal();
		printf("%d",red);
		return 0;
}

