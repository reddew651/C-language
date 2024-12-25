def print_string(a):
    lens = len(a)
    tem=0
    while (a[(tem+8)%8]!='\0' and tem<=lens):
        if (tem+8<lens):
            print(a[tem:tem+8:1],end=' ')
        tem+=8
        if tem>lens:
            print(a[tem-8:tem:1] +'0'*(tem-lens))


def prime_factors(n):
    factors = []
    # 处理 2 的因子
    while n % 2 == 0:
        factors.append(2)
        print(2,end=' ')
        n //= 2 #//表示整除
    # 处理其他质数因子
    for i in range(3, int(n**0.5) + 1, 2): #从3开始，步长为2，到n的平方根,步长为2是因为偶数不是质数
        while n % i == 0:
            factors.append(i)
            print(i,end=' ')
            n //= i
    # 如果剩余的数大于 2，则它本身就是一个质数因子
    if n > 2:
        factors.append(n)
        print(n,end=' ')
    print('\n')

n=int(input())
prime_factors(n)

def bubble_sort(a):
    i=0
    lens = 10
    for i in range(lens):
        j=i
        for j in range(0,lens-i-1):
            if a[j]>a[j+1]:
                temp=a[j]
                a[j]=a[j+1]
                a[j+1]=temp


def factorial(n):
    if n==0:
        return 1
    else:
        return factorial(n-1)*n

