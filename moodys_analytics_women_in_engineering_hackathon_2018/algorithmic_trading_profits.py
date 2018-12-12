#!/bin/python3

import math
import os
import random
import re
import sys
from itertools import product

#
# Complete the 'solve' function below.
#
# The function is expected to return an INTEGER.
# The function accepts 2D_INTEGER_ARRAY profits as parameter.
#

class ProfitSolver:
    
    def __init__(self, profits):
        self.profits = profits
        self.max_matrix = [[[-1 for k in range(4)] for j in range(4)] for i in range(len(profits))]
    
    def solve(self, profits_index, index_chosen1, index_chosen2):
        already_calculated = self.max_matrix[profits_index][index_chosen1][index_chosen2]
        if already_calculated != -1:
            return already_calculated
        
        # we are picking day 1 (special case)
        if profits_index == 0:
            # iterate over all possible choices for this day
            max_profit = 0
            for index_alg, profit_alg in enumerate(self.profits[profits_index]):

                # if this index is not equal to the one after
                if (index_alg != index_chosen1) and (index_alg != index_chosen2):

                    # calculate total profit for this choice
                    total_profit = profit_alg

                    # if it's bigger than any seen yet for this day, choose it
                    if total_profit > max_profit:
                        max_profit = total_profit

            self.max_matrix[profits_index][index_chosen1][index_chosen2] = max_profit
            return max_profit    

        # we are picking days 2+ (starting from the last day)
        else:
            # iterate over all possible choices for this day
            max_profit = 0
            for index_alg, profit_alg in enumerate(self.profits[profits_index]):

                # if this index is not equal to either of the two after
                if (index_alg != index_chosen1) and (index_alg != index_chosen2):

                    # calculate total profit based on picking this one this day
                    total_profit = profit_alg + self.solve(profits_index - 1, index_alg, index_chosen1)

                    # if it's bigger than any seen yet for this day, choose it
                    if total_profit > max_profit:
                        max_profit = total_profit

            self.max_matrix[profits_index][index_chosen1][index_chosen2] = max_profit
            return max_profit
        
def dumb_solve(profits):
    test_cases = list(product([0, 1, 2, 3], repeat=len(profits)))
    
    max_profit = 0
    for i in range(0, len(test_cases)):
        profit = 0
        for j in range(0, len(test_cases[i])):
            profit += profits[j][test_cases[i][j]]
            if (test_cases[i][0] == test_cases[i][1]):
                profit = -1
                break
                
            if j < len(test_cases[i]) - 2:
                if (test_cases[i][j] == test_cases[i][j+1]) or (test_cases[i][j] == test_cases[i][j+2]):
                    profit = -1
                    break
            
            if j == len(test_cases[i]) - 2:
                if test_cases[i][j] == test_cases[i][j+1]:
                    profit = -1
                    break
                
        if profit > max_profit:
            max_profit = profit
            
    return max_profit

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input().strip())

    for q_itr in range(q):
        w = int(input().strip())

        profits = []

        for _ in range(w):
            profits.append(list(map(int, input().rstrip().split())))
            
        profit_solver = ProfitSolver(profits)

        result = profit_solver.solve(w-1, -1, -2)
        #result = dumb_solve(profits)

        fptr.write(str(result) + '\n')

    fptr.close()
