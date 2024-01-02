//有n(比如n=3)个结构体变量，内含学生学号、姓名和3门课程的成绩。
//要求输出平均成绩最高的学生的信息(包括学号、姓名、3门课程成绩和平均成绩)。

#include "stdio.h"
#define N 3
struct student
{
	int num;
	char name[20];
	float score[3];
	float aver;
};
void input(struct student stu[])//define the input function
{
	int i;
	for (i = 0;i < N;i++)
	{
		scanf("%d %s %f %f %f", &stu[i].num, stu[i].name, &stu[i].score[0], &stu[i].score[1], &stu[i].score[2]);
		stu[i].aver = (stu[i].score[0] + stu[i].score[1] + stu[i].score[2]) / 3.0;
	}
}
struct student max(struct student stu[])//define the max function to get the max 
{
	int i, m = 0;
	for (i = 0;i < N;i++)
	if (stu[i].aver > stu[m].aver)
		m = i;
	return stu[m];

}
void print(struct student stud)
{
	printf("\n成绩最高的学生是:\n");
	printf("学号:%d\n姓名:%s\n三门课成绩:%.1f,%.1f,%.1f\n平均成绩:%6.2f\n", stud.num, stud.name, stud.score[0], stud.score[1], stud.score[2], stud.aver);

}
int main()
{
	struct student stu[N], * p = stu;//p=the address of the first stu
	input(stu);
	print(max(stu));
	return 0;

}
//16 4
//13 3
//15 4