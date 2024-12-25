#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

const int maxn=50000;
const int maxm=500000;

int n,m;

int a[maxm + 1], b[maxm + 1];
int p[maxn + 2];
int linkto[2 * maxm + 1];

/* 可通过阅读下面这段函数的代码，来理解p和linkto  */ 
void input_data() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d %d", &a[i], &b[i]);
	for (int i = 1; i <= m; i++) p[a[i]]++;	
	for (int i = 1; i <= n; i++) p[i] = p[i] + p[i - 1];
	p[n + 1] = p[n];  
	for (int i = 1; i <= m; i++) {
		linkto[p[a[i]]] = b[i];
		p[a[i]]--;
	}
}

int min(int a,int b){
	return a<b ? a:b; 
}

int count=0;
int index[maxn];
int low[maxn];
int stack[maxn],top=0;
int on_stack[maxn];

int tComponent=0; // tComponent是当前找到的强连通块个数。 
int size[maxn];   // size[i]保存第i个强连通块 的顶点个数。   

void tarjan_scc(int v){  // SCC主过程! 
	index[v]=low[v]=count++;
	stack[top++]=v;
	on_stack[v]=1;
	// push v into the stack and mark v to be on stack.
	for(int i=p[v]+1;i<=p[v+1];i++){
		int w=linkto[i];
		if(!index[w]){
			tarjan_scc(w);
			low[v]=min(low[v],low[w]);
		}
		else if(on_stack[w]) low[v]=min(low[v],index[w]);
		//add some code here by yourself
		//Hint 1. dfs. Hint 2. modify low[v]
	}
	if(index[v]==low[v]){ // find out a new component. 
		int j;
		do{
			j=stack[--top];
			on_stack[j]=0;
			//Add some code in the following.
			//Hint: pop an element from the stack to j, and mark j to be not on stack.
			size[tComponent]++;
		} while (j!=v);
		tComponent++;
	}
}

void swap(int &a, int &b) {
  int t = a; a = b; b = t;
}
int partition(int array[], int low, int high) {
  int pivot = array[high];
  int i = low;
  for (int j = low; j < high; j++) {
  	i++;
  	if(array[j]<pivot) swap(array[j],array[i]); 
    //fill this part by yourself.
  }
  swap(array[i], array[high]);
  return (i);
}
void quickSort(int array[], int low, int high) {
	if(low<high){
		int k=partition(array,low,high);
		quickSort(array,low,k-1);
		quickSort(array,k+1,high);
	}
  // write this by yourself.
}

int main(){
	input_data();
	for(int i=1;i<=n;i++)
		if(!index[i]) tarjan_scc(i);
	
	quickSort(size,0,tComponent-1);
    for(int i=0;i<tComponent;i++) printf("%d ",size[i]);
	return 0;
} 

