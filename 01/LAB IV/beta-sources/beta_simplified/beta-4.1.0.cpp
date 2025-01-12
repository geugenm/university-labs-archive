#include "../headers/config.h"
 
int main() {
    const int num_size = 4;
    int num, num_set[num_size], j{}, counter{};;
    
    for (int i{}; i <= 3; i++) {
        cout << "Enter a number:"; cin >> num_set[i];
    }

    map <int, string> rome_digits = {
        {1, "M"},
        {2, "MM"},
        {3, "MMM"},
        {4, "MMMM"},
        {5, "MMMMM"},
        {6, "MMMMMM"},
        {7, "MMMMMMM"},
        {8, "MMMMMMMM"},
        {9, "MMMMMMMMM"},

        {10, "C"},
        {11, "CC"},
        {12, "CCC"},
        {13, "CCCC"},
        {14, "D"},
        {15, "DC"},
        {16, "DCC"},
        {17, "DCCC"},
        {18, "CM"},

        {20, "X"},
        {21, "XX"},
        {22, "XXX"},
        {23, "XXXX"},
        {24, "L"},
        {25, "LX"},
        {26, "LXX"},
        {27, "LXXX"},
        {28, "XC"},

        {30, "I"},
        {31, "II"},
        {32, "III"},
        {33, "IV"},
        {34, "V"},
        {35, "VI"},
        {36, "VII"},
        {37, "VIII"},
        {38, "X"},
    };

    for (int i{1}, k{1}; i <= 36; i++, k++) {
        if (num_set[j] == k) {
            cout << rome_digits[i];
            counter++;
            i = 0; i += counter*10 - 1;
            k = 0;
            j++;
        }
    }
}