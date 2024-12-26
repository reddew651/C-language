//数字操作
//输入一个不多于5位的正整数，要求：
//求出它是几位数
//分别输出每一位数字
//按逆序输出各位数字，例如原数为321，应输出123
#include  "stdio.h"
#include  "math.h"
int main() 
{
	int num,indiv,ten,hundred,thousand,ten_thousand,place;      
	scanf("%d",&num);
	if (num>9999)
		place=5;
	else  if (num>999)
		place=4;
	else  if (num>99)
		place=3;
	else  if (num>9)
		place=2;
	else 
place=1;
	printf("位数:%d\n",place);
	printf("每位数字为:");
	ten_thousand=num/10000;
	thousand=num/1000%10;
	hundred=num/100%10;
	ten=num/10%10;
	indiv=num%10;
	switch(place) {
		case 5:
			printf("%d,%d,%d,%d,%d",ten_thousand,thousand,hundred,ten,indiv);
			printf("\n反序数字为:");
			printf("%d%d%d%d%d\n",indiv,ten,hundred,thousand,ten_thousand);
			break;
		case 4:
			printf("%d,%d,%d,%d",thousand,hundred,ten,indiv);
			printf("\n反序数字为:");
			printf("%d%d%d%d\n",indiv,ten,hundred,thousand);
			break;
		case 3:
			printf("%d,%d,%d",hundred,ten,indiv);
			printf("\n反序数字为:");
			printf("%d%d%d\n",indiv,ten,hundred);
			break;
		case 2:
			printf("%d,%d",ten,indiv);
			printf("\n反序数字为:");
			printf("%d%d\n",indiv,ten);
			break;
		case 1:
			printf("%d",indiv);
			printf("\n反序数字为:");
			printf("%d",indiv);
			break;
	}
	return 0;
}
//there is a nice way to solve this problem, when you want to know the certain nuber,use num/1000%10 to get it 
//for example, count the thousand's digit,use num/1000%10 to get it