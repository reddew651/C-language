clc;
clear;

% 读取股票数据
opts = detectImportOptions('Top96_A_Lite.csv');  % 检测导入选项
opts.VariableNamingRule = 'preserve';            % 保留原始列标题
data = readtable('Top96_A_Lite.csv', opts);      % 读取数据

% 提取股票信息
stock_num = size(data, 1);                       % 获取股票数量
stock_codes = data.("代码");                     % 股票代码
stock_names = data.("名称");                     % 股票名称
latest_prices = data.("最新价");                  % 最新价
profit_rates = data.("年初至今涨跌幅");          % 收益率
cost_prices = data.("成本价");                   % 成本价





% 题目2：选择成本价格最高的前 10 支股票的编码
[~, cost_sorted_idx] = sort(cost_prices, 'descend'); % 按成本价降序排序
top10_stock_codes = zeros(stock_num, 1);              % 初始化编码向量
top10_stock_codes(cost_sorted_idx(1:10)) = 1;         % 将前10支股票标记为1
fprintf('选择成本价最高的10支股票的编码为：\n');
disp(top10_stock_codes);

% 题目3：交叉操作
[~, profit_sorted_idx] = sort(profit_rates);       % 按收益率升序排序
x1 = zeros(stock_num, 1);
x1(cost_sorted_idx(1:30)) = 1;                      % 前30支成本价最高的股票
x2 = zeros(stock_num, 1);
x2(profit_sorted_idx(1:30)) = 1;                    % 前30支收益率最低的股票

fprintf('交叉之前的x1和x2编码：\n');
disp('x1:');
disp(x1);
disp('x2:');
disp(x2);

% 定义交叉函数
function [new_x1, new_x2, crossover_point] = crossover(x1, x2)
    % 确保两个个体的长度相同
    if length(x1) ~= length(x2)
        error('两个个体的长度不相同');
    end
    
    % 强制将x1和x2转换为行向量
    x1 = reshape(x1, 1, []);  % 转换为行向量
    x2 = reshape(x2, 1, []);  % 转换为行向量

    % 输出调试信息，查看x1和x2的长度
    disp(['x1长度: ', num2str(length(x1))]);
    disp(['x2长度: ', num2str(length(x2))]);
    
    % 随机选择一个交叉点
    crossover_point = randi([1, length(x1)-1]);  % 随机选择一个交叉点，保证不越界
    
    % 进行交叉操作
    new_x1 = [x1(1:crossover_point), x2(crossover_point+1:end)];
    new_x2 = [x2(1:crossover_point), x1(crossover_point+1:end)];
    
    % 输出交叉后的结果
    disp('new_x1:');
    disp(new_x1);
    disp('new_x2:');
    disp(new_x2);
end

% 调用交叉函数进行交叉操作
[new_x1, new_x2, crossover_point] = crossover(x1, x2);
fprintf('交叉操作发生的位置: %d\n', crossover_point);
fprintf('交叉后的x1和x2编码：\n');
disp('new_x1:');
disp(new_x1);
disp('new_x2:');
disp(new_x2);

% 定义变异函数
function mutated_individual = mutate0(individual, mutation_rate)
    % 遍历每个基因
    for i = 1:length(individual)
        % 根据变异率决定是否变异
        if rand() < mutation_rate
            individual(i) = 1 - individual(i);  % 反转基因（0变1，1变0）
        end
    end
    % 返回变异后的个体a
    mutated_individual = individual;
end






% 题目4：变异操作
x1_example = [1, 0, 1, 0, 1, 0, 0, 0, 1];   % 示例个体
mutation_rate = 0.1;                          % 变异率
x1_mutated = mutate0(x1_example, mutation_rate); % 变异操作

fprintf('原始个体编码：\n');
disp(x1_example);
fprintf('变异后的个体编码：\n');
disp(x1_mutated);
