//将一个字符串中的元音字母复制到另一个字符串
//写一个函数，其功能是：将一个字符串中的元音字母复制到另一个字符串。
//在主函数中输入字符串，调用自定义函数，然后在主函数中输出处理后的字符串。
#include <stdio.h>
int main()
{
	void cpy(char [],char []); //declare the function
	char str[80],c[80]; //declare the variables
	scanf("%s",str);
	cpy(str, c); //call the function
	printf("%s\n", c);
	return 0;
}
void cpy(char d[],char b[] )  //design the function
{
	int i, j;
	for (i = 0,j=0;d[i]!='\0';i++) //copy the string for the detailed requirement，remember to use d[i]!='\0' to prevent the program from copying the '\0' at the end of the string
		if (d[i] == 'a' || d[i] == 'e' || d[i] == 'i' || d[i] == 'o' || d[i] == 'u')
        {
            b[j]=d[i]; //copy the required result
            j++;
        }
        b[j]='\0';//add '\0' at the end of the string
}