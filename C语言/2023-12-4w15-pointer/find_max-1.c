//数组中的最⼤值所在的元素下标（要求利用指针作为函数的参数）
//在主函数中，从键盘上输⼊5个数据到⼀维数组中。编写函数int max(int *p)，
//功能为：找出数组中的最⼤值所在的元素下标。在主函数中调用max函数，并输出数组中的最⼤值所在的元素下标。
//1 2 3 4 5
//最大值下标:4
#include <stdio.h>
int main()
{
    int max(int *p);
    int a[5],i;
    for (i=0;i<5;i++)
    scanf("%d",&a[i]);
    printf("最大值下标:%d\n",max(a));
}
int max(int *p)//pointer is to point to the array
{
    int i,max=0;
    for (i=0;i<5;i++)
    {
        if (*(p+i)>*(p+max))//*(p+i) is the value of the array
        max=i;//save the index of the max value
    }
    return max;
}