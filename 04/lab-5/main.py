import numpy as np
import matplotlib.pyplot as plt
import scipy.integrate


def process():
    # let's generate x and y, and add some noise into y
    x = np.arange(60, 130, 10)
    print(x)
    y = np.array([0.0148, 0.0124, 0.0102, 0.0085, 0.0071, 0.0059, 0.0051])

    # Let’s fit the data after we applied the log trick.
    A = np.vstack([x, np.ones(len(x))]).T
    beta, log_alpha = np.linalg.lstsq(A, np.log(y), rcond=None)[0]
    alpha = np.exp(log_alpha)
    print(f'alpha={alpha}, beta={beta}')

    # Let's have a look of the data
    plt.figure(figsize=(10, 8))
    plt.plot(x, y, 'b.')
    plt.plot(x, alpha * np.exp(beta * x), 'r')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.show()


def test_func(x):
    return (1 + x ** 3) ** (1 / 2)

def lab5():
    x = np.linspace(0.8, 1.762)
    y1 = test_func(x)
    print(scipy.integrate.trapezoid(y1, x))
    print(scipy.integrate.simpson(y1, x))

if __name__ == '__main__':
    #process()
    lab5()
