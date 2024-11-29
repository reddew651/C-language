//定义结构体类型STUDENT，用于描述学生信息如下：学号（长整型）、姓名（字符串）、年龄（整型），英语、数学、语文等3科的成绩（均为实型），总分（实型）、平均分（实型）。

//主程序输入3个学生信息，计算每个学生的总分、平均分，然后输出总分最高的学生姓名。

#include <stdio.h>
#include <string.h>
struct STUDENT
{
	long int num;
	char name[10];
	int age;
	int eng;
	int math;
	int chi;
}STUDENT[3];//define a struct array
int main()
{
	int sum = 0, order = 0;
	for (int i = 0;i < 3;i++)//input the information of the students
		scanf("%ld%s%d%d%d%d", &STUDENT[i].num, STUDENT[i].name, &STUDENT[i].age, &STUDENT[i].eng, &STUDENT[i].math,&STUDENT[i].chi);
	for (int i = 0;i < 3;i++)
		if ((STUDENT[i].eng + STUDENT[i].math + STUDENT[i].chi) > sum)
		{
			sum = (STUDENT[i].eng + STUDENT[i].math + STUDENT[i].chi);
			order = i;//get the number of the hightest score
		}
	printf("%s", STUDENT[order].name);//print the name of the hightest score
	return 0;
}