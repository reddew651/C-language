//求应发奖金总数，保留两位小数
//企业发放的奖金根据利润提成。
//利润I低于或等于100000元的，奖金可提成10%；
//利润高与100000元，低于200000元（100000≤ I ≤200000）时，低于100000元的部分按10%提成，高于100000的部分，可提成7.5%；
//200000＜I  ≤400000时，低于200000元的部分仍按上述办法提成（下同）。高于200000元的部分按5%提成；
//400000＜I ≤600000元时，高于400000元的部分按3%提成；
//600000＜ I ≤1000000时，高于600000元的部分按1.5%提成；
//I＞1000000时，超过1000000元的部分按1%提成。从键盘输入当月利润I，求应发奖金总数，保留两位小数。用switch语句编写程序。
#include  "stdio.h"
int main() 
{
	int i;
	double bonus,bon1,bon2,bon4,bon6,bon10;
	bon1=100000*0.1;
	bon2=bon1+100000*0.075;
	bon4=bon2+200000*0.05;
	bon6=bon4+200000*0.03;
	bon10=bon6+400000*0.015;
	scanf("%d",&i);
  switch( i / 100000) //switch means switch many cases
  {
    case 0://remember to use : after case
      bonus=i*0.1;
      break;//break means jump out of the switch
    case 1:
      bonus=bon1+(i-100000)*0.075;
      break;

    case 2://if there are nothing after case,then it will run the next case
    case 3:
		  bonus=bon2+(i-200000)*0.05;
      break;
    case 4:
    case 5:
		  bonus=bon4+(i-400000)*0.03;
	    break;
    case 6:
    case 7:
    case 8:
    case 9:
		  bonus=bon6+(i-600000)*0.015;
      break;
    default ://default means if there are no case can be run, there will run default
      bonus=bon10+(i-1000000)*0.01;
  }
	printf("%.2f",bonus);
	return 0;
}
//the difference between break and continue is that break will jump out of the loop,continue will jump out of the loop and run the next loop