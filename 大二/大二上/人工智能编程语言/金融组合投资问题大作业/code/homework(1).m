% 读取股票数据文件，并检查文件是否成功打开
file_location = '中国A股数据/Top96_A_Lite';
if exist(file_location, 'file') ~= 2
    error(['无法找到文件: "' file_location '"']);
end
stock_data = readtable(file_location);

% 打印数据表的变量名，检查列名是否正确
disp('数据表的列名:');
disp(stock_data.Properties.VariableNames);

% 由于MATLAB无法正确解析列名，手动设置正确的列名
new_column_names = {'股票代码', '股票名称', '当前价格', '年初涨跌幅', '成本价格'};
% 更新列名
stock_data.Properties.VariableNames = new_column_names;
% 打印更新后的列名
disp('更新后的数据表列名:');
disp(stock_data.Properties.VariableNames);

% 根据成本价格排序，提取成本价最高的10只股票
[~, sorted_by_cost] = sort(stock_data.("成本价格"), 'descend');
top_10_cost_indices = sorted_by_cost(1:10);
% 初始化编码
stock_encoding = zeros(1, height(stock_data)); 
% 将成本价最高的10只股票的编码设为1
stock_encoding(top_10_cost_indices) = 1;

% 交叉操作函数
function [offspring1, offspring2] = crossover_function(parent1, parent2)
    % 随机选择交叉点
    crossover_point = randi([2, length(parent1)-1]);
    % 交叉生成新的编码
    offspring1 = [parent1(1:crossover_point-1), parent2(crossover_point:end)];
    offspring2 = [parent2(1:crossover_point-1), parent1(crossover_point:end)];
end

% 变异操作函数
function mutated_chromosome = mutation_function(chromosome, mutation_probability)
    % 复制染色体
    mutated_chromosome = chromosome;
    % 进行变异
    for j = 1:length(mutated_chromosome)
        if rand < mutation_probability
            mutated_chromosome(j) = 1 - mutated_chromosome(j);
        end
    end
end

% 获取成本价最高的前30只股票
top_30_cost_indices = sorted_by_cost(1:30);
chromosome1 = zeros(1, height(stock_data));
chromosome1(top_30_cost_indices) = 1;

% 根据年初涨跌幅排序，提取收益率最低的30只股票
[~, sorted_by_return] = sort(stock_data.("年初涨跌幅"), 'ascend');
bottom_30_return_indices = sorted_by_return(1:30);
chromosome2 = zeros(1, height(stock_data));
chromosome2(bottom_30_return_indices) = 1;

% 执行交叉操作
[offspring1, offspring2] = crossover_function(chromosome1, chromosome2);

% 对其中一个后代染色体进行变异
mutated_offspring1 = mutation_function(offspring1, 0.01);

% 打印编码结果
disp('初始编码（成本价前10）:');
disp(stock_encoding);
disp('编码1（成本价前30）:');
disp(chromosome1);
disp('编码2（收益率最低前30）:');
disp(chromosome2);
disp('交叉后编码1:');
disp(offspring1);
disp('变异后的编码1:');
disp(mutated_offspring1);
