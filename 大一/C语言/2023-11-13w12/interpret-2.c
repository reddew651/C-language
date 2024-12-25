//输入一行电文，已按下面规律译成密码：
//A->Z	a->z
//B->Y	b->y
//C->X	c->x
//即第1个字母变成第26个字母，第i个字母变成第(26-i+1)个字母，非字母字符不变。要求编程序将密码译回原文，并输出原文。
#include  "stdio.h"
int main() 
{
	int j,n;
	char ch[80],tran[80];
	fgets(ch,sizeof(ch),stdin);
	j=0;
	while (ch[j]!='\0') //here is the important part, the '\0' is the end of the string, so we need to use it to end the loop
    {
		if ((ch[j]>='A') && (ch[j] <='Z'))
			tran[j]=155-ch[j];//155 is the ASCII code of 'A'+'Z'
		else if ((ch[j]>='a') && (ch[j] <='z'))
			tran[j]=219-ch[j];//219 is the ASCII code of 'a'+'z'
		else
			tran[j]=ch[j];
		j++;
	}
	
    n=j;//so now we get the length of the string,j is the length of the string
    tran[n] = '\0'; // Ensure the string is null-terminated
    puts(tran);
	return 0;
}