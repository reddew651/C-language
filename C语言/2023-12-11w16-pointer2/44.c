#include  "stdio.h"
#include  "string.h"
void replace(char *str,char *fstr,char *rstr)
{
    char dest[100]={0};
    int flag=0,i,j,k;
    for (i=0; i <strlen(str);i++)
	{
        for (j=i,k=0;fstr[k]==str[j];k++,j++)
			if (fstr[k]=='\0') 
			{
				flag=1 ;
			}
        if (flag==1)
		{//找到一个源子串，用目的子串替换
            strcat(dest,rstr);
            i=i+k-1;
            flag=0;
        }else
		{//没找到源子串，将源串中该部分字符复制到目的串
            int l=strlen(dest);
            dest[l]=str[i];
        }
    }
    puts(dest);
    strcpy(str,dest);
}
int main()
{	char str[100],fstr[10],rstr[10];
    scanf("%s",str);
    scanf("%s",fstr);
    scanf("%s",rstr);
    replace(str,fstr,rstr);
    puts(str);
    return 0;
}