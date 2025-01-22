function myGA()
    clc; clear; close all;

    %% ======= 读取 CSV，保留原始中文表头 =======
    fileName = 'Top96_A_Lite';  % 请改成你的真实 CSV 文件名(含后缀)
    if ~isfile(fileName)
        error('无法找到文件: %s', fileName);
    end

    % 关键参数: 'VariableNamingRule','preserve' 
    % 让 Matlab 不自动改列名, 直接使用表头的原字符串
    dataTbl = readtable(fileName, ...
        'Encoding','UTF-8', ...
        'VariableNamingRule','preserve');

    % 调试查看列名 & 前几行数据
    disp('[调试] 表格列名:');
    disp(dataTbl.Properties.VariableNames);
    disp('[调试] 前5行数据:');
    disp(dataTbl(1:5,:));

    % 若没有“成本价”列，则通过“最新价” & “年初至今涨跌幅”来计算
    varNames = dataTbl.Properties.VariableNames;
    % 这里假设表头正好是 {'代码','名称','最新价','年初至今涨跌幅','成本价'} 之类
    if ~ismember('成本价', varNames)
        % 成本价 = 最新价 / (1 + 年初至今涨跌幅/100)
        dataTbl.('成本价') = dataTbl.('最新价') ./ ...
            (1 + dataTbl.('年初至今涨跌幅')./100);
    end

    % 查看成本价区间
    minCost = min(dataTbl.('成本价'));
    maxCost = max(dataTbl.('成本价'));
    fprintf('[调试] 最低成本价=%.2f, 最高成本价=%.2f\n', minCost, maxCost);

    %% ======== 前三问：编解码，交叉，变异 ========
    % (1) 找出成本价最高的前10只
    [~, sortIdxDesc] = sort(dataTbl.('成本价'), 'descend');
    top10Idx = sortIdxDesc(1:10);
    initialEncoding = zeros(height(dataTbl),1);
    initialEncoding(top10Idx) = 1;

    % 单点交叉函数
    function [c1, c2] = crossover(encA, encB)
        crossPos = randi([1, length(encA)-1]);
        c1 = [encA(1:crossPos); encB(crossPos+1:end)];
        c2 = [encB(1:crossPos); encA(crossPos+1:end)];
    end

    % 变异函数
    function mutated = mutation(enc, pm)
        mutated = enc;
        for i = 1:length(enc)
            if rand < pm
                mutated(i) = 1 - mutated(i);
            end
        end
    end

    % (2) 成本价最高前30只
    top30Idx = sortIdxDesc(1:30);
    encode1 = zeros(height(dataTbl),1);
    encode1(top30Idx) = 1;

    % (3) 年初至今涨跌幅最低30只
    [~, sortIdxAsc] = sort(dataTbl.('年初至今涨跌幅'),'ascend');
    bottom30Idx = sortIdxAsc(1:30);
    encode2 = zeros(height(dataTbl),1);
    encode2(bottom30Idx) = 1;

    % 交叉 + 变异演示
    [newEnc1, newEnc2] = crossover(encode1, encode2);
    mutatedEnc1 = mutation(newEnc1, 0.01);

    % 输出前三问结果
    disp('=== 前三问: 编码,交叉,变异结果 ===');
    disp(['最高成本价前10只编码: ', num2str(initialEncoding')]);
    disp(['encode1(最高成本价前30只): ', num2str(encode1')]);
    disp(['encode2(涨跌幅最低30只): ', num2str(encode2')]);
    disp(['newEnc1 after crossover: ', num2str(newEnc1')]);
    disp(['mutatedEnc1 after mutation: ', num2str(mutatedEnc1')]);


    %% ======== 第四问：简易遗传算法 ========
    Budget = 7000;   % 最大资金
    nStocks = height(dataTbl);

    costArr = dataTbl.('成本价');
    latestArr = dataTbl.('最新价');

    % 适应度(若超预算则-1e6, 否则计算 (最新价-成本价) 之和)
    function val = fitnessFunc(indv)
        totalCost = sum(costArr .* indv);
        if totalCost > Budget
            val = -1e6;
        else
            val = sum((latestArr - costArr).*indv);
        end
    end

    % 初始化种群
    function pop = initPopulation(popSize)
        pop = randi([0,1], popSize, nStocks);
    end

    % 选择操作: 保留前 popSize
    function newPop = selection(oldPop, fits, pSize)
        [~, idxSort] = sort(fits,'descend');
        bestIdx = idxSort(1:pSize);
        newPop = oldPop(bestIdx,:);
    end

    % GA 主流程
    function [bestLog, avgLog, finalPop] = runGA(gens, pSize, nextSize, pc, pm)
        population = initPopulation(pSize);
        bestLog = zeros(gens,1);
        avgLog = zeros(gens,1);

        for g = 1:gens
            % 交叉 生成后代
            offspring = [];
            while size(population,1)+size(offspring,1)<nextSize
                if rand<pc
                    pp = randperm(size(population,1),2);
                    [child1, child2] = crossover(population(pp(1),:)', population(pp(2),:)');
                    offspring = [offspring; child1'; child2'];
                else
                    idx = randi(size(population,1));
                    offspring = [offspring; population(idx,:)];
                end
            end
            population = [population; offspring];

            % 变异
            for iPop = 1:size(population,1)
                population(iPop,:) = mutation(population(iPop,:)', pm)';
            end

            % 计算适应度
            fits = zeros(size(population,1),1);
            for iPop = 1:size(population,1)
                fits(iPop) = fitnessFunc(population(iPop,:)');
            end

            % 选择
            population = selection(population, fits, pSize);

            % 记录
            newFits = zeros(size(population,1),1);
            for iPop = 1:size(population,1)
                newFits(iPop) = fitnessFunc(population(iPop,:)');
            end
            bestLog(g) = max(newFits);
            avgLog(g)  = mean(newFits);

            fprintf('第 %d/%d 代: 最优=%.2f, 平均=%.2f\n', g, gens, bestLog(g), avgLog(g));
        end
        finalPop = population;
    end

    % GA 参数
    GEN = 100;
    POP_SIZE = 10;
    NEXT_SIZE = 15;
    Pc = 0.6;
    Pm = 0.01;

    disp('=== 第四问: 运行简易GA ===');
    [bestList, avgList, finalSet] = runGA(GEN, POP_SIZE, NEXT_SIZE, Pc, Pm);

    % 绘图
    figure('Name','GA收敛曲线(保留原表头中文)');
    plot(1:GEN, bestList,'r-','LineWidth',1.5); hold on;
    plot(1:GEN, avgList,'b--','LineWidth',1.2);
    xlabel('迭代次数');
    ylabel('适应度(收益)');
    title(sprintf('Gen=%d, Pc=%.2f, Pm=%.2f', GEN, Pc, Pm));
    legend({'最优','平均'},'Location','best');
    grid on;

    % 最优解
    finalFits = zeros(size(finalSet,1),1);
    for i = 1:size(finalSet,1)
        finalFits(i) = fitnessFunc(finalSet(i,:)');
    end
    [~, bestIdx] = max(finalFits);
    bestSol = finalSet(bestIdx,:);
    finalCost = sum(costArr .* bestSol');
    finalProfit = sum((latestArr - costArr).*bestSol');

    fprintf('\n=== 最终结果 ===\n');
    fprintf('总成本 = %.2f (预算=%.2f)\n', finalCost, Budget);
    fprintf('收益 = %.2f\n', finalProfit);
    fprintf('选中股票数 = %d\n', sum(bestSol));
    chosenIdx = find(bestSol==1);
    disp('选中股票索引:');
    disp(chosenIdx');
    disp('完成。');
end
