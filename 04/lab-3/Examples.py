import math
import matplotlib.pyplot as pyplot
import sympy


def DefineCalculationSettings():
    """
    It asks the user to define the integration step and step limit, and returns them as a tuple
    :return: the integration step and the step limit.
    """
    integrationStep = float(input('Define integration step: '))
    stepLimit = float(input('Define step limit: '))
    return integrationStep, stepLimit


def FirstEquation(EulerMethodFunction):
    """
    It solves the first equation of the task, using the Euler method

    :param EulerMethodFunction: the function that will be used to calculate the solution
    """
    # Parameters section:
    omega = float(input('Define w [25 (1) 48]'))
    alpha = 2.5 + omega / 40

    tau, T = DefineCalculationSettings()

    # Equation section
    def function(t, u):
        u1, u2 = u
        divider = t
        if t == 0:
            divider = 1e-5
        return [-u1 * u2 + math.sin(t) / divider, - u2 ** 2 + alpha * t / (1 + t ** 2)]

    u0 = [0, -0.412]
    u, t = EulerMethodFunction(F=function, u0=u0, tau=tau, T=T)

    u1 = u[:, 0]
    u2 = u[:, 1]

    plotFigure = pyplot.figure()
    firstPlot, secondPlot = pyplot.plot(t, u1, 'ro', t, u2, 'bo')
    plotFigure.legend((firstPlot, secondPlot), ('$u1$', '$u2$'))
    pyplot.xlabel('X layout')
    pyplot.ylabel('Y values')


def SecondEquation(EulerMethodFunction):
    """
    It defines the parameters of the equation, then it defines the equation itself, then it defines the initial conditions,
    then it calls the Euler method function, then it plots the results

    :param EulerMethodFunction: The function that will be used to calculate the solution
    """
    # Parameters section:
    alpha = float(input('Define a [2 (0.25) 3]'))
    kappa = float(input('Define k [0.25 (0.25) 1.25]'))

    tau, T = DefineCalculationSettings()

    # Equation section
    def function(t, u):
        u1, u2 = u
        return [u2 - (alpha * u1 + kappa * u2) * u1, math.exp(u1) - (u1 + alpha * u2) * u1]

    u0 = [1, 0]

    u, t = EulerMethodFunction(F=function, u0=u0, tau=tau, T=T)

    u1 = u[:, 0]
    u2 = u[:, 1]

    plotFigure = pyplot.figure()
    firstPlot, secondPlot = pyplot.plot(t, u1, 'ro', t, u2, 'bo')
    plotFigure.legend((firstPlot, secondPlot), ('$u1$', '$u2$'))
    pyplot.xlabel('X layout')
    pyplot.ylabel('Y values')


def ThirdEquation(EulerMethodFunction):
    """
    It solves the third equation of the system of equations,
    using the Euler method, and plots the results.

    :param EulerMethodFunction: The function that will be used to calculate the solution
    """
    # Parameters section:
    alpha = float(input('Define a [1 (0.25) 2]'))
    kappa = float(input('Define k [2 (0.25) 3]'))

    tau, T = DefineCalculationSettings()

    # Equation section
    def function(t, u):
        u1, u2, u3 = u
        return [((kappa - alpha) / alpha) * u2 * u3, ((alpha + kappa) / kappa) * u1 * u3,
                ((alpha - kappa) / alpha) * u1 * u2]

    u0 = [1, 1, 1]

    u, t = EulerMethodFunction(F=function, u0=u0, tau=tau, T=T)

    u1 = u[:, 0]
    u2 = u[:, 1]
    u3 = u[:, 2]

    plotFigure = pyplot.figure()
    firstPlot, secondPlot, thirdPlot = pyplot.plot(t, u1, 'ro', t, u2, 'bo', t, u3, 'go')
    plotFigure.legend((firstPlot, secondPlot, thirdPlot), ('$u1$', '$u2$', '$u3$'))
    pyplot.xlabel('X layout')
    pyplot.ylabel('Y values')


def FourthEquation(EulerMethodFunction):
    """
    It solves the fourth equation of the system of equations using the Euler method

    :param EulerMethodFunction: a function that takes in the following parameters:
    """
    symbolicU1, symbolicU2, symbolicU3 = sympy.symbols('u1:4')

    l1 = int(input('Define lambda1: '))
    l2 = int(input('Define lambda2: '))
    l3 = int(input('Define lambda3: '))

    alphaMatrix = (1 / 6) * sympy.Matrix([
        [2 * l1 + 4 * l2, 2 * (l1 - l2), 2 * (l1 - l2)],
        [2 * (l1 - l2), 2 * l1 + l2 + 3 * l3, 2 * l1 + l2 - 3 * l3],
        [2 * (l1 - l2), 2 * l1 + l2 - 3 * l3, 2 * l1 + l2 + 3 * l3]
    ])

    betaMatrix = (- 1 / 6) * sympy.Matrix([
        [4 * l1 + 2 * l2],
        [4 * l1 - l2 - 9 * l3],
        [4 * l1 - l2 + 9 * l3]
    ])

    functionalMatrix = sympy.Matrix([
        [symbolicU1],
        [symbolicU2],
        [symbolicU3]
    ])

    equationMatrix = alphaMatrix * functionalMatrix - betaMatrix

    def function(t, u):
        u1, u2, u3 = u
        return [float(equationMatrix[0, 0].subs(symbolicU1, u1).subs(symbolicU2, u2).subs(symbolicU3, u3)),
                float(equationMatrix[1, 0].subs(symbolicU1, u1).subs(symbolicU2, u2).subs(symbolicU3, u3)),
                float(equationMatrix[2, 0].subs(symbolicU1, u1).subs(symbolicU2, u2).subs(symbolicU3, u3))]

    tau, T = DefineCalculationSettings()

    u0 = [10, 22, 9]

    u, t = EulerMethodFunction(F=function, u0=u0, tau=tau, T=T)

    u1 = u[:, 0]
    u2 = u[:, 1]
    u3 = u[:, 2]

    plotFigure = pyplot.figure()
    firstPlot, secondPlot, thirdPlot = pyplot.plot(t, u1, 'ro', t, u2, 'bo', t, u3, 'go')
    plotFigure.legend((firstPlot, secondPlot, thirdPlot), ('$u1$', '$u2$', '$u3$'))
    pyplot.xlabel('X layout')
    pyplot.ylabel('Y values')
