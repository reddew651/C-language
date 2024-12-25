'''第二题（25分）
​请编写一个Python程序，该程序接受一个字符串‘Hello world！’作为输入，并执行以下操作：
1. 统计字符串中每个字符出现的次数，并将结果存储在一个字典中，其中键是字符，值是字符的出现次数，打印出字典中每个字符及其出现次数，。
2. 创建一个包含字符串中唯一字符的集合，并打印这个集合。
3. 将字符串中所有字母变为大写。
4. 利用字符串的切片操作提取子串，提取字符串前5个字符、后5个字符、偶数索引位置的字符，并将他们分别输出。
5. 将字符串中的空格替换为","，然后以","作为间隔将字符串分成两段保存到列表中，再分别输出.'''

str=input()
dic={}
for char in str:
    if char in dic:  #如果字典中已经有这个字符，就将这个字符的值加1
        dic[char]+=1
    else:  #如果字典中没有这个字符，就将这个字符的值设为1
        dic[char]=1
print(dic)

only=set()
for char in str:
    if dic[char]==1:
        only.add(char)  #将只出现一次的字符添加到集合中
print(only)

upper=str.upper()  #将字符串中的字母全部变为大写
print(upper)

print(str[:5])  #输出前5个字符
print(str[-5:])  #输出后5个字符
print(str[::2])  #输出偶数索引位置的字符

strnew=str.replace(' ',',') #将字符串中的空格替换为","
lis=strnew.split(',')  #以","作为间隔将字符串分成两段保存到列表中
print(lis)

