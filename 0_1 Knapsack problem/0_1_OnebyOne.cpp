#include <iostream>
using namespace std;

int value[] = {23, 41, 24, 12, 42};
int weight[] = {5, 8, 4, 10, 9};
int maxweight = 30;

int GetValue(int * bags, int length)
{
	int sumvalue = 0;
	int sumweight = 0;
	for(int i = 0; i < length; i++)
	{
		sumvalue += value[i] * bags[i];
		sumweight += weight[i] * bags[i];
	}
	
	if (sumweight > maxweight)
		return 0;
	else
		return sumvalue;
}

int main()
{	
	int bags[5] = {0};
	int sumvalue = 0;
	int savebags[5] = {0};
	for(int i = 0; i <= 1; i++)
	{
		for(int j = 0; j <= 1; j++)
		{
			for(int k = 0; k <= 1; k++)
			{
				for(int l = 0; l <= 1; l++)
				{
					for(int m = 0; m <= 1; m++)
					{
						bags[0] = i;
						bags[1] = j;
						bags[2] = k;
						bags[3] = l;
						bags[4] = m;
						int temp = GetValue(bags, 5);
						if (temp > sumvalue)
						{
							for(int i = 0; i < 5; i++)
							{
								savebags[i] = bags[i];
							}
							sumvalue = temp;
						}
							
					}
				}
			}
		}
	}
	
	
	cout << "最大价值：" << sumvalue << endl;
	cout << "[ " ;
	for(int i = 0; i < 5; i++)
	{
		cout << savebags[i] << " ";
	}
	cout << "]" << endl;
	return 0; 
} 
