import numpy as np
import pandas as pd
import matplotlib as mpl

data = pd.read_csv('2.csv') # 读取数据
mathScore = data['Math']
mathMean = np.mean(mathScore)
mathMidian = np.median(mathScore)
mathMin = np.min(mathScore)
mathMax = np.max(mathScore)
print(f"平均值:{mathMean} 中位数:{mathMidian} 最小值:{mathMin} 最大值:{mathMax}")

import matplotlib.pyplot as plt

# 分数段统计 (每 10 分一段)
bins = range(60, 110, 10)   # 60-70, 70-80, 80-90, 90-100
reading_score_counts = pd.cut(data['Reading'], bins=bins).value_counts().sort_index()   #cut函数，将数据进行分段，value_counts()统计每个分段的个数，sort_index()按索引排序

# 绘制柱状图
plt.figure(figsize=(10, 6))
reading_score_counts.plot(kind='bar', color='skyblue', edgecolor='black')   #kind='bar'绘制柱状图，color='skyblue'设置颜色，edgecolor='black'设置边框颜色
plt.title('Reading Score Distribution')
plt.xlabel('Reading Score Range')
plt.ylabel('Number of Students')
plt.show()

# 计算每个学生的平均成绩
data['Average Score'] = data[['Math', 'Reading', 'Writing']].mean(axis=1)   #data[['Math', 'Reading', 'Writing']]选取三科成绩列，mean(axis=1)计算每行的平均值
data_sorted = data.sort_values(by='Average Score', ascending=False)  #sort_values(by='Average Score', ascending=False)按平均成绩降序排列

# 绘制水平条形图
plt.figure(figsize=(10, 8))
plt.barh(data_sorted.index, data_sorted['Average Score'], color='orange')       #barh绘制水平条形图，data_sorted.index作为Y轴，data_sorted['Average Score']作为X轴，color='orange'设置颜色
plt.xlabel('Average Score')
plt.ylabel('Student Index')
plt.title('Student Ranking by Average Score')
plt.gca().invert_yaxis()  # 反转Y轴以显示高分在顶部
plt.show()

# 绘制箱线图
plt.figure(figsize=(8, 6))
data.boxplot(column='Math', by='Gender', grid=False)    #by是根据性别分组，grid=False去掉网格线,column='Math'表示绘制数学成绩的箱线图
plt.title('Math Score Distribution by Gender')
plt.suptitle('')  # 去掉默认的子标题
plt.xlabel('Gender')
plt.ylabel('Math Score')
plt.show()

# 根据是否参加考前准备课程，计算各科目平均成绩
course_group = data.groupby('Test Preparation Course')[['Math', 'Reading', 'Writing']].mean()

# 绘制堆积柱状图
course_group.plot(kind='bar', stacked=True, color=['lightcoral', 'skyblue', 'lightgreen'], edgecolor='black', figsize=(10, 6))  #stacked=True绘制堆积柱状图，color设置颜色，edgecolor='black'设置边框颜色
plt.title('Average Scores by Test Preparation Course')  
plt.xlabel('Test Preparation Course')
plt.ylabel('Average Score')
plt.show()