#include <iostream>

long long int k = 0; //全局变量 
int a[1100000];
int b[1100000];
long long int MergeSort(int s[], int left, int middle, int right)
{
   int i = left, j = middle;
   int index = 0;
   long long int sum = 0;
   int t = 0;
   while (i < middle && j <= right)
   {
       /* do something
         ...
		  */ 
   }

   while (i < middle)
       // do something 
   while (j <= right)
       // do something

   index = 0;
   for (int m = left; m <= right; m++)
       s[m] = b[index++];
   return sum ;//最后返回给k值
}


void Merge(int s[], int low, int high)
{
   if (low < high)
   {
       int mid = (low + high) / 2;
       // do something
       // do something
       k += MergeSort(?, ?, ?, ?);
   }
}

int main()
{    
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
        
   Merge(a, 0, n - 1);
   printf("%lld\n", k);
   return 0;
}

