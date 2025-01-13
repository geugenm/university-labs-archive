import math
import matplotlib.pyplot as plt


# Constants
g = 9.81  # acceleration due to gravity (m/s^2)
rho_0 = 1.225  # sea level air density (kg/m^3)
T_0 = 288.15  # sea level temperature (K)
L = 0.0065  # temperature lapse rate (K/m)
M = 0.0289644  # molar mass of dry air (kg/mol)
R = 8.31447  # ideal gas constant (J/mol*K)

def calculate_drag_force(mass, radius, length, h):
    # Calculate air density at altitude
    T = T_0 - L * h  # temperature at altitude (K)
    P = 101325 * (1 - L * h / T_0) ** (g * M / (R * L))  # pressure at altitude (Pa)
    rho = P / (R * T / M)  # air density at altitude (kg/m^3)

    # Calculate terminal velocity
    A = math.pi * radius**2  # surface area of cylinder (m^2)
    C_D_cylinder = 0.82  # drag coefficient of a cylinder
    C_D_sphere = 0.47  # drag coefficient of a sphere
    C_D = C_D_cylinder + (C_D_sphere - C_D_cylinder) * radius / (radius + length)  # drag coefficient of cylinder with spherical tip
    v_terminal = math.sqrt(2 * mass * g / (rho * C_D * A))  # terminal velocity (m/s)

    # Calculate time elapsed
    t = h / v_terminal  # time elapsed (s)

    return v_terminal, t, rho, C_D, A

def main():
    mass = 2  # mass of object (kg)
    radius = 0.1  # radius of cylinder (m)
    length = 0.5  # length of cylinder (m)
    h = 2000  # initial altitude (m)

    v_terminal, t, rho, C_D, A = calculate_drag_force(mass, radius, length, h)

    # Calculate distance traveled and acceleration
    s = v_terminal * t  # distance traveled (m)
    a = v_terminal / t  # acceleration (m/s^2)

    # Calculate forces
    F_grav = mass * g  # gravitational force (N)
    F_drag = 0.5 * rho * v_terminal**2 * C_D * A  # drag force (N)

    # Print results
    print(f'Terminal velocity of object: {v_terminal:.2f} m/s')
    print(f'Time elapsed: {t:.2f} s')
    print(f'Distance traveled: {s:.2f} m')
    print(f'Acceleration: {a:.2f} m/s^2')
    print(f'Gravitational force: {F_grav:.2f} N')
    print(f'Drag force: {F_drag:.2f} N')

    # Create plot
    plt.plot(t, s)
    plt.xlabel('Time elapsed (s)')
    plt.ylabel('Distance traveled (m)')
    plt.title('Fall of Cylinder with Spherical Tip')



if __name__ == '__main__':
    main()

