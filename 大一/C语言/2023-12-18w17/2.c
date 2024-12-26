//编写程序，定义结构体类型PERSON，含有四个成员：姓名，基本工资，浮动工资，支出。

//定义结构体数组leader[3]，存放下表中的数据（姓名，基本工资，浮动工资）。键盘输入每个人的支出，然后计算并输出每人的姓名和工资实发数（=基本工资＋浮动工资-支出）。
#include <stdio.h>
#include <string.h>
struct Person
{
	char name[10];
	double bas;
	double flo;
	double cost;
}man[3] = { "zhao",240,420,0,"qian",360,120,0,"sun",560,0,0 };//set the 3 mans
int main()
{
	int i;
	for (i = 0;i < 3;i++)
		scanf("%lf", &man[i].cost);//puts the cost of 3 mans 
	for (i = 0;i < 3;i++)
		printf("%s:%.2lf\n", man[i].name, man[i].bas + man[i].flo - man[i].cost);//print their whole money
	return 0;
}