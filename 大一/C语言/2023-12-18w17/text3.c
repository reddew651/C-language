#include <stdio.h>
#include <string.h>
void findlet(char* str, char* let, int* order)
{
	char* p = str;
	for (int i = 0;i <strlen(str);i++)
	{
		if (*(p+i)==*let)//find the same char
		{
			*order = i;
			break;//if founded, break
		}
		else *order = -1;//or order =-1
	}
}
int main()
{
	char str[30], let;
	int order=0;
	fgets(str,sizeof(str),stdin);
	let=getchar();
	findlet(str, &let, &order);//get order
	printf("%d", order);
	return 0;
}