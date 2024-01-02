//将大写字母转换为小写字母
//输入一个字符，判别它是否为大写字母，如果是，转换成小写字母，如果不是，不转换。
#include  "stdio.h"
int main() 
{
	char ch; //declare a char
	scanf("%c",&ch); //input
	ch=(ch>='A' && ch <='Z') ? (ch+32) : ch; //if ch is a capital letter,then ch+=32,else ch=ch,if (ch>='A' && ch <='Z') is true,then first situation, else second
	printf("%c",ch);
	return 0;
}
//reminders ,use' ' to declare a char,'A' is smaller than 'a' in ASCII code,and 'a'-'A'=32