//another way
#include <stdio.h>
int main()
{	
	int test(int i);
	int i,j;
	for(i=1;i<=100;i++)//如果求[m,n]区间的孪生素数则改为for(i=m;i<=n;i++)
	{	
		if(test(i)==1)
		{
			j=i+2;
			if(test(j)==1)
				printf("%d,%d\n",i,j);
		}
	}
 } 
 int test(int i)
 {
 	int j;
 	for(j=2;j<=i;j++)
    {
 		if(i%j==0)
 		break;
        }
	 if(j<i) return 0;
	 else return 1;
 }