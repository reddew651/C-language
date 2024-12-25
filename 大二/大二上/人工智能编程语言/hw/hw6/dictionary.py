def stu_info(name,id,**any):
   stu_info = {
       'Name':name,
       'Student_ID':id
   }
   stu_info.update(any)
   return stu_info
students = []
students.append(stu_info('Reddew','23354049',gender = 'male'))
students.append(stu_info('Redddew','233354049',gender = 'male',hobbit = 'dancing'))
students.append(stu_info('Redddew','233354049',gender = 'male',hobbit = 'eating'))
students.append(stu_info('Redddew','233354049',gender = 'male',hobbit = 'playing'))
students.append(stu_info('Redddew','233354049',gender = 'male',hobbit = 'sleeping'))
students.append(stu_info('Redddew','233354049',gender = 'male',hobbit = 'gaming'))
students.append(stu_info('Redddew','233354049',gender = 'male',hobbit = 'coding',height = '180'))
students.append(stu_info('Redddew','233354049',gender = 'male',hobbit = 'dancing',money = '$9999999999999999999'))
students.append(stu_info('Redddew','233354049',gender = 'female',hobbit = 'dancing'))
students.append(stu_info('Redddew','233354049',gender = 'male',hobbit = 'traveling'))
for i,student in enumerate(students,1):
   print(f"Student {i}:{student}")