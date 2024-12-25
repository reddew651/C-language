//show how to calculate the factorial
#include <stdio.h>
int main ()
 {
   int i,t; //declare the variable
   t=1; //t is the result of the factorial
   i=2;
   while(i<=5) //use the while loop to calculate the factorial
   {
     t=t*i; //you can use t*=i to replace t=t*i
     i=i+1;
   }
   printf("%d\n",t);
  return 0;
}