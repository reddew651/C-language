//编一个程序，将两个字符串s1和s2比较，若s1>s2，输出一个正数；
//若s1=s2，输出0；若s1<s2，输出一个负数。不要用strcpy函数。两个字符串用gets函数读入。
//输出的正数或负数的绝对值是相比较的两个字符串第一个不同的相应字符的ASCII码的差值。
//例如“A”与“C”比，由于“A”<“C”，应输出负数，同时由于两者ASCII码差值为2，因此应输出-2。
//同理，“And”和“Aid”比较，根据第二个字符比较结果，‘n’比‘i’大5，因此输出5
#include  "stdio.h"
int main() 
{
	int i,resu;
	char s1[100],s2[100];
	scanf("%s",s1);
	scanf("%s",s2);
	i=0;
	while ((s1[i]==s2[i]) && (s1[i]!='\0')) i++;
	if (s1[i]=='\0' && s2[i]=='\0')
		resu=0;
	else
		resu=s1[i]-s2[i];
	printf("result:%d",resu);
	return 0;
}