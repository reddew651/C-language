//用选择排序法对10个整数进行排序[1,12,4,9,10,22,-7,0,99,8]
#include <stdio.h>
int main()
{
    int a[10] = {1, 12, 4, 9, 10, 22, -7, 0, 99, 8};
    int i,j,t;
    for (i=0;i<9;i++)
    {
        for (j=i+1;j<10;j++)
        {
            if (a[i]>a[j])
            {
                t=a[i];
                a[i]=a[j];
                a[j]=t;
            }
        }
    }
    for (i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
}