//输入字符串，要求将每个单词的第一个字母改为大写字母，并输出。
//如“hello world！”改为“Hello World”
#include <stdio.h>
#include <string.h>
int main()
{
	char str[100] = { 0 };//define a string 
	gets(str);
    int len = strlen(str);//get the length after input!!!!1
	char* p;//define a pointer
	p = str;//point to the first element of the string
    if (*p >= 'a'&&*p <= 'z')//solve the first letter 
        *p=*p-32;//change the first letter to upper case
	for (int i = 0;i < len;i++)
		if (*(p + i) == ' '&&*(p + i + 1) >= 'a'&&*(p + i + 1) <= 'z')//check if the current char is the same as the target char
        *(p + i+1) = *(p + i+1) - 32;//change the first letter to upper case
	puts(str);
	return 0;
}