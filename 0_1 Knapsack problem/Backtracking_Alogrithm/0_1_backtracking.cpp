#include <iostream>
using namespace std;

int n = 10;//��Ʒ����
double c = 269;//��������
double w[10] = {95,4,60,32,23,72,80,62,65,46};//������Ʒ�ļ�ֵ
double v[10] = {55,10,47,5,4,50,8,61,85,87};//������Ʒ������
int cw;   //��ǰ��������
int cv;   //��ǰ������ֵ
int bestv;//������������
int X[10] = {0};  //��¼�����е��ƶ�·��,Ϊ1��ʱ���ʾѡ��������ݣ�Ϊ0�ı�ʾ��ѡ���������

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
	cout << "��weights��values��value_per_weight��������:�������ڼ�֦������ģ�������ֵ��������Ϊ�ɿ��Ͻ磩" << endl;
	for(int i = 0; i < n; i++)
		cout << (double)v[i]/w[i] << " " ; 
	cout << endl;
}

void display()
{
	cout << "�ﵽ���������" << cv << "  ";
	for (int i = 0; i < 10; i++)
    {
    	cout << X[i] << " ";
	}
	cout << endl;
}

//�����Ͻ纯��
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
    cout << "��ǰ��������ֵ������������������£�" << endl << b << endl;
    return b;
}

void getBest(int i)
{
    if(i>=n)//�ݹ�������ж�����
    {
        if(cv>bestv)
        {
        	bestv=cv;
        	display();
		}
        return;
    }
    if(cw+w[i]<=c)//����ýڵ���Һ��ӣ�ֵΪ1�ĺ��ӣ�
    {
        X[i]=1;
        cw+=w[i];
        cv+=v[i];
        getBest(i+1);
        cw-=w[i];//�˴�����
        cv-=v[i];
    }
	if(bound(i+1)>bestv)
	{
		X[i]=0;//����ýڵ���Һ��ӣ�ֵΪ0�ĺ��ӣ�
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

