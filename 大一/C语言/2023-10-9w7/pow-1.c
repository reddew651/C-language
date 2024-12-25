#include<stdio.h>
#include<math.h>
int main()
{
	float r, p;
	r = 0.07;
	p = pow(1 + r, 10); //the pow function is used to calculate the power of a number such as 2^3, it means (1+r)^10
	p = p - 1; //
		printf("%.2f\n",p); //%.2f means the result will be printed with two decimal places
			return 0;
}