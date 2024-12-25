//提示用户输入分钟数（例如10000000），然后显示这些分钟代表多少年和多少天。为了简化问题，假设一年有365天，不足1天按1天算。
//for example,there are 60*24*365+60*24+1 minutes,when calculate the year,the answer is 1,when calculate the day,we should minus the minutes of a year
#include "stdio.h"
int main(void) 
{
	long int m,y,d,m1; //declare a long interger
	scanf("%ld",&m);
	y=m/60/24/365;//calculate the year
	d=(m-y*365*24*60)/60/24;//y is an interger,so the reminderis the day
	m1=m-y*365*24*60-d*60*24;//calculate the minutes
	if(m1>0) 
		d++;
	printf("%ld年%ld天",y,d);
}

#include <stdio.h>
int main()
{
	long int m,d,m,y,reminder;
	scanf("%d",&m);
	y=m/60/24/365;
	d=m/60/24%365;
	reminder=m%(60*24);
		if (reminder>0)
		d++;
	printf("%ld%ld",y,d);
	return 0;
}
