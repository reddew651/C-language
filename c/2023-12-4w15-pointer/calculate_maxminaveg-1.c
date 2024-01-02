//编写函数计算一维实型数组前n个元素的最大值、最小值和平均值。
//数组、n、最大值、最小值和平均值均作为函数形参，函数无返回值；
//在主函数中输入数据，调用函数得到结果。（要求用指针方法实现）
#include <stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    int a[n];
    for (int i=0;i<n;i++)
    scanf("%d",&a[i]);
    void diulei(int *a,int n);//declare the diulei function
    diulei(a,n);
}
void diulei(int *a,int n)//int *a is a array
{
    float max,min,aveg,sum;
    int *p;//declare the poninter
    max=*a;//the first element is the max
    min=*a;
    sum=0;
    for (p=a;p<a+n;p++)//p=a is the first element
    {
        if (*p>max)
        max=*p;
        if (*p<min)
        min=*p;
        sum+=*p;
    }
    aveg=sum/n;
    printf("max:%.2f\nmin:%.2f\naveg:%.2f\n",max,min,aveg);
}
