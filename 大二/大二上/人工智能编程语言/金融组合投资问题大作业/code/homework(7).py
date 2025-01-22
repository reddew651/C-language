import pandas as pd
import random
import numpy as np
import matplotlib.pyplot as plt

##############################################
#  1) 数据读取
##############################################
fileName = 'Top96_A_Lite'
try:
    dataset = pd.read_csv(fileName, encoding='utf-8')
except FileNotFoundError:
    print(f"无法找到文件: {fileName}")
    raise

print("\n[调试] 数据列名:", dataset.columns.tolist())
print("[调试] 前5行数据:")
print(dataset.head())
lowestCost = dataset['成本价'].min()
highestCost = dataset['成本价'].max()
print(f"[调试] 成本价范围: min={lowestCost:.2f}, max={highestCost:.2f}")

##############################################
#  2) 前三问 (编码、交叉、变异)
##############################################
# 选取成本价最高的前10只
top10_stocks = dataset.nlargest(10, '成本价')
top10_indices = top10_stocks.index.tolist()
initialCode = [1 if i in top10_indices else 0 for i in range(len(dataset))]

def crossover(codeA, codeB):
    crossPos = random.randint(1, len(codeA) - 1)
    newA = codeA[:crossPos] + codeB[crossPos:]
    newB = codeB[:crossPos] + codeA[crossPos:]
    return newA, newB

def mutation(code, mutationProb=0.01):
    mutated = code.copy()
    for i in range(len(mutated)):
        if random.random() < mutationProb:
            mutated[i] = 1 - mutated[i]
    return mutated

# 成本价最高前 30
top30_stocks = dataset.nlargest(30, '成本价')
top30_indices = top30_stocks.index.tolist()

# 年初至今涨跌幅最低 30
bottom30_stocks = dataset.nsmallest(30, '年初至今涨跌幅')
bottom30_indices = bottom30_stocks.index.tolist()

encodeA = [1 if i in top30_indices else 0 for i in range(len(dataset))]
encodeB = [1 if i in bottom30_indices else 0 for i in range(len(dataset))]

newA, newB = crossover(encodeA, encodeB)
mutatedA = mutation(newA)

print("\n=== 前三问: 主要输出 ===")
print("最高成本价前10的编码:", initialCode)
print("encodeA (Top 30 by cost):", encodeA)
print("encodeB (Lowest 30 by涨跌幅):", encodeB)
print("newA after Crossover:", newA)
print("mutatedA after Mutation:", mutatedA)

##############################################
#  3) 第四问：GA + 本地修复(LowCost≤700)
##############################################
BudgetThreshold = 700
nStocks = len(dataset)

costVec = dataset['成本价'].values
latestVec = dataset['最新价'].values

# ====== 适应度函数(若超700则-1e6) ======
def fitness_evaluation(ind):
    total_cost = np.sum(costVec * ind)
    if total_cost > BudgetThreshold:
        return -1e6
    return np.sum((latestVec - costVec) * ind)

# ====== 本地修复函数: 保证个体总成本 ≤ 700 ======
def repair_individual(ind):
    """
    若组合总成本>700, 则随机关闭(置0) 某些基因直到 总成本<=700
    """
    total_cost = np.sum(costVec * ind)
    while total_cost > BudgetThreshold:
        one_positions = [i for i,b in enumerate(ind) if b==1]
        if not one_positions:
            # 已没法关了(有可能单只股票本身就>700?), 只能break
            break
        # 随机关掉一个持股
        close_idx = random.choice(one_positions)
        ind[close_idx] = 0
        total_cost = np.sum(costVec * ind)
    return ind

# ====== 初始化: 随机生成后立刻修复 ======
def initialize_group(pop_size):
    population = []
    for _ in range(pop_size):
        individual = [random.randint(0,1) for __ in range(nStocks)]
        individual = repair_individual(individual)
        population.append(individual)
    return population

# ====== 改进交叉: 生成后修复 ======
def crossover_repaired(parent1, parent2):
    crossPos = random.randint(1, len(parent1)-1)
    c1 = parent1[:crossPos] + parent2[crossPos:]
    c2 = parent2[:crossPos] + parent1[crossPos:]
    c1 = repair_individual(c1)
    c2 = repair_individual(c2)
    return c1, c2

# ====== 改进变异: 变异后修复 ======
def mutation_repaired(code, pm=0.01):
    mutated = code.copy()
    for i in range(len(mutated)):
        if random.random() < pm:
            mutated[i] = 1 - mutated[i]
    mutated = repair_individual(mutated)
    return mutated

def population_selection(pop, fit_list, pop_size):
    idx_sorted = np.argsort(fit_list)[::-1]
    best_idx = idx_sorted[:pop_size]
    return [pop[i] for i in best_idx]

def run_ga(
    generations=100,
    pop_size=10,
    next_size=15,
    pc=0.6,
    pm=0.01
):
    population = initialize_group(pop_size)
    best_log, avg_log = [], []

    for g in range(generations):
        offspring = []
        while len(population)+len(offspring) < next_size:
            if random.random() < pc:
                p1_idx, p2_idx = random.sample(range(len(population)),2)
                child1, child2 = crossover_repaired(population[p1_idx], population[p2_idx])
                offspring.append(child1)
                offspring.append(child2)
            else:
                # 不交叉就复制一个(也可修复一次以防万一)
                idx = random.randint(0, len(population)-1)
                clone = population[idx][:]
                # clone = repair_individual(clone) # 可选
                offspring.append(clone)

        population.extend(offspring)

        # 变异(改用 mutation_repaired)
        for i in range(len(population)):
            population[i] = mutation_repaired(population[i], pm)

        # 适应度
        fits = [fitness_evaluation(ind) for ind in population]

        # 选择
        population = population_selection(population, fits, pop_size)

        # 记录
        new_fits = [fitness_evaluation(ind) for ind in population]
        best_fit = max(new_fits)
        avg_fit = np.mean(new_fits)
        best_log.append(best_fit)
        avg_log.append(avg_fit)

        print(f"迭代 {g+1}/{generations}, 最优={best_fit:.2f}, 平均={avg_fit:.2f}")

    return best_log, avg_log, population


if __name__ == '__main__':
    param_list = [
        (100, 0.1, 0.01, 10, 15),
        (200, 0.3, 0.01, 10, 15),
        (200, 0.15, 0.01, 10, 15),
        (200, 0.1, 0.02, 10, 15),
        (200, 0.2, 0.02, 20, 30),
        (200, 0.2, 0.02, 6, 8),
    ]

    best_param_set = None
    best_fitness = -np.inf  # 初始设为非常低的值用于比较
    best_solution = None
    best_final_cost = None
    best_final_profit = None
    best_chosen_idx = None

    # 对每组参数配置运行 GA
    for (GEN, PC, PM, POP_SIZE, NEXT_SIZE) in param_list:
        print("\n==============================================")
        print(f"运行 GA, Gen={GEN}, pc={PC}, pm={PM}, pop_size={POP_SIZE}, next_size={NEXT_SIZE}")

        bestLog, avgLog, finalPop = run_ga(
            generations=GEN,
            pop_size=POP_SIZE,
            next_size=NEXT_SIZE,
            pc=PC,
            pm=PM
        )

        # 绘制收敛曲线
        plt.figure(figsize=(6, 4))
        plt.plot(range(1, GEN + 1), bestLog, 'r-', label='最佳适应度')
        plt.plot(range(1, GEN + 1), avgLog, 'b--', label='平均适应度')
        plt.xlabel('代数')
        plt.ylabel('适应度')
        plt.title(f'GA (Gen={GEN}, pc={PC}, pm={PM}, pop_size={POP_SIZE}, next_size={NEXT_SIZE})')
        plt.legend()
        plt.tight_layout()
        plt.show()

        # 评估最终种群并选择最佳解
        finalFits = [fitness_evaluation(ind) for ind in finalPop]
        idxBest = np.argmax(finalFits)
        bestOne = finalPop[idxBest]
        finalCost = np.sum(costVec * bestOne)
        finalProfit = np.sum((latestVec - costVec) * bestOne)

        # 对比并存储最优解
        if finalProfit > best_fitness:
            best_fitness = finalProfit
            best_param_set = (GEN, PC, PM, POP_SIZE, NEXT_SIZE)
            best_solution = bestOne
            best_final_cost = finalCost
            best_final_profit = finalProfit
            best_chosen_idx = np.where(np.array(bestOne) == 1)[0]

        # 输出当前配置的最佳解
        print("=== 当前配置的最佳解 ===")
        print(f"总成本 = {finalCost:.2f}, 收益 = {finalProfit:.2f}, 选中股票数 = {sum(bestOne)}")
        print("选中的股票索引:", best_chosen_idx)

    # 所有配置运行完后，输出最佳参数配置
    print("\n=== 最优参数配置 ===")
    print(f"最优参数: Gen={best_param_set[0]}, pc={best_param_set[1]}, pm={best_param_set[2]}, "
          f"pop_size={best_param_set[3]}, next_size={best_param_set[4]}")
    print(f"最优解的总成本 = {best_final_cost:.2f}, 最优解的收益 = {best_final_profit:.2f}")
    print(f"最优解选中的股票: {best_chosen_idx}")