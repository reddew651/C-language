//哥德巴赫猜想
//德巴赫猜想：任何一个大于4的偶数都可以表示为两个素数之和。验证[6,50]之间的偶数
//写函数void guest(int n)，找到并输出所有素数对，每个素数对之和均等于偶数n。
//编写main函数，遍历[6,50]间所有的偶数，调用guest函数查找并输出素数对。

//some prombles
#include <stdio.h>
int main()
{
  int prime(int n);
	int n, b;
	for (b = 6;b <= 50;b += 2)
	{
		for (n = 3;n <= 50;n++)
			if (prime(n) && prime(b - n) && b > n && b - n != 1 && n <= b - n)
				printf("%d=%d+%d ", b, n, b - n);
		printf("\n");
	}
	return 0;
}

int prime(int n)
{
	int flag = 1, i;
	for (i = 2;i <= n/2 && flag == 1;i++)//the question is n/2，but change <= can run
		if (n % i == 0)
			flag = 0;
	return(flag);
}

