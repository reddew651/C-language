# akshare是一个用于获取股票市场的包，可进行简单的排序等操作
import akshare as ak
import pandas as pd
'''
    该代码用于获取并处理股票信息，供同学们参考
    处理后的股票数据文件已给出，名为“Top96_A_Lite”，格式为CSV文件
    由于股票市场变动频繁，为保证统一，请同学们统一提供的“Top96_A_Lite”文件。
'''

# 获得A股股票信息
stock_zh_a_spot_df = ak.stock_zh_a_spot_em()
# 按照总市值排序，获得Top100排行榜
stock_zh_a_spot_df_sorted = stock_zh_a_spot_df.sort_values(by="总市值", ascending=False)
top_100_market_value = stock_zh_a_spot_df_sorted.head(100)
# 查询市值Top 100的公司
top_100_market_value.to_csv("Top100_A")

file_path = 'Top100_A'
data = pd.read_csv(file_path, usecols=['代码', '名称', '最新价', '年初至今涨跌幅'])
# 删除满足特定查询条件的行
# 删除满足某条件的所有行
# 直接在原DataFrame上操作
data.dropna(subset=['最新价'], axis=0, inplace=True)
data['成本价'] = data['最新价'] / (1 + data['年初至今涨跌幅'] / 100)
data.to_csv('Top'+ str(len(data)) + '_A_Lite', index=False)

import pandas as pd

# 假设已加载数据，文件名为 'Top96_A_Lite.csv'
data = pd.read_csv('Top96_A_Lite.csv')
print(data)

# 按成本价降序排序，并获取前10只股票
top_10_stocks = data.sort_values(by='成本价', ascending=False).head(10)

# 构造编码数组：长度为96（所有股票数），对前10只股票设置为1，其余为0
n_stocks = len(data)
encoding = [0] * n_stocks

# 找到前10只股票的索引，并将对应位置的编码设置为1
for index in top_10_stocks.index:
    encoding[index] = 1

print("编码结果:", encoding)

print([0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
      == [0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])


############################################################


import numpy as np

# 生成示例数据（问题2中的成本价格和收益率数据）
cost_prices = data['成本价'].values
returns = data['年初至今涨跌幅'].values      # 收益率（百分比）

# 选择成本价格最高的前30种股票
highest_cost_indices = np.argsort(-cost_prices)[:30]
x1 = np.zeros(len(cost_prices), dtype=int)
x1[highest_cost_indices] = 1  # 设置编码

# 选择收益率最低的前30种股票
lowest_return_indices = np.argsort(returns)[:30]
x2 = np.zeros(len(returns), dtype=int)
x2[lowest_return_indices] = 1  # 设置编码

# 随机选择交叉点并进行交叉操作
crossover_point = np.random.randint(1, len(cost_prices))  # 交叉点（不包括开头和结尾）
x1_new = np.concatenate([x1[:crossover_point], x2[crossover_point:]])
x2_new = np.concatenate([x2[:crossover_point], x1[crossover_point:]])

# 输出结果
print("原始 x1:", x1)
print("原始 x2:", x2)
print("交叉点位置:", crossover_point)
print("新 x1:", x1_new)
print("新 x2:", x2_new)

import numpy as np

# 确定变异位数（10%）
mutation_rate = 0.1

# 定义变异操作
def mutate(individual, mutation_rate):
    for i in range(len(individual)):
        if np.random.rand() < mutation_rate:
            individual[i] = 1 - individual[i]  # 0变为1，1变为0
    return individual

# 对新生成的解进行变异操作
x1_mutated = mutate(x1_new.copy(), mutation_rate)
x2_mutated = mutate(x2_new.copy(), mutation_rate)

# 输出结果
print("变异前 x1_new:", x1_new)
print("变异后 x1_mutated:", x1_mutated)
print("变异前 x2_new:", x2_new)
print("变异后 x2_mutated:", x2_mutated)

# Gen 最大迭代次数  pc 交叉概率  pm 变异概率  p0 初始种群  p 种群

############################################################


import numpy as np
import pandas as pd
import matplotlib
matplotlib.use('TkAgg')  # 或 'Agg'
import matplotlib.pyplot as plt

# 读取数据
data = pd.read_csv('Top96_A_Lite.csv')
cost_prices = data['成本价'].values  # 提取成本价
returns = data['年初至今涨跌幅'].values  # 提取收益率
max_investment = 700  # 最大投资金额

# 初始化种群
def initialize_population(method, P0, n_stocks):
    if method == "random":
        return np.random.randint(0, 2, size=(P0, n_stocks))
    elif method == "roulette":
        probabilities = np.random.rand(n_stocks)
        probabilities /= probabilities.sum()
        population = np.zeros((P0, n_stocks), dtype=int)
        for i in range(P0):
            population[i] = np.random.rand(n_stocks) < probabilities
        return population
    else:
        raise ValueError("Unsupported initialization method!")

# 适应度函数：收益 + 约束修复
def fitness(population, cost_prices, returns, max_investment):
    fitness_values = []
    for individual in population:
        total_cost = np.sum(individual * cost_prices)
        while total_cost > max_investment:  # 超出限制，修复
            one_indices = np.where(individual == 1)[0]
            if len(one_indices) == 0:
                break
            remove_idx = np.random.choice(one_indices)
            individual[remove_idx] = 0
            total_cost = np.sum(individual * cost_prices)
        total_return = np.sum(individual * returns)
        fitness_values.append(total_return)
    return np.array(fitness_values)

# 选择操作
def roulette_wheel_selection(population, fitness_values):
    probabilities = fitness_values - fitness_values.min() + 1e-6  # 避免负值
    probabilities /= probabilities.sum()
    indices = np.random.choice(range(len(population)), size=len(population), p=probabilities)
    return population[indices]

# 交叉操作
def crossover(population, pc):
    new_population = []
    for i in range(0, len(population), 2):
        if i + 1 < len(population) and np.random.rand() < pc:
            crossover_point = np.random.randint(1, population.shape[1])
            new_population.append(np.concatenate((population[i][:crossover_point], population[i+1][crossover_point:])))
            new_population.append(np.concatenate((population[i+1][:crossover_point], population[i][crossover_point:])))
        else:
            new_population.append(population[i])
            if i + 1 < len(population):
                new_population.append(population[i+1])
    return np.array(new_population)

# 变异操作
def mutation(population, pm):
    for individual in population:
        for i in range(len(individual)):
            if np.random.rand() < pm:
                individual[i] = 1 - individual[i]
    return population

# 遗传算法主函数
def genetic_algorithm(Gen, pc, pm, P0, P, initialization_method="random"):
    n_stocks = len(cost_prices)
    population = initialize_population(initialization_method, P0, n_stocks)
    best_solutions = []
    average_fitness = []

    for generation in range(Gen):
        # 计算适应度
        fitness_values = fitness(population, cost_prices, returns, max_investment)
        best_solutions.append(fitness_values.max())
        average_fitness.append(fitness_values.mean())

        # 精英保留：保留 P 个最优个体
        elite_indices = fitness_values.argsort()[-P:]
        elites = population[elite_indices]

        # 选择、交叉和变异操作
        selected_population = roulette_wheel_selection(population, fitness_values)
        crossed_population = crossover(selected_population, pc)
        mutated_population = mutation(crossed_population, pm)

        # 将精英加入下一代
        population = np.vstack((elites, mutated_population[:P0 - P]))

    return best_solutions, average_fitness

# 参数集合
params = [
    (100, 0.1, 0.01, 10, 15),
    (200, 0.3, 0.01, 10, 15),
    (200, 0.15, 0.01, 10, 15),
    (200, 0.1, 0.02, 10, 15),
    (200, 0.2, 0.02, 20, 30),
    (200, 0.2, 0.02, 6, 8),
]
# 运行遗传算法
results = {}
for i, (Gen, pc, pm, P0, P) in enumerate(params):
    best, avg = genetic_algorithm(Gen, pc, pm, P0, P, initialization_method="random")
    results[f"ParamSet {i+1}"] = (best, avg)

# 绘制结果
plt.figure(figsize=(12, 8))
for i, (key, (best, avg)) in enumerate(results.items()):
    plt.subplot(2, 3, i+1)
    plt.plot(best, label='Best Fitness')
    plt.plot(avg, label='Average Fitness')
    plt.title(key)
    plt.xlabel('Generation')
    plt.ylabel('Fitness')
    plt.legend()
plt.tight_layout()
plt.show()
