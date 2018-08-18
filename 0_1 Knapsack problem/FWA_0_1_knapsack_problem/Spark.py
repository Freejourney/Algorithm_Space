import random
import math


class Spark:
    """
    Single firework
    """
    EvaNum = 0

    def __init__(self, vardim, bound, weights, value):
        self.vardim = vardim
        self.bound = bound
        self.fitness = 0.
        self.si = 0.
        self.Ai = 0.
        self.Ri = 0.
        self.weights = weights
        self.value = value

    def initialize(self):
        """
        Initialization
        """
        len = self.vardim
        self.location = [round(random.uniform(self.bound[0], self.bound[1])) for _ in range(len)]
        print(self.location)

    def evaluate(self):
        """
        Get fitness
        """
        weight = 0
        for i in range(0, self.vardim):
            self.location[i] = round(self.location[i])
            if self.location[i] == 1:
                weight += self.weights[i]
        if weight > 269:
            self.fitness = 0
        else:
            self.fitness = self.Fitness()
            # print(self.fitness)
        Spark.EvaNum += 1

    def distance(self, other):
        dis = 0.
        for i in range(0, self.vardim):
            dis += (self.location[i] - other.location[i]) ** 2
        return math.sqrt(dis)

    def Fitness(self):
        fitness = 0
        for i in range(0, len(self.location)):
            if self.location[i] == 1:
                fitness += self.value[i]
        return fitness

