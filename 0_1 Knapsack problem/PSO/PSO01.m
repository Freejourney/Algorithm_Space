a = [95 4 60 32 23 72 80 62 65 46]; % weight
c = [55 10 47 5 4 50 8 61 85 87];   % value
b = 269;    % maxWeight

Dim = 10;   % 粒子维数
xSize = 20; % 种群数
MaxIt = 30; % 最大迭代次数
c1 = 0.7;
c2 = 0.7;   %加速因子
w = 0.8;    %惯性因子

A = repmat(a,xSize,1);  % 将weight扩展成xSize*size(a)的矩阵，20*10
C = repmat(c,xSize,1);  % 将value扩展成xSize*size(c)的矩阵，20*10
x = round(rand(xSize,Dim)); % 随机选取一个xSize*size(a)的矩阵作为初始位置，20*10
v = rand(xSize,Dim);    % 随机获取20*10矩阵各位置粒子初速度
xbest = zeros(xSize,Dim);   % 单粒子最佳位置
fxbest = zeros(xSize,1);    % 单粒子最佳位置所对应的适应度
gbest = zeros(1,Dim);   % 粒子群最佳位置
fgbest = 0;     % 粒子群最佳适应度

iter = 0;
while iter < MaxIt
    iter = iter + 1;
    fx = sum((C.*x)');  % 当前粒子群适应度，背包物品价值，适应度函数
    sx = sum((A.*x)');  % 当前粒子群背包总重量，限制函数
    for i = 1:xSize
        if sx(i) > 269
            fx(i) = 0;  % 背包总重量超额，将价值置零
        end
    end
    for i = 1:xSize
        if fxbest(i) < fx(i)    % 单粒子适应度超过其最佳适应度时，更新适应度及位置
            fxbest(i)=fx(i);    % 更新单粒子最佳适应度
            xbest(i,:)=x(i,:);  % 更新单粒子最佳位置
        end
    end
    if fgbest<max(fxbest)   % 全局最佳适应度小于单粒子集最佳适应度时，更新全局最佳适应度及位置
        [fgbest,g]=max(fxbest); % 更新全局最佳适应度
        gbest=xbest(g,:)    % 更新全局最佳位置
    end
    for i=1:xSize
        if x(i,:)==gbest
            x(i,:)=round(rand(1,Dim));  % 避免局部最优化，重置粒子群中粒子位置为全局最优的粒子，继续搜索其它位置
        end
    end
    R1=rand(xSize,Dim);
    R2=rand(xSize,Dim);
    v = v*w+c1*R1.*(xbest-x)+c2*R2.*(repmat(gbest,xSize,1)-x);  % 速度更新
    x = x + v;  % 位置更新
    for i = 1:xSize     % 位置取整
        for j = 1:Dim
            if x(i,j)<0.5
                x(i,j)=0;
            else
                x(i,j)=1;
            end
        end
    end
end

fgbest
sgbest = sum((a.*gbest)')
gbest