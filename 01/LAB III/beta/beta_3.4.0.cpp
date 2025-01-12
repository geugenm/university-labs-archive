#include "../headers/config.h"

/*  
    * Output the sequence dk, dk-1, ..., d0 decimal digits of
    * number 3^200, i.e. such integer sequence in which each term 
    * di satisfies the condition and the sequence.
    * via https://www.cyberforum.ru/pascal/thread2420034.html
    */

int main() {
    int n[100] = {1, 1};

    for (int p{1}; p <= 3; p++) {
        int b{0};
        for(int i{1}; i <= n[0]; i++) {
            b = b + n[i] * 3; printf("b_in: %d \n", b);
            n[i] = b % 10; printf("n[%d]: %d \n", i, n[i]);
            b /= 10; printf("b_out: %d \n", b);
        }
        if (b > 0) {
            n[0] += 1; printf("n[0]: %d \n", n[0]);
            n[n[0]] = b; printf("n[n[0]]: %d \n", n[n[0]]);
        }
    }

    for (int j{n[0]}; j > 0; j--) {
        cout << n[j];
    }
}