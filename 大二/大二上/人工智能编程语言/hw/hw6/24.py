def calc(a, b, operator):
    if operator == '+':
        return a + b
    elif operator == '-':
        return a - b
    elif operator == '*':
        return a * b
    elif operator == '/':
        return a / b if b != 0 else None  

'''
lis = [0] * 4
for i in range(4):
    lis[i] = int(input())
'''
lis = list(map(int, input().split()))

for i in range(4):
    for j in range(4):
        for k in range(4):
            for l in range(4):
                if i != j and i != k and i != l and j != k and j != l and k != l:
                    numbers = [lis[i], lis[j], lis[k], lis[l]]
                    for operator1 in ['+', '-', '*', '/']:
                        for operator2 in ['+', '-', '*', '/']:
                            for operator3 in ['+', '-', '*', '/']:
                                result = calc(calc(calc(numbers[0], numbers[1], operator1), numbers[2], operator2), numbers[3], operator3)
                                if result == 24:
                                    print('true')
                                    print(f'(({numbers[0]} {operator1} {numbers[1]}) {operator2} {numbers[2]}) {operator3} {numbers[3]} = 24')
                                    exit(0)
print('false')