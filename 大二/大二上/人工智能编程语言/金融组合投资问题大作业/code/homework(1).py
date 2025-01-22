import pandas as pd
import random
import numpy as np
import matplotlib.pyplot as plt

##############################
#          数据读取
##############################
fileName = 'Top96_A_Lite'  # 若实际为“Top96_A_Lite.csv”等，请修改
try:
    dataset = pd.read_csv(fileName, encoding='utf-8')
except FileNotFoundError:
    print(f"无法找到文件: {fileName}")
    raise

# 显示列名与样例
print("\n[调试] 数据列名:", dataset.columns.tolist())
print("[调试] 前 5 行数据:")
print(dataset.head())

# 如果没有“成本价”列，则通过“最新价”和“年初至今涨跌幅”来计算
if '成本价' not in dataset.columns:
    dataset['成本价'] = dataset['最新价'] / (1 + dataset['年初至今涨跌幅'] / 100)

# 调试用：观察成本价的最小/最大值
lowestCost = dataset['成本价'].min()
highestCost = dataset['成本价'].max()
print(f"[调试] 最低成本价={lowestCost:.2f}, 最高成本价={highestCost:.2f}")

##############################
#          前三问
##############################
# 1) 选取成本价最高的前 10 支股票
top10_stocks = dataset.nlargest(10, '成本价')
top10_indices = top10_stocks.index.tolist()
initialCode = [1 if i in top10_indices else 0 for i in range(len(dataset))]


def crossover(codeA, codeB):
    """单点交叉：随机选取一点，将 A/B 基因片段互换"""
    crossPos = random.randint(1, len(codeA) - 1)
    newA = codeA[:crossPos] + codeB[crossPos:]
    newB = codeB[:crossPos] + codeA[crossPos:]
    return newA, newB


def mutation(code, mutationProb=0.01):
    """基因翻转：以一定概率将位 0->1 或 1->0"""
    mutated = code.copy()
    for i in range(len(mutated)):
        if random.random() < mutationProb:
            mutated[i] = 1 - mutated[i]
    return mutated


# 2) 成本价最高前 30
top30_stocks = dataset.nlargest(30, '成本价')
top30_indices = top30_stocks.index.tolist()

# 3) 年初至今涨跌幅最低 30
bottom30_stocks = dataset.nsmallest(30, '年初至今涨跌幅')
bottom30_indices = bottom30_stocks.index.tolist()

encodeA = [1 if i in top30_indices else 0 for i in range(len(dataset))]
encodeB = [1 if i in bottom30_indices else 0 for i in range(len(dataset))]

# 演示一次交叉 + 变异
newA, newB = crossover(encodeA, encodeB)
mutatedA = mutation(newA)

print("\n=== 前三问: 主要输出 ===")
print("最高成本价前10的编码:", initialCode)
print("encodeA (Top 30 by cost):", encodeA)
print("encodeB (Lowest 30 by涨跌幅):", encodeB)
print("newA after Crossover:", newA)
print("mutatedA after Mutation:", mutatedA)

##############################
#          第四问
##############################
BudgetThreshold = 7000  # 可用资金上限
stockCount = len(dataset)

# 提取向量(数组)
costVec = dataset['成本价'].values
currentPriceVec = dataset['最新价'].values


def fitness_evaluation(individual):
    """
    若投资组合的总成本 > BudgetThreshold，则返回 -1e6 惩罚；
    否则收益 = (最新价 - 成本价) 的累加和。
    """
    totalExpanse = np.sum(costVec * individual)
    if totalExpanse > BudgetThreshold:
        return -1e6
    netProfit = np.sum((currentPriceVec - costVec) * individual)
    return netProfit


def initialize_group(groupSize):
    """随机生成 groupSize 个 0/1 的个体(股票选择编码)"""
    group = []
    for _ in range(groupSize):
        single = [random.randint(0, 1) for __ in range(stockCount)]
        group.append(single)
    return group


def population_selection(group, fitList, groupSize):
    """对个体按适应度从高到低排序，只保留 groupSize 个"""
    sortedIdx = np.argsort(fitList)[::-1]
    bestPart = sortedIdx[:groupSize]
    return [group[i] for i in bestPart]


def genetic_optimization(
        iteration=10,
        initSize=10,
        newSize=15,
        crossProb=0.6,
        mutateProb=0.01
):
    """
    简易版 GA：
    1. 初始化群体
    2. 交叉 + 变异 -> 种群扩大到 newSize
    3. 计算适应度 -> 选择, 保留 initSize
    4. 重复迭代 iteration 代
    """
    population = initialize_group(initSize)
    bestTrace, avgTrace = [], []

    for gen in range(iteration):
        # 交叉操作
        offspring = []
        while len(population) + len(offspring) < newSize:
            if random.random() < crossProb:
                idx1, idx2 = random.sample(range(len(population)), 2)
                child1, child2 = crossover(population[idx1], population[idx2])
                offspring.append(child1)
                offspring.append(child2)
            else:
                cpyIdx = random.randint(0, len(population) - 1)
                offspring.append(population[cpyIdx][:])  # 复制某个体

        # 合并父代+子代
        population.extend(offspring)

        # 变异
        for i in range(len(population)):
            population[i] = mutation(population[i], mutateProb)

        # 计算并选择
        fitnessScores = [fitness_evaluation(ind) for ind in population]
        population = population_selection(population, fitnessScores, initSize)

        # 记录本代最优 & 均值
        newScores = [fitness_evaluation(ind) for ind in population]
        bestNow = max(newScores)
        meanNow = np.mean(newScores)
        bestTrace.append(bestNow)
        avgTrace.append(meanNow)

        print(f"迭代 {gen + 1}/{iteration}, 当前最优={bestNow:.2f}, 平均={meanNow:.2f}")

    return bestTrace, avgTrace, population


if __name__ == '__main__':
    # 参数
    GEN = 100
    POP_SIZE = 10
    NEXT_SIZE = 15
    CROSS_RATE = 0.6
    MUTATE_RATE = 0.01

    print("\n=== 第四问: 进化算法示例运行 ===")
    bestLog, avgLog, finalPop = genetic_optimization(
        iteration=GEN,
        initSize=POP_SIZE,
        newSize=NEXT_SIZE,
        crossProb=CROSS_RATE,
        mutateProb=MUTATE_RATE
    )

    # 画出收敛曲线
    plt.figure(figsize=(6, 4))
    plt.plot(range(1, GEN + 1), bestLog, 'r-', label='Best Fit')
    plt.plot(range(1, GEN + 1), avgLog, 'b--', label='Average Fit')
    plt.xlabel('Generation')
    plt.ylabel('Fitness')
    plt.title(f'GA Evolution (Gen={GEN}, Pc={CROSS_RATE}, Pm={MUTATE_RATE})')
    plt.legend()
    plt.tight_layout()
    plt.show()

    # 最优个体
    finalScores = [fitness_evaluation(ind) for ind in finalPop]
    idxBest = np.argmax(finalScores)
    bestOne = finalPop[idxBest]

    finalCost = np.sum(costVec * bestOne)
    finalProfit = np.sum((currentPriceVec - costVec) * bestOne)
    print("\n=== 最优解输出 ===")
    print(f"总成本 = {finalCost:.2f} (预算={BudgetThreshold})")
    print(f"收益 = {finalProfit:.2f}")
    print("选择股票数 =", sum(bestOne))
    chosenStockIds = np.where(np.array(bestOne) == 1)[0]
    print("被选股票索引 =", chosenStockIds)
    print("运行结束。")
