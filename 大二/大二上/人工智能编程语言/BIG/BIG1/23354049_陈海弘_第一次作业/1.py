#请编写一个Python程序，该程序要能接受用户输入的一个任意长度的整数列表（先输入列表长度，再输入对应的数值），并执行以下操作：
#1. 将列表中的所有奇数元素提取出来，存放在一个新的元组中，并将结果打印出来。
#2. 计算列表中所有偶数的平均值，并将结果打印出来。


lens=int(input())
lis=[]
for i in range(lens):   #使用循环输入列表
    lis.append(int(input()))

odd = []    #创建一个空列表
even=0      #记录偶数的和
evens=0     #记录偶数的个数

for x in lis:
    if x%2==1:
        odd.append(x)   #将奇数添加到odd列表中
    else:
        even+=x     #将偶数相加
        evens+=1    #记录偶数的个数
odd=tuple(odd)  #将odd列表转换为元组

print(odd)
print(even/evens)


