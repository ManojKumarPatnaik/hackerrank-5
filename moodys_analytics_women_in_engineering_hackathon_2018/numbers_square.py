#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'numbersSquare' function below.
#
# The function accepts following parameters:
#  1. INTEGER n
#  2. INTEGER s
#

def numbersSquare(n, s):
    # Write your code here
    final_number = s + (n**2) - 1
    
    square =  [ [0 for j in range(n)] for i in range(n) ]
    
    for i in range(n-1, -1, -1):
        for j in range(0, i + 1):
            square[i][j] = str(final_number)
            final_number -= 1 
            
        j = i
        for k in range(i-1, -1, -1):
            square[k][j] = str(final_number)
            final_number -= 1
            
    for i in range(0, n):
        print(" ".join(square[i]))
            
if __name__ == '__main__':
    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    s = int(first_multiple_input[1])

    numbersSquare(n, s)
