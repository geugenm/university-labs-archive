import numpy as np
from scipy import optimize


def ForwardEuler(F, u0, tau, T):
    """
    > The function `ForwardEuler` takes as input a function `F`, an initial condition `u0`, a time step `tau`, and a final
    time `T`, and returns the numerical solution `u` and the time points `t`

    :param F: the function that defines the differential equation
    :param u0: initial condition
    :param tau: time step
    :param T: the total time of the simulation
    :return: the solution u and the time steps t.
    """
    N_t = int(round(T / tau))
    F_ = lambda t, u: np.asarray(F(t, u))
    t = np.linspace(0, N_t * tau, N_t + 1)
    u = np.zeros((N_t + 1, len(u0)))
    u[0] = np.array(u0)
    for n in range(N_t):
        u[n + 1] = u[n] + tau * F_(t[n], u[n])

    return u, t


def BackwardEuler(F, u0, tau, T):
    """
    > The function `BackwardEuler` takes as input a function `F`, an initial condition `u0`, a time step `tau`, and a final
    time `T`, and returns the numerical solution `u` and the time points `t`

    :param F: the function that defines the ODE
    :param u0: initial condition
    :param tau: time step
    :param T: the total time of the simulation
    :return: the solution u and the time points t.
    """
    N_t = int(round(T / tau))
    F_ = lambda t, u: np.asarray(F(t, u))
    t = np.linspace(0, N_t * tau, N_t + 1)
    u = np.zeros((N_t + 1, len(u0)))
    u[0] = np.array(u0)

    def Phi(z, t, v):
        return z - tau * F_(t, z) - v

    for n in range(N_t):
        u[n + 1] = optimize.fsolve(Phi, u[n], args=(t[n], u[n]))

    return u, t
