//识别最长字符串
//写一个函数，对于一行字符（含空格），能够找到字符串中最长的单词。
//主函数中，输入字符串，调用自定义函数并输出最长的单词。

//this type is the classical type of the longest word in a sentence, you should know the basic idea of this type 2023-11-27
#include<stdio.h>
#include<string.h>
int main()
{
    char str[100]; //declare the string
    fgets(str,sizeof(str),stdin); //use fgets function to get the string, the sizeof(str) is the length of the string, stdin is the input stream    
    //scanf("%s",str); 
    //here is a problem, if use the scanf function, it ends when meets the space" ", so you should use the gets fuction ,because the gets function won't ends when meet the space, it ends when meet the enter"\n"
    void Longest(char str[]); 
    Longest(str);
    return 0;//
}
 
void Longest(char str[])
{
    int currLen=0,maxLen=0,currStart=0,MaxStart=0; //currlen is the current length of the word,maxlen is the max length of the word,curresstart is the start of the current word,maxstart is the start of the max length word
    int i=0,j=0;
    for(i=0;str[i];i++)
    {
        if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')) //if the character is a letter,use '||' to connect the two conditions
        {
            if(currLen==0)//current length is 0,which means it is the start of a new word
                currStart=i;//the start of the current word
            currLen++;
        }
        if(currLen>maxLen)//if the current length is longer than the max length,update the max length and the start of the max length
        {
            maxLen = currLen;
            MaxStart = currStart;
        }
        if(str[i]==' ')//if meet the space,reset the current length
        {
            currLen = 0;
        }
    }
    for(j=MaxStart;j<MaxStart+maxLen;j++)
        printf("%c",str[j]);
}
