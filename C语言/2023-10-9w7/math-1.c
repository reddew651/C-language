#include "stdio.h"
#include "math.h" 
int main()
{
	double x,y; //double is used to declare a decimal number
	scanf("%lf%lf",&x,&y); //%lf is used to read a long float number,and remember to use &before 
	printf("sin(x):%0.2lf\n",sin(3.1415938*x/180));//use pi/180 to convert the angle from degree to radian
	printf("cos(x):%0.2lf\n",cos(3.141593*x/180));
	printf("|x|:%0.2lf\n",fabs(x)); //fabs is used to get the absolute value
	printf("e的x次方:%0.2lf\n",exp(x)); //exp means exponential
	printf("x的y次方:%0.2lf",pow(x,y));
}