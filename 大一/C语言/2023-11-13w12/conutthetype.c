//计算各类型字符个数
//有一篇文章，共有3行文字，每行小于80个字符。要求分别统计出其中英文大写字母、小写字母、数字、空格以及其他字符的个数
#include <stdio.h>
#include <string.h>
int main()
{
	int i, j, upper = 0, lower = 0, digit = 0, space = 0, other = 0;  //初始化各数字
	char text[3][80];
	for (i = 0;i <= 2;i++)
	{
		fgets(text[i], sizeof(text[i]), stdin);//sizeof is to get the size of the array, remember to add '\0',for example ,the size of "hello" is 6
		for (j = 0;j <= 80 && text[i][j] != '\0';j++)     //循环80次，直到遇到'\0'结束
			if (text[i][j] >= 'a' && text[i][j] <= 'z')    //如果在小写字母范围内
				lower++;     //最小的数字+1
			else if (text[i][j] >= 'A' && text[i][j] <= 'Z')
				upper++;
			else if (text[i][j] >= '0' && text[i][j] <= '9')
				digit++;
			else if (text[i][j] == ' ')
				space++;
			else
				other++;

	}
	printf("upper case:%d\n", upper);   //输入各数字
	printf("lower case:%d\n", lower);
	printf("digit:%d\n", digit);
	printf("space:%d\n", space);
	printf("other:%d\n", other);
	return 0;
}