import math, random
from numpy import arange

def get_i():
    return math.e ** 1 - math.e ** 0

def monte_karlo_method(func, n):
    in_d, out_d = 0., 0.
    for i in arange(n):
        x, y = random.uniform(0, 1), random.uniform(0, 3)
        if y < func(x): in_d += 1

    print('M-K:')
    print('\t%s\t%s' % (n, abs(in_d/n * 3)))

monte_karlo_method(lambda x: math.e ** x, 100)
print('True value:\n\t%s' % get_i())
