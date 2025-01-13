import EulerMethods
import Examples

import matplotlib.pyplot as pyplot

if __name__ == '__main__':
    Examples.FirstEquation(EulerMethods.ForwardEuler)
    Examples.FourthEquation(EulerMethods.BackwardEuler)
    pyplot.show()
