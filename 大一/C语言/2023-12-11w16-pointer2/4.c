//编写函数replace(char *str,char *fstr,char *rstr)，
//将str所指字符串中凡是与fstr字符串相同的字符替换成rstr（rstr与fstr的字符长度不一定相同）。
//从主函数中输入原始字符串"iffordowhileelsewhilebreak"、
//查找字符串"while"和替换字符串"struct"，调用函数得到结果。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* replace(char *str, char *fstr, char *rstr)//this is a pointer
{
    char *newstr = malloc(strlen(str) + 1);
    if (newstr == NULL) 
    {
        return NULL;
    }
    newstr[0] = '\0';

    for (int i = 0; i < strlen(str);)
    {
        if (strncmp(&str[i], fstr, strlen(fstr)) == 0)//compare the first n characters of two strings
        {
            strcat(newstr, rstr);
            i += strlen(fstr);
        }
        else
        {
            int len = strlen(newstr);
            newstr[len] = str[i];
            newstr[len + 1] = '\0';
            i++;
        }
    }
    return newstr;
}

int main()
{
    char str[100] = {0};
    scanf("%s", str);
    char fstr[100] ={0};
    scanf("%s", fstr);
    char rstr[100] = {0};
    scanf("%s", rstr); 
    char *result = replace(str, fstr, rstr);
    if (result != NULL) //if the pointer is not null
    {
        puts(result);//output the string
		puts(result);
        free(result);
    }
    return 0;
}