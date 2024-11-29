//连接字符串
//编一程序，将两个字符串连接起来，不要用strcat函数
#include <stdio.h>
#include <string.h>
int main()
{
	int i = 0, j = 0;
	char a[20], b[10];  //两个数组
	scanf("%s", a);
	scanf("%s", b);

	while (a[i] != '\0') //当a不等于0的时候,the '\0' is the end of the string, so we need to use it to end the loop
		i++;//actually is to get the length of the string
	while (b[j] != '\0')//当b不等于0的时候
		a[i++] = b[j++]; //相等对应
	a[i] = '\0'; // Ensure the string is null-terminated
	puts(a);
	return 0;
}