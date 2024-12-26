//使用字符指针编写程序，输入一个长度为n的字符串a，在字符串a的i （0＜i＜n）处插入字符x，输出插入后的字符串a。
//n，x，i的值可自由输入
#include <stdio.h>
#include <string.h>
int main()
{
	int len = 0, n = 0;
	char* p;//define a pointer
	char str[100] = { 0 };//set the string to 0
	p = str;//point to the first element of the string
	fgets(str, sizeof(str), stdin);//input the string
	len = strlen(str);//get the length after input!!!!
	scanf("%d", &n);
	for (int i =0;i<len-n ;i++)
	{
		*(p+len  - i) = *(p + len - i-1);//move the string to the right
	}
	scanf(" %c", &str[n]);
	str[len + 1] = '\0';//remember to add the end of the string
	puts(str);
} 
