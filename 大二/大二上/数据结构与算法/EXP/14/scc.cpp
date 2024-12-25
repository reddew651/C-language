#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

const int maxn=50000;
const int maxm=500000;

int n,m;

int a[maxm + 1], b[maxm + 1];
int p[maxn + 2];
int linkto[2 * maxm + 1];
/*p ��linkto ��һά������ �洢�����ڽӱ� (ʹ�÷��㣬�����ö�̬���飩 
 linkto ���һά�����   p[v]+1...p[v+1] ��Щλ�ô洢v��ֱ�Ӻ�̡� 
 ��ͨ���Ķ�������κ����Ĵ��룬������p��linkto  */ 
void input_data() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d %d", &a[i], &b[i]);
	for (int i = 1; i <= m; i++) p[a[i]]++;	
	for (int i = 1; i <= n; i++) p[i] = p[i] + p[i - 1];//�൱��ָ�룬�������
	p[n + 1] = p[n];  //trick ��һ��ָ��ָ�����һ��Ԫ��
	for (int i = 1; i <= m; i++) {//�����ڽ�����
		linkto[p[a[i]]] = b[i];
		p[a[i]]--;
	}
}

int min(int a,int b){
	return a<b ? a:b; 
}

int count=0;
int inde[maxn];
int low[maxn];
int stack[maxn],top=0;
int in_stack[maxn];

int tComponent=0; // tComponent�ǵ�ǰ�ҵ���ǿ��ͨ������� 
int size[maxn];   // size[i]�����i��ǿ��ͨ�� �Ķ��������   

void tarjan_scc(int v){  // SCC������! 
	inde[v]=low[v]=count++;
	stack[top++] = v;
	in_stack[v] = 1;
	// push v into the stack and mark v to be on stack.
	for(int i=p[v]+1;i<=p[v+1];i++){
		int w=linkto[i];
		if(!inde[w]){
			tarjan_scc(w);
			low[v] = min(low[v],low[w]);
		}
		else if(in_stack[w]) low[v] = min(low[v],inde[w]);
		//add some code here by yourself
		//Hint 1. dfs. Hint 2. modify low[v]
	}
	if(inde[v]==low[v]){ // find out a new component. 
		int j;
		do{
			j = stack[--top];
			in_stack[j] = 0;
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
  	if (array[j] <= pivot){
  		i++;
  		swap (array[i], array[j]);
	  }
    //fill this part by yourself.
  }
  swap(array[i], array[high]);
  return (i);
}
void quickSort(int array[], int low, int high) {
	if (low < high){
		int pi = partition(array, low, high);
		quickSort(array,low,pi-1);
		quickSort(array,pi+1,high);
	}
  // write this by yourself.
}

int main(){
	input_data();
	for(int i=1;i<=n;i++)
		if(!inde[i]) tarjan_scc(i);
	
	quickSort(size,0,tComponent-1);
    for(int i=0;i<tComponent;i++) printf("%d ",size[i]);
	return 0;
} 

