//find the greatest divisor and lowest multiple of two numbers
#include <stdio.h>
int main()
{
    int a,b,c,r,q;
    scanf("%d %d",&a,&b);
    q=a*b;
    if (a<b)//make sure a>b
    {
        c=a;
        a=b;
        b=c;
    }
    while (b!=0)//Euclidean algorithm
    {
        r=a%b;
        a=b;
        b=r;
    }
    printf("%d %d",a,q/a);//q/a is the lowest multiple
    return 0;
}
