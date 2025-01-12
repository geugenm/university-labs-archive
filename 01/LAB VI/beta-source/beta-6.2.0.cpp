/*
 * Software to define a union with bit fields to represent given information. 
 * The function for displaying the fields on the screen is described here. 
 * We create a random array of such structures. Sort the array elements with 
 * the standard function std::sort. Also, we find repeating elements and display them.
 * 
 * The unifying type double, bit fields: sign, order, mantissa are declared here.
 */


#include "../headers/config.h"

union double_cast {
    double target;
    struct {
        unsigned int mantissa_end : 31;
        unsigned int mantissa_start : 20;
        unsigned int exponent : 11;
        unsigned int sign : 1;
    } parts;
};

void randomFilling(double_cast struct_array[], int struct_size, double rand_min, double rand_max) {
    for (int i{}; i < struct_size; i++) {
        double rand_value = (double)rand() / RAND_MAX;
        struct_array[i].target = rand_min + rand_value * (rand_max - rand_min);
    }
}

void outputBitField(double_cast struct_array, int struct_size) {
    printf("Value = %f\n", struct_array.target);
    /* Using hex view */
    printf("Sign = %x\n", struct_array.parts.sign);
    printf("Exponent = %x\n", struct_array.parts.exponent);
    printf("Mantissa = %x%x\n\n", struct_array.parts.mantissa_start, struct_array.parts.mantissa_end);
}

void sortUnion(double_cast struct_array[], int struct_size) {

    double* buffer = new double[struct_size];

    for (int i{}; i < struct_size; i++) {
        buffer[i] = struct_array[i].target;
    }

    sort(buffer, buffer + struct_size);

    for (int i{}; i < struct_size; i++) {
        struct_array[i].target = buffer[i];
    }
}

void runBeta_6_2_0() {

    srand(time_t(NULL));

    /* Configuration */

    const int elements_amount = 25;
    double rand_infinum = -1.0, rand_supremum = -1.0;

    double_cast* exemplary = new double_cast[elements_amount];

    /* Hook */

    randomFilling(exemplary, elements_amount, rand_infinum, rand_supremum);

    sortUnion(exemplary, elements_amount);

    for (int i{}; i < elements_amount; i++) {
        for (int j = i + 1; j < elements_amount; j++) {
            if (exemplary[i].target == exemplary[j].target) {
                outputBitField(exemplary[i], elements_amount);
            }
        }
    }

}