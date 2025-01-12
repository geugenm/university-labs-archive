#include "../headers/config.h"

/*
    * A program to convert from hexadecimal to binary
    * Original code source - https://stackoverflow.com/questions/8551383/how-to-convert-a-hexadecimal-string-to-a-binary-string-in-c
    */

int main() {
    int p{};
    char result[1024]; result[0] = '\0';

    const char hex_digits_in_binary[16][5] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    const char hex_digits[] = "0123456789abcdef";

    const char input[] = "1ab";

    while(input[p]) {
        const char *v = strchr(hex_digits, tolower(input[p++]));
        if (v) {
            strcat(result, hex_digits_in_binary[v - hex_digits]);
        }
    }
    
    for(int i{}; i <= strlen(result) - 1; i++) { 
        cout << result[i];
    }
}
