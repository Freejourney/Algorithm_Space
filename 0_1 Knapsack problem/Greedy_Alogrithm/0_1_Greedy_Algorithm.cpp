#include <iostream>
#include <iomanip>
using namespace std;

/*
	Zero_One_Knapsack class describes the elements of objects and includes weight、value and unitValue(the value of every unit weight)
*/
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
	int compareTo(Zero_One_Knapsack knapsack);	// to compare with another objects and return 1 or 0. 1 means the another object is less than this and vice versa
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
	int getCurrentMaxWeight(); 
private:
	Zero_One_Knapsack * bags;
	int totalWeight;
	int bestValue; 
	int currentMaxWeight;
	int size;
};

Greedy_Algorithm::Greedy_Algorithm(Zero_One_Knapsack * bags, int totalWeight, int size)
{
	this->bags = bags;
	this->totalWeight = totalWeight;
	this->size = size;
	bestValue = 0;
	currentMaxWeight = 0;
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
	
	currentMaxWeight = totalWeight - tempWeight;
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
		// adjust the width to make them in the same column and print them
		cout << "UV:"  << setw(10) << left << bags[i].getUnitValue() << " Weight:" << setw(5) << left << bags[i].getWeight() << " Value:" << setw(5) << left << bags[i].getValue() << endl;
	}
}

int Greedy_Algorithm::getBestValue() 
{
	return bestValue;
}

int Greedy_Algorithm::getCurrentMaxWeight()
{
	return currentMaxWeight;
}

int main()
{
	// Create Object Array
	// Original Datas
//	Zero_One_Knapsack bags[8] = {	Zero_One_Knapsack(2, 13),
//               						Zero_One_Knapsack(1, 10), 
//									Zero_One_Knapsack(3, 24), 
//									Zero_One_Knapsack(2, 15),
//                					Zero_One_Knapsack(4, 28), 
//									Zero_One_Knapsack(5, 33), 
//									Zero_One_Knapsack(3, 20),
//                					Zero_One_Knapsack(1, 8)		};

	//Test 1
//	Zero_One_Knapsack bags[] = {
//									Zero_One_Knapsack(95, 55),
//									Zero_One_Knapsack(4, 10),
//									Zero_One_Knapsack(60, 47),
//									Zero_One_Knapsack(32, 5),
//									Zero_One_Knapsack(23, 4),
//									Zero_One_Knapsack(72, 50),
//									Zero_One_Knapsack(80, 8),
//									Zero_One_Knapsack(62, 61),
//									Zero_One_Knapsack(65, 85),
//									Zero_One_Knapsack(46, 87)
//																};
//                
//    int totalWeight = 269;
//    
//    Greedy_Algorithm ga(bags, totalWeight,10);

	//Test 2
	Zero_One_Knapsack bags[] = {
									Zero_One_Knapsack(92, 44),
									Zero_One_Knapsack( 4, 46),
									Zero_One_Knapsack(43, 90),
									Zero_One_Knapsack(83, 72),
									Zero_One_Knapsack(84, 91),
									
									Zero_One_Knapsack(68, 40),
									Zero_One_Knapsack(92, 75),
									Zero_One_Knapsack(82, 35),
									Zero_One_Knapsack( 6, 8),
									Zero_One_Knapsack(44, 54),
									
									Zero_One_Knapsack(32, 78),
									Zero_One_Knapsack(18, 40),
									Zero_One_Knapsack(56, 77),
									Zero_One_Knapsack(83, 15),
									Zero_One_Knapsack(25, 61),
									
									Zero_One_Knapsack(96, 17),
									Zero_One_Knapsack(70, 75),
									Zero_One_Knapsack(48, 29),
									Zero_One_Knapsack(14, 75),
									Zero_One_Knapsack(58, 63),
															};
	
	int totalWeight = 878;
	
	Greedy_Algorithm ga(bags, totalWeight,20);
															
    ga.solve();
    
    cout << "BestValue:" << ga.getBestValue() << endl;
    cout << "CurrentMaxWeight:" << ga.getCurrentMaxWeight() << endl;
}
