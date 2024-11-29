//编写函数fun(int *p1,int *p2,int *p3)，
//其功能是：求p1所指一维数组中的所有能被5整除的数的个数以及这些所有能被5整除的数的积；
//分别将所求得的个数以及积通过指针p2和p3返回主函数。
//主函数中，由键盘输入3个整数存入一维数组, 调用函数fun后, 在主函数输出最后的结果
//输入: 10 2 5
//输出: 2  50
#include <stdio.h>
int main()
{
    int fun(int *p1,int *p2,int *p3);
    int a[3],i;
    for (i=0;i<3;i++)
    scanf("%d",&a[i]);
    fun (a,&a[1],&a[2]);//*p1=a,*p2=a[1],*p3=a[2],a means the address of the first element of the array, which is the same as &a[0]
}
int fun(int *p1,int *p2,int *p3)
{
    int i,count=0,product=1;
    for (i=0;i<3;i++)
    {
        if (*(p1+i)%5==0)
        {
            count++;//count the number of elements that can be divided by 5,but when meet 0, it will be counted as well
            product*=*(p1+i);//calculate the product of the elements that can be divided by 5,*p1+i is the value of the element
        }
    }
    if (count==0)
    product=0;
    *p2=count;//now p2 is pointing to the address of count
    *p3=product;//now p3 is pointing to the address of product
    printf("%d %d\n",*p2,*p3);
    return 0;
}