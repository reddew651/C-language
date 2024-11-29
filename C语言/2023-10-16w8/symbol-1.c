//输出浮点数的符号、整数部分和小数部分
//编写程序，从键盘输入一个不等于0的浮点数，然后分别输出这个浮点数的符号、整数部分和小数部分。例如输入-123.456，输出应该是（按下列格式输出）：
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
int main()
{
	double a;
	int b;
	double c;
	scanf("%lf",&a);
	printf("sign:%c\n",a<0?'-': '+'); //if a<0,then print '-
	b=abs((int)a); //fabs means absolute value,(int)a means transform double a to int a
	printf("integral part:%d\n",b);
	c=a>0? a-b:fabs((a+b));
	printf("decimal fraction part:%lf",c);
}
// Path: c/2023-10-16/2/symbol-2.c
//care,fabs used in float,abs used in int,when use ,add abs #include "stdlib.h"