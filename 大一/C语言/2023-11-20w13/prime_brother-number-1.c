//寻找[0,100]区间内所有的孪生素数并输出。孪生素数是指差为2的两个素数，例如，3和5，5和7。
#include <stdio.h>
int main()
{
	int prime(int);
	int n;
	for (n = 1;n <= 100;n++)//循环
		if (prime(n) && prime(n + 2))
			printf("%d,%d\n",n,n+2);
	return 0;
}
//use i*i<=n 
int prime(int n)
{
	int flag = 1, i;
	for (i = 2;i < n && flag == 1;i++)//n/2 when enconter 4,flag=1,and enconter 2,flag=1,so I got wrong answer,2 and 4 are prime number
		if (n % i == 0)//if n can be divided by i,then it is not a prime number
			flag = 0;//不是素数
	return(flag);
}