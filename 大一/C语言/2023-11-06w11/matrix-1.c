#include  "stdio.h"
int main() 
{
	int a[3][3]={{1,2,3},{4,5,6},{7,8,9}},sum=0;//define a 3*3 matrix
	int i,j;
	for (i=0; i <3; i++)
		sum=sum+a[i][i];//add the number in the diagonal
	printf("%d\n",sum);
	return 0;
}