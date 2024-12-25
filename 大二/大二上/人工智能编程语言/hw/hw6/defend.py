def find(n):
   po = n**2
   tem = n
   lens = 0
   while (tem!=0):
       tem=int(tem/10)
       lens+=1
   while lens !=0 and  po%10== n%10:
       lens-=1
       po=int (po/10)
       n=int (n/10)
   if (lens==0):
       return True

num=0
n = int(input())
for i in range(1,n+1):
   if find(i):
       num+=1
       print(i,end=' ')
print()
print (num)