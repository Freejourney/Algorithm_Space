#include <iostream>
#include <iomanip>
using namespace std;

class Zero_One_Knapsack
{
public:
	Zero_One_Knapsack(int weight, int value);
	~Zero_One_Knapsack();
	int getWeight();
	void setWeight(int weight);
	int getValue();
	void setValue(int value);
	double getUnitValue();
	void setUnitValue(double unitValue);
	int compareTo(Zero_One_Knapsack knapsack);
private:
	int weight;
	int value;
	double unitValue;
}; 

Zero_One_Knapsack::Zero_One_Knapsack(int weight, int value)
{
	this->weight = weight;
	this->value = value;
	unitValue = (weight==0)?0:(double)value/weight;
}

Zero_One_Knapsack::~Zero_One_Knapsack()
{
	
}

int Zero_One_Knapsack::getWeight()
{
	return this->weight;
}

void Zero_One_Knapsack::setWeight(int weight)
{
	this->weight = weight;
}

int Zero_One_Knapsack::getValue()
{
	return this->value;
} 
 
void Zero_One_Knapsack::setValue(int value)
{
	this->value = value;
} 

double Zero_One_Knapsack::getUnitValue()
{
	return this->unitValue;
}

void Zero_One_Knapsack::setUnitValue(double unitValue)
{
	this->unitValue = unitValue;
}

int Zero_One_Knapsack::compareTo(Zero_One_Knapsack knapsack)
{
	double value = knapsack.unitValue;
	if (unitValue > value)
		return 1;
	else
		return 0;
}

class Greedy_Algorithm
{
public:
	Greedy_Algorithm(Zero_One_Knapsack * bags, int totalWeight, int size);
	void solve();
	void uvsort(Zero_One_Knapsack * bags, int size);
	int getBestValue();
private:
	Zero_One_Knapsack * bags;
	int totalWeight;
	int bestValue; 
	int size;
};

Greedy_Algorithm::Greedy_Algorithm(Zero_One_Knapsack * bags, int totalWeight, int size)
{
	this->bags = bags;
	this->totalWeight = totalWeight;
	this->size = size;
	bestValue = 0;
	uvsort(bags, size);
}

void Greedy_Algorithm::solve()
{
	int tempWeight = totalWeight;
	
	for (int i = 0; i < size; i++)
	{
		if (tempWeight - bags[i].getWeight() < 0)
			continue;
			
		tempWeight -= bags[i].getWeight();
		bestValue += bags[i].getValue();
	}
};

void Greedy_Algorithm::uvsort(Zero_One_Knapsack * bags, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size-1-i; j++)
		{
			if (!bags[j].compareTo(bags[j+1]))
			{
				int tempweight = bags[j].getWeight();
				int tempvalue = bags[j].getValue();
				double tempunitvalue = bags[j].getUnitValue();
				
				bags[j].setWeight(bags[j+1].getWeight());
				bags[j].setValue(bags[j+1].getValue());
				bags[j].setUnitValue(bags[j+1].getUnitValue());
				
				bags[j+1].setWeight(tempweight);
				bags[j+1].setValue(tempvalue);
				bags[j+1].setUnitValue(tempunitvalue);	
			}
		}
	}
	
	for (int i = 0; i < size; i++)
	{
		cout << "UV:"  << setw(10) << left << bags[i].getUnitValue() << " Weight:" << setw(10) << left << bags[i].getWeight() << " Value:" << setw(10) << left << bags[i].getValue() << endl;
	}
}

int Greedy_Algorithm::getBestValue() 
{
	return bestValue;
}

int main()
{
	Zero_One_Knapsack bags[8] = {	Zero_One_Knapsack(2, 13),
               						Zero_One_Knapsack(1, 10), 
									Zero_One_Knapsack(3, 24), 
									Zero_One_Knapsack(2, 15),
                					Zero_One_Knapsack(4, 28), 
									Zero_One_Knapsack(5, 33), 
									Zero_One_Knapsack(3, 20),
                					Zero_One_Knapsack(1, 8)		};
                
    int totalWeight = 12;
    
    Greedy_Algorithm ga(bags, totalWeight,8);
    ga.solve();
    
    cout << "BestValue:" << ga.getBestValue() << endl;
}
