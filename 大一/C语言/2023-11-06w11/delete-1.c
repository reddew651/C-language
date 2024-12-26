//删除数组中重复出现的数据
//键盘输入一个长度为10的int型数组，删除数组中重复出现的数据
//如，原数组是： 1 4 2 3 4 1 2 5 5 9，输出：1 4 2 3 5 9
#include <stdio.h>
int main()
{
    int a[10],i,j;//declare the variable
    for (i=0;i<10;i++)
    scanf("%d",&a[i]);
    for (i=0;i<10;i++)
    {
        for (j=i+1;j<10;j++)//the important point is j=i+1,reduce the circle times becuase it will delete the wanted number
        {
            if (a[i]==a[j])
            {
                a[j]=0;
            }
        }
    }
    for(i=0;i<10;i++)
    if (a[i]!=0)
    printf("%d ",a[i]);
}