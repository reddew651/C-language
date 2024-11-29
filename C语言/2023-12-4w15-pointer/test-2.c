#include <stdio.h>
#include <string.h>
int main()
{
    char str1[30],str2[20];
    int n;
    scanf("%s",str1);
    scanf("%s",str2);
    scanf("%d",&n);
    void insert(char str1[],char str2[],int n);
    insert(str1,str2,n);
}

void insert(char str1[],char str2[],int n)
{
    int i,m=strlen(str2),j=strlen(str1);//here you should strlen the str1
    for (i=j-1;i>=n;i--)//start from the end of the str1, or you will cover some number
    {
        str1[m+i]=str1[i];
    }
    for (i=0;i<m;i++)
    {
        str1[n+i]=str2[i];
    }
    str1[m+j]='\0';//the end of the string is '\0' not '0' [zero
    printf("%s",str1);
}