import random
import operator
import time
import heapq

temps1 = time.time()

#genetic algorithm function
def fitness (test_sack, weights, values, max_weight):
	value = 0
	weight = 0
	i = 0
	while (i < len(test_sack)):
		if (test_sack[i] == 1):
			weight += weights[i]
			value += values[i]
		i += 1

	if (weight > max_weight):
		return 0
	else:
		return value

	""" 随机生成个体并计算其适应度值 """
def generateASack (item_quantity, weights, values, max_weight):
	i = 0
	sack = []
	result = []
	while i < item_quantity:
		sack.append(round(random.random()))
		i +=1
	result.append(-fitness(sack, weights, values, max_weight))
	result.append(sack)
	return result

	""" 生成第一代种群并堆排序 """
def generateFirstPopulation(size_population, item_quantity, weights, values, max_weight):
	population = []
	i = 0
	while i < size_population:
		population.append(generateASack(item_quantity, weights, values, max_weight))
		i+=1
	heapq.heapify(population)
	#print(population)
	return population

#probably now not needed
def computePerfPopulation(population, password):
	populationPerf = {}
	for individual in population:
		populationPerf[individual] = fitness(password, individual)
	return sorted(populationPerf.items(), key = operator.itemgetter(1), reverse=True)

	""" 保留精英并随机选取lucky个进化 """
def selectFromPopulation(old_population, best_sample, lucky_few):
	best = []
	for i in range(best_sample):
		best.append(old_population[i])
	#best = heapq.nlargest(best_sample, old_population, key=None)
	lucky = []
	for i in range(lucky_few):
		lucky.append(random.choice(old_population))
	#random.shuffle(nextGeneration)
	return best + lucky

	""" 利用保留下来的个体进行交叉遗传 """
def createChild(individual1, individual2, weights, values, max_weight):
	sack = []
	child = []
	for i in range(len(individual1[1])):
		if (int(100 * random.random()) < 50):
			sack.append(individual1[1][i])
		else:
			sack.append(individual2[1][i])
	child.append(-fitness(sack, weights, values, max_weight))
	child.append(sack)
	return child

	""" 生成子代 """
def createChildren(breeders, weights, values, max_weight):
	nextPopulation = []
	size = len(breeders)
	for i in range(size):
		nextPopulation.append(createChild(breeders[i], breeders[random.randint(0, size-1)], weights, values, max_weight))
	return nextPopulation

def mutateWord(sack, weights, values, max_weight):
	index_modification = random.randint(0, len(sack[1])-1)
	if (sack[1][index_modification] == 0):
		sack[1][index_modification] = 1
	else:
		sack[1][index_modification] = 0
	sack[0] = (-fitness(sack[1], weights, values, max_weight))
	return sack

	""" 对交叉遗传后的子代进行变异操作 """
def mutatePopulation(population, chance_of_mutation, weights, values, max_weight):
	for i in range(len(population)):
		if random.random() * 100 < chance_of_mutation:
			population[i] = mutateWord(population[i], weights, values, max_weight)
	heapq.heapify(population)
	return population

	""" 生成下一代种群，包括精英保留、交叉、变异三个部分 """
def nextGeneration (firstGeneration, best_sample, lucky_few, chance_of_mutation, weights, values, max_weight):
	print(firstGeneration, '\n')
	nextBreeders = selectFromPopulation(firstGeneration, best_sample, lucky_few)
	nextPopulation = createChildren(nextBreeders, weights, values, max_weight)
	nextGeneration = mutatePopulation(nextPopulation, chance_of_mutation, weights, values, max_weight)
	return nextGeneration

	""" Genetic Algorithm """
def multipleGeneration(number_of_generation, size_population,
				   best_sample, lucky_few, chance_of_mutation,
				   item_quantity, weights, values, max_weight):
	historic = []
	historic.append(generateFirstPopulation(size_population, item_quantity, weights, values, max_weight))
	for i in range (number_of_generation):
		historic.append(nextGeneration(historic[i], best_sample, lucky_few, chance_of_mutation,
										weights, values, max_weight))
	return historic

#print result:
def printSimpleResult(historic, number_of_generation): #bestSolution in historic. Caution not the last
	result = getListBestIndividualFromHistorique(historic)
	print ("value:", -result[0][0], "\nsack: ", result[0][1])

#analysis tools
def getBestIndividualFromPopulation (population):
	return population[0]

def getListBestIndividualFromHistorique (historic):
	bestIndividuals = []
	for population in historic:
		bestIndividuals.append(getBestIndividualFromPopulation(population))
	heapq.heapify(bestIndividuals)
	return bestIndividuals

def main():

	#variables
	#argv = sys.argv
	size_population = 40
	best_sample = 20
	lucky_few = 20
	number_of_generation = 500
	chance_of_mutation = 5

	# weights = [10,20,30,40,50,5,15,25,35]
	# values = [60,100,120,140,160,50,100,150,80]

	weights = [95,4,60,32,23,72,80,62,65,46]
	values = [55,10,47,5,4,50,8,61,85,87]

	item_quantity = len(weights)
	max_weight = 269

	#program
	if ((best_sample + lucky_few) != size_population):
		print ("population size not stable")
	else:
		historic = multipleGeneration(number_of_generation, size_population,
									best_sample, lucky_few, chance_of_mutation,
									item_quantity, weights, values, max_weight)

		printSimpleResult(historic, number_of_generation)


	print (time.time() - temps1)

if __name__ == "__main__":
	main()
