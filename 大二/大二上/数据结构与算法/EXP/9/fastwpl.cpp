#include<stdio.h>
#include<stdlib.h>

int n , ans = 0; //nΪa��������������,ans�洢��� 
int a[50001],tmp[50001];
//a����Ϊn����ͬ����������tmp������������ 
int open = 0, closed = 0;
int next = 1;

int getMin(){
	int ret;
	
	if(next > n) ret = tmp[closed++];
	else if (closed >=open) ret = a[next++];
	else if (a[next]<tmp[closed]) ret = a[next++];
	else ret = tmp[closed++];
	return ret;
}
//�鲢���� 
void merge(int arr[], int left, int middle, int right){
	int i, j;
	int n1=middle-left+1, n2=right-middle;                     
	int L[n1], R[n2];
	for(i=0;i<n1;i++) L[i]=arr[left+i];
	for(j=0;j<n2;j++) R[j]=arr[middle+1+j];

	i=j=0;
	int k=left;
	while(i<n1 && j<n2)
		if(L[i]<=R[j]) arr[k++] = L[i++];
		else  arr[k++] = R[j++];
	while (i<n1) arr[k++] = L[i++];
	while (j<n2) arr[k++] = R[j++]; 
}

void mergesort(int arr[],int left, int right){
	if (left < right){
		int mid = (left + right)/2;
		mergesort(arr,mid+1,right);
		mergesort(arr,left,mid);
		merge(arr,left,mid,right);
	}
  // add some code here to conduct mergesort based on merge function 
}


int fastwpl(int a[]){
	int answer = 0;
	for(int i = 1; i<n; i++){
		int x = getMin();
		int y = getMin();
		tmp[open++] = x+y;
		answer += (x+y);
	}
	return answer;
}
    

int main(){	
    scanf("%d",&n);
    for(int i=1; i <=n; i++)scanf("%d",&a[i]); 
	mergesort(a,1,n);
	
	if(n==1)printf("%d",a[1]);
	else
		printf("%d",fastwpl(a)); 
	return 0;
}
