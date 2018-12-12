#!/bin/python3

import math
import os
import random
import re
import sys
import bisect

#
# Complete the 'computePrices' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts following parameters:
#  1. INTEGER_ARRAY s
#  2. INTEGER_ARRAY p
#  3. INTEGER_ARRAY q
#

def computePrices(s, p, q):
    # Write your code here
    res = []
    
    sorted_s = sorted(s)
    sorted_p = [x for _,x in sorted(zip(s,p))]
    
    for buying in q:
        index = bisect.bisect_right(sorted_s, buying)
        res.append(sorted_p[index-1])
    
    return res

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    s = list(map(int, input().rstrip().split()))

    p = list(map(int, input().rstrip().split()))

    k = int(input().strip())

    q = []

    for _ in range(k):
        q_item = int(input().strip())
        q.append(q_item)

    res = computePrices(s, p, q)

    fptr.write('\n'.join(map(str, res)))
    fptr.write('\n')

    fptr.close()
