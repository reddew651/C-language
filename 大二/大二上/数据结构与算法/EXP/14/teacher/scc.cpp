#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

const int maxn=50000;
const int maxm=500000;

int n,m;

int a[maxm + 1], b[maxm + 1];
int p[maxn + 2];
int linkto[2 * maxm + 1];
//p ��linkto ��һά������ �洢�����ڽӱ��ϲ���һά���飬 p[v]+1...p[v+1] ��Щλ�ô洢v��ֱ�Ӻ�̡� 
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
int index[maxn];
int low[maxn];
int stack[maxn],top=0;
int in_stack[maxn];

int tComponent=0;
int size[maxn];   // ÿ��ǿ��ͨ�� �������ٶ��㡣  tComponent�ǵ�ǰ�ҵ���ǿ��ͨ������� 

void tarjan_scc(int v){
	index[v]=low[v]=count++;
	stack[top++]=v;
	in_stack[v]=1;
	for(int i=p[v]+1;i<=p[v+1];i++){
		int w=linkto[i];
		if(!index[w]){
			tarjan_scc(w);
			low[v]=min(low[v],low[w]); 
		}
		else if (in_stack[w]) low[v]=min(low[v],index[w]);
	}
	if(index[v]==low[v]){
		int j;
		do{
			j=stack[--top];
			in_stack[j]=0;
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
    if (array[j] > pivot){
      swap(array[i], array[j]); i++;
    }
  }
  swap(array[i], array[high]);
  return (i);
}
void quickSort(int array[], int low, int high) {
  if (low < high) {
    int k = partition(array, low, high);
    quickSort(array, low, k - 1);
    quickSort(array, k + 1, high);
  } 
}

int main(){
	input_data();
	for(int i=1;i<=n;i++)
		if(!index[i]) tarjan_scc(i);
	
	quickSort(size,0,tComponent-1);
    for(int i=0;i<tComponent;i++) printf("%d ",size[i]);
	return 0;
} 

