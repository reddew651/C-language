def fibonacci_recursion(n):
   fib=[1,1]
   while len(fib)<n:
       fib.append(fib[-1]+fib[-2])
   return fib
fr=fibonacci_recursion(50)
print(fr)

def fibonacci(n):
   fib=[]
   a,b=1,1
   for i in range(n):
       fib.append(a)
       a,b=b,a+b
   return fib
z=fibonacci(100)
print(z)