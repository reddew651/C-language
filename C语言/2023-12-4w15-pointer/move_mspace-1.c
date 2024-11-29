//有5个整数，使前面各数顺序向后移m个位置，
//最后m个数变成最前面m个数，写一个函数实现以上功能，在主函数中输入5个整数和输出调整后的5个数
//1 2 3 4 5 1
//5 1 2 3 4
#include <stdio.h>
int main()
{
    int a[5],n;
    for (int i=0;i<5;i++)
    scanf("%d",&a[i]);
    scanf("%d",&n);
    void move(int *a,int n);
    move(a,n);
}
void move (int *a,int n)//*a=a[0]
{
    int i,j,temp;
    int *p;//set a pointer
    p=a;//p=a[0]
    for (i=0;i<n;i++)//move n times
    {
        for (j=4;j>0;j--)
        {
            temp=*(p+j);
            *(p+j)=*(p+j-1);
            *(p+j-1)=temp;
        }
    }
    printf("%d %d %d %d %d",*a,*(a+1),*(a+2),*(a+3),*(a+4));
}