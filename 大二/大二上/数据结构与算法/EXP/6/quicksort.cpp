#include <stdio.h>
#include <cstdlib>
#pragma comment(linker, "/STACK:1073741824")

const int maxn=1000001;
int A[maxn];

void swap(int &a, int &b) {
  int c = a; a = b; b = c;
}

int partition(int arr[], int low, int high) {
  int random = low + rand()%(high-low+1);
  swap(arr[random],arr[high]);
  int i = low;
  int pivot= arr[high];
  for (int j = low; j < high; j++) {
  	if (arr[j]<= pivot){
  		swap (arr[j],arr[i++]);
	  } 
    //add something here
  }
  swap (arr[i],arr[high]);
  return i;
  //add something here
}

void quickSort(int arr[], int low, int high) {
  if (low < high) {
    int k = partition(arr, low, high);
    quickSort(arr,low,k-1);
    quickSort(arr,k+1,high);
    //add something here
	//add something here
  }
}

int main() {
  int n;
  scanf( "%d", &n);
  for (int i=0; i<n; i++) scanf("%d", &A[i]);

  quickSort(A, 0, n-1); //change this sentence
  
  for (int i=0; i<n; i++) printf("%d ", A[i]);
  return 0; 
}
