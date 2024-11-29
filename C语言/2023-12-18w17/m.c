#include <stdio.h>
#include <string.h>
int findlet(char* str, char* lea, int order)
{
	char* p=str;
	for (int i=0;i<strlen(str);i++)
	{
	if (*(p+i)==*lea)
	{
	order=i;
	break;
	}
	else 
	order=-1;
	}
	return order;
}
int main()
{
	char str[30],lea;
	int order=0;
	fgets(str,sizeof(str),stdin);
	scanf("%c",&lea);
	order=findlet(str, &lea, order);
	printf("%d",order);
	return 0;
}