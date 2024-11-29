#include<stdio.h>
int main()
{
    char str[100];
    fgets(str,sizeof(str),stdin);
    void Longest(char str[],char maxstr[]);
    char maxstr[100];
    Longest(str,maxstr);
    printf("%s",maxstr);

}

void Longest(char str[],char maxstr[])
{
    int currl=0,maxl=0,currs=0,maxs=0;
    int i=0,j=0;
    for (i=0;str[i];i++)
    {
        if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z'))
        {
            if (currl==0)
            {
                currs=i;
            }
            currl++;
        }
        if (currl>maxl)
        {
            maxl=currl;
            maxs=currs;
        }
        if (str[i]==' ')
        {
            currl=0;
        }
    }
    int m,n;
        for (m=maxs,n=0;m<maxs+maxl;m++,n++)
        {
            maxstr[n]=str[m];
        }
}