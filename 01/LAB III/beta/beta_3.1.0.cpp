#include "../headers/config.h"

/*
    * An array of integers with n elements is given. 
    * To test, it is possible to set the elements of the array in different ways:
    * in the description with initialization, by assigning values (including random ones), 
    * or by entering the necessary values. The choice of the way of initialization of the array is
    * made through the menu with the use of enum.
    */

int main_menu() {
    int choice;
    printf("\nCONFIG:\n 1. Custom\n 2. Auto\n\nMake your choice: "); cin >> choice;
    
    return choice;
}

int main() {
    int size, local_buffer;

    system("cls");  // Use "clear" on LINUX based systems

    cout << "Determine the size:"; cin >> size;

    int *primary_array = new int[size];

    switch (main_menu()) {
    case 2:
        for (int i{}; i < size; i++) {
            primary_array[i] = rand();
            printf("Got element %d: %d \n", i + 1, primary_array[i]);
        }
        break;

    case 1:
        for (int i{}; i < size; i++) {
            printf("Enter element %d: ", i + 1); cin >> primary_array[i];
        }
        break;
    default:
        break;
    }
    

    for (int i{}; i < size; i++) {
        // Bubble sort algorithm
        for (int j{}; j < size - 1; j++) {
            if (primary_array[j] > primary_array[j + 1]) {
                int local_buffer = primary_array[j];
                primary_array[j] = primary_array[j + 1]; // Reverse the values of the array
                primary_array[j + 1] = local_buffer;
            }
        }
    }

    for (int i{}; i < size; i++) {
        cout << primary_array[i] << endl;
    }

}