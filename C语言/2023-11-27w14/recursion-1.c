#include <stdio.h>
int main()
{
	double p(int n, int x); //claim the function
	int n, x; //declare the variables
	scanf("%d %d", &n,&x); //input the variables
	printf("%.2lf", p(n, x)); //output the result
	return 0;

}
double p(int n, int x) //define the function
{
	double i = 0;   //declare the variable
	if (n == 0) //the condition of the recursion
		i = 1; //the result of the recursion
	else if (n == 1) //another situation
		i = x;
	else i = ((2 * n - 1) * x * p(n - 1, x) - (n - 1) * p(n - 2, x)) / n;
	return (i); //return the result
}