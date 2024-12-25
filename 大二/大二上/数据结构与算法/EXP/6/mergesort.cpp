#include<stdio.h>
const int maxn=1000001;
int A[maxn];

void merge(int arr[], int left, int middle, int right){
	int i, j;
	int n1=middle-left+1, n2=right-middle;
	int L[n1], R[n2];
	for(i=0;i<n1;i++) L[i]=arr[left+i];
	for(j=0;j<n2;j++) R[j]=arr[middle+1+j];
	i = 0, j = 0;
	int k = left;
	while (i < n1 && j < n2){
		if (L[i] <= R [j]) {
			arr [k] = L[i];
			i++;
		}
		else{
			arr [k] = R[j];
			j++;
		}
		k++;
	}
	while (i<n1){
		arr[k] = L[i];
		i++,k++;
	}
	while (j<n2){
		arr[k] = R[j];
		j++,k++;
	}
   /* Please fill this part:
	merge (L[0],...,L[n1-1])  with  (R[0],...,R[n2-1]) and store the result (in sorted order) in arr[left],...,arr[right]. */
}

void mergesort(int arr[],int left, int right){
	if(left<right){
		int middle=(left+ right)/2;
		mergesort (arr,left,middle);
		mergesort (arr,middle+1,right);
		merge(arr, left, middle, right);
		//add something here. Think it by yourself.
	}
}

 int main() {
 	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d", &A[i]);
	
	mergesort(A,0,n-1); //edit this sentence

	for(int i=0;i<n;i++) printf("%d ", A[i]);
} 
