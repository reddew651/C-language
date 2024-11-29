//字符反序输出
//写一个函数，使输入的一个字符串按反序存放，在主函数中输入和输出字符串
#include <stdio.h>
#include <string.h>
int main()
{
	void convert(char a[]);
	char a[100]={0};
	scanf("%s", a);
	convert(a); //call the funciton
	printf("%s", a); //print the result
	return 0;
}
void convert(char a[]) //define the function
{
	//i is the index variable for the beginning of the string
	//j is the index variable for the end of the string
	//t is a temporary character used to swap characters
	int i,j;
	char t;
	//loop through the string from the beginning to the middle
	for (i = 0,j=strlen(a);i < strlen(a)/2;i++,j--)//use strlen(a)/2 to prevent the string from being swapped back
	{
		//swap the character at the beginning of the string with the character at the end of the string
		t = a[i];
		a[i] = a[j - 1];//use j-1 because the index of the last character is strlen(a)-1
		a[j - 1] = t;

	}
}