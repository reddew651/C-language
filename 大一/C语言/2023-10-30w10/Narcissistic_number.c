//this is to find all the narcissistic numbers in a given range
#include<stdio.h>
int main()
{
	int a, b, c;
	for (int i = 100;i <= 999;i++)//three digits ,find all three digits whether is narcissistic number
	{
		a = i / 100;
		b = i / 10 % 10;
		c = i % 10;
		if (a * a * a + b * b * b + c * c * c == i)
			printf("%d ", i);

	}
	return 0;
}