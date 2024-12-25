'''第三题（25分）
​请编写一个python程序，该程序接受学生成绩信息序列作为输入，输出成绩从高到低、从低到高、按某一门成绩的排列。相同成绩按先录入排列在前的规则处理。数据如下：(数据规则：学生姓名 高数成绩 英语成绩 大物成绩)
SanZhang 70 80 61
SiLi 86 77 81
WuWang 88 90 77
MingLi 60 77 81
MiWang 71 70 60
HaiLi 88 78 89
HeWang 70 90 80
LiWang 67 71 70
要求：利用字典容器，完成对于每个学生成绩数据的储存，并将所有学生储存于列表中；在此基础上，按照总分从高到低的学生名单，总分从低到高的学生名单，三门课成绩从高到低的学生名单。给出具体的排序结果、涉及的代码，以及简要介绍自己设计的排序算法原理'''

data = '''SanZhang 70 80 61
SiLi 86 77 81
WuWang 88 90 77
MingLi 60 77 81
MiWang 71 70 60
HaiLi 88 78 89
HeWang 70 90 80
LiWang 67 71 70'''

# Parse the input data
students = []
for line in data.split('\n'):   #循环遍历每一行
    name, math, english, physics = line.split() #将每一行的数据按空格分割，分别赋值给name, math, english, physics
    student = { #将每一行的数据存储到字典中
        'name': name,
        'math': int(math),
        'english': int(english),
        'physics': int(physics),
        'total': int(math) + int(english) + int(physics)
    }
    students.append(student)    #将每一行的数据存储到列表中

# 按照总分从高到低的学生名单
sorted_by_total_desc = sorted(students, key=lambda x: x['total'], reverse=True) #sorted()函数，key参数指定排序的依据，reverse参数指定排序的顺

# 按照总分从低到高的学生名单
sorted_by_total_asc = sorted(students, key=lambda x: x['total'])

# 按照三门课成绩从高到低的学生名单
sorted_by_math_desc = sorted(students, key=lambda x: x['math'], reverse=True)
sorted_by_english_desc = sorted(students, key=lambda x: x['english'], reverse=True)
sorted_by_physics_desc = sorted(students, key=lambda x: x['physics'], reverse=True)

print("按照总分从高到低的学生名单:")
for student in sorted_by_total_desc:
    print(student)

print("\n按照总分从低到高的学生名单:")
for student in sorted_by_total_asc:
    print(student)

print("\n按照数学成绩从高到低的学生名单:")
for student in sorted_by_math_desc:
    print(student)

print("\n按照英语成绩从高到低的学生名单:")
for student in sorted_by_english_desc:
    print(student)

print("\n按照物理成绩从高到低的学生名单:")
for student in sorted_by_physics_desc:
    print(student)
