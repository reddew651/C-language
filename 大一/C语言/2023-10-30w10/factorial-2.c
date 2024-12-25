//count the sum of the factorial
#include <stdio.h>
int main()
{
    int i,n;
    unsigned long long sum=1;//remember if the number is too big, use unsigned long long rather than int
		unsigned long long count=0;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
  			sum=sum*i;//calculate the factorial
				count+=sum;
		}
    printf("%llu",count);
    return 0;
}
//unsigned means the number is positive,the variable can't be nagative