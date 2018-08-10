a = [95 4 60 32 23 72 80 62 65 46]; % weight
c = [55 10 47 5 4 50 8 61 85 87];   % value
b = 269;    % maxWeight

Dim = 10;   % ����ά��
xSize = 20; % ��Ⱥ��
MaxIt = 30; % ����������
c1 = 0.7;
c2 = 0.7;   %��������
w = 0.8;    %��������

A = repmat(a,xSize,1);  % ��weight��չ��xSize*size(a)�ľ���20*10
C = repmat(c,xSize,1);  % ��value��չ��xSize*size(c)�ľ���20*10
x = round(rand(xSize,Dim)); % ���ѡȡһ��xSize*size(a)�ľ�����Ϊ��ʼλ�ã�20*10
v = rand(xSize,Dim);    % �����ȡ20*10�����λ�����ӳ��ٶ�
xbest = zeros(xSize,Dim);   % ���������λ��
fxbest = zeros(xSize,1);    % ���������λ������Ӧ����Ӧ��
gbest = zeros(1,Dim);   % ����Ⱥ���λ��
fgbest = 0;     % ����Ⱥ�����Ӧ��

iter = 0;
while iter < MaxIt
    iter = iter + 1;
    fx = sum((C.*x)');  % ��ǰ����Ⱥ��Ӧ�ȣ�������Ʒ��ֵ����Ӧ�Ⱥ���
    sx = sum((A.*x)');  % ��ǰ����Ⱥ���������������ƺ���
    for i = 1:xSize
        if sx(i) > 269
            fx(i) = 0;  % �����������������ֵ����
        end
    end
    for i = 1:xSize
        if fxbest(i) < fx(i)    % ��������Ӧ�ȳ����������Ӧ��ʱ��������Ӧ�ȼ�λ��
            fxbest(i)=fx(i);    % ���µ����������Ӧ��
            xbest(i,:)=x(i,:);  % ���µ��������λ��
        end
    end
    if fgbest<max(fxbest)   % ȫ�������Ӧ��С�ڵ����Ӽ������Ӧ��ʱ������ȫ�������Ӧ�ȼ�λ��
        [fgbest,g]=max(fxbest); % ����ȫ�������Ӧ��
        gbest=xbest(g,:)    % ����ȫ�����λ��
    end
    for i=1:xSize
        if x(i,:)==gbest
            x(i,:)=round(rand(1,Dim));  % ����ֲ����Ż�����������Ⱥ������λ��Ϊȫ�����ŵ����ӣ�������������λ��
        end
    end
    R1=rand(xSize,Dim);
    R2=rand(xSize,Dim);
    v = v*w+c1*R1.*(xbest-x)+c2*R2.*(repmat(gbest,xSize,1)-x);  % �ٶȸ���
    x = x + v;  % λ�ø���
    for i = 1:xSize     % λ��ȡ��
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