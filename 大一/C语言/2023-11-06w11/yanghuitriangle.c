//杨辉三角形
//输出一个以下的杨辉三角形，要求输出10行
#include  "stdio.h"
#define N  10//define N 10
int main() 
{
	int i,j,a[N][N]={0}; //set a[N][N] to 0
	for (i=0; i <N; i++)
	 {
		a[i][i]=1;
		a[i][0]=1;
	}
	for (i=2; i <N; i++)
		for (j=1; j <=i-1; j++)
			a[i][j]=a[i-1][j-1]+a[i-1][j];
	for (i=0; i <N; i++) 
	{
		for (j=0; j <=i; j++)
			printf("%d ",a[i][j]);//a[i][j]means the number in i row and j colume
		printf("\n");//when the upon loop is over,print a new line,there is loop in a loop
	}
	return 0;
}