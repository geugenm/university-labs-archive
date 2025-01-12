#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
int main() {
  setlocale(LC_ALL, "Rus");
  srand(time(NULL));
  int a[50][50], b[50][50] = {0};
  int n;
  cout << "Введите размер матрицы ";
  cin >> n;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      a[i][j] = rand() % 20;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      b[i][j] = a[i][j];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (b[i][j] == 0)
        b[i][j] = 21;
  int l = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - 1; j++) {
      for (int q = j + 1; q <= n; q++) {
        if (b[i][j] == b[i][q]) {
          b[i][q] = 0;
          ;
          l++;
        }
      }
      if (l != 0)
        b[i][j] = 0;
      l = 0;
    }
    l = 0;
  }

  int e;
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < n; i++) {
      if (b[j][i] == 0) {
        e = i;
        while (b[j][e] == 0)
          e++;
        if (e > n)
          e = n;
        b[j][i] = b[j][e];
        b[j][e] = 0;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (a[i][j] == 21) {
        a[i][j] = 0;
      }
      cout << setw(3) << a[i][j];
    }
    cout << endl;
  }
  cout << "Новая матница" << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (b[i][j] == 21) {
        b[i][j] = 0;
      }
      cout << setw(3) << b[i][j];
    }
    cout << endl;
  }
}
