#include <stdio.h>
int main()
{
    int funn(int *p1,int *p2,int *p3);
    int a[3],i;
    for (i=0;i<3;i++)
    {
        scanf("%d",&a[i]);
    }
    funn(&a[0],&a[1],&a[2]);
}
int funn(int *p1,int *p2,int *p3)
{
    int i,count=0,product=1;
    for (i=0;i<3;i++)
    {
        if(*(p1+i)%5==0)
        {
            count++;
            product*=*(p1+i);
        }
    }
    if (count==0)
    {
        product=0;
    }
    *p2=count;
    *p3=product;
    printf("%d %d\n",*p2,*p3);
    return 0;

}