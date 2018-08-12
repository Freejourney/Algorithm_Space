#include <iostream>
using namespace std;

int n = 10;//物品数量
double c = 269;//背包容量
double w[10] = {95,4,60,32,23,72,80,62,65,46};//各个物品的价值
double v[10] = {55,10,47,5,4,50,8,61,85,87};//各个物品的重量
int cw;   //当前背包重量
int cv;   //当前背包价值
int bestv;//迄今最大的收益
int X[10] = {0};  //记录在树中的移动路径,为1的时候表示选择该组数据，为0的表示不选择该组数据

void sortwv()
{
	double vpw[10] = {0};
	for(int i = 0; i < n; i++)
	{
		vpw[i] = v[i] / w[i];
	}
	for(int i = 0; i < n - 1; i++)
	{
		for(int j = 0; j < n-i-1; j++)
		{
			if(vpw[j] < vpw[j+1])
			{
				int tempv = v[j];
				int tempw = w[j];
				double tempvpw = vpw[j];
				v[j] = v[j+1];
				w[j] = w[j+1];
				vpw[j] = vpw[j+1];
				v[j+1] = tempv;
				w[j+1] = tempw;
				vpw[j+1] = tempvpw;
			}
		}
	}
	cout << "对weights和values按value_per_weight进行排序:（这样在剪枝过程中模拟的最大价值量才能作为可靠上界）" << endl;
	for(int i = 0; i < n; i++)
		cout << (double)v[i]/w[i] << " " ; 
	cout << endl;
}

void display()
{
	cout << "达到最大条件：" << cv << "  ";
	for (int i = 0; i < 10; i++)
    {
    	cout << X[i] << " ";
	}
	cout << endl;
}

//计算上界函数
double bound(int i)
{
    double leftw= c-cw;
    double b = cv;
    while(i<n&&w[i]<=leftw)
    {
        leftw-=w[i];
        b+=v[i];
        i++;
    }
    if(i<n)
        b+=v[i]/w[i]*leftw;
    cout << "当前理想最大价值量：（背包问题情况下）" << endl << b << endl;
    return b;
}

void getBest(int i)
{
    if(i>=n)//递归结束的判定条件
    {
        if(cv>bestv)
        {
        	bestv=cv;
        	display();
		}
        return;
    }
    if(cw+w[i]<=c)//进入该节点的右孩子（值为1的孩子）
    {
        X[i]=1;
        cw+=w[i];
        cv+=v[i];
        getBest(i+1);
        cw-=w[i];//此处回溯
        cv-=v[i];
    }
	if(bound(i+1)>bestv)
	{
		X[i]=0;//进入该节点的右孩子（值为0的孩子）
  		getBest(i+1);
	}

}

int main()
{
    sortwv();
    getBest(0);
    printf("%d",bestv);


    return 0;
}

