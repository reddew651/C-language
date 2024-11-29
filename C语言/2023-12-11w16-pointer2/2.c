//编写函数intsearch(char *cpSource, char ch)，该函数在一个字符串中找到可能的最长的子字符串，该字符串是由同一字符组成的。
//从主函数中输入"aabbcccddddeeeeeffffff"和'e'，调用函数得到结果。
#include <stdio.h>
#include <string.h>

int intsearch(char *cpSource, char ch) 
{
    int currentCount = 0;//define the current count
    int maxCount = 0;
    int len = strlen(cpSource);
    char *p = cpSource;
    for (int i = 0; i < len; i++) 
    {
        if (*(p+i) == ch) //check if the current char is the same as the target char
        {
            currentCount++;
            if (currentCount > maxCount) 
            {
                maxCount = currentCount;//update the maxcout
            }
        } 
        else 
        {
            currentCount = 0;
        }
    }

    return maxCount;
}

int main() 
{
    char str[100] = {0};//set the string to 0
    fgets(str, sizeof(str), stdin);//get the string
    char ch = {0};
    scanf("%c", &ch);
    int result = intsearch(str, ch);
    printf("%d\n",result);
    for (int i = 0; i < result; i++) 
    {
        printf("%c", ch);
    }
    return 0;
}