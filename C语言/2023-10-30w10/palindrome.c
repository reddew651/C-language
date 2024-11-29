#include  "stdio.h"
#include  "math.h"
int main()
{
	int i,j,k;
	for(i=100000;i <=999999;i++){
		j=i;
		k=0;
		while(j!=0){//fabulous!change the order of the digits,use a while loop
			k=k*10+j%10;
			j=j/10;
		}
		if(i==k&&(int)sqrt(i)==sqrt(i))//(int)sqrt(i)change the type of sqrt(i) to int
			printf("%d\n",i);
	}
}