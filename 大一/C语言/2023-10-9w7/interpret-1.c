#include <stdio.h>
int main()
{
	char c1='C',c2='h',c3='i',c4='n',c5='a'; //char is used to declare a character, and you can use ' ' to represent a character
    c1+=4; //c1++ means c1=c1+1, so c1+=4 means c1=c1+4
    c2+=4;
    c3+=4;
    c4+=4;
    c5+=4;
	printf("%c%c%c%c%c\n", c1, c2, c3, c4, c5);
	return 0;
}