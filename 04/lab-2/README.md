# Laboratory work №2 "Newton equation solving"
All tasks are placed on the portal of my university.

Briefly, the task was to solve systems using special methods:
- Newtons equation solving with direct and embedded calculation of Jacobian
Also inconsistency and absolute error were calculated here.

# Requirements
- `__Cmake__` at least __22.1__ version
- `__C++20__` version (Only STL)
- `__Python3.10__` version (With `sympy` package installed)
- `__Windows 11__` (`uint64_t` was used for sizes)


# Compilation
Just use cmake and select CMakeLists.txt in root directory:
```
mkdir NewtonBuild
cd NewtonBuild
cmake ..
cmake --build
```

## What tools were used
- `Clion 2022.2` (Official Pro)
- `Valgrind` memcheck for debugging
- `Perf-linux` profiler on Kali WSL 2.0
- `Python Community Edition` plugin for Clion

### Sources
[Метод Ньютона для систем нелинейных уравнений](https://algowiki-project.org/ru/%D0%9C%D0%B5%D1%82%D0%BE%D0%B4_%D0%9D%D1%8C%D1%8E%D1%82%D0%BE%D0%BD%D0%B0_%D0%B4%D0%BB%D1%8F_%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC_%D0%BD%D0%B5%D0%BB%D0%B8%D0%BD%D0%B5%D0%B9%D0%BD%D1%8B%D1%85_%D1%83%D1%80%D0%B0%D0%B2%D0%BD%D0%B5%D0%BD%D0%B8%D0%B9)
