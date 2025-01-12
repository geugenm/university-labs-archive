#include "../headers/config.h"

/*
    * A new line of words is written that consist of
    * the same letters as the last word of the given character string.
    */

void shuffleOutput(char *target_array) {
    for(int i{}, k{}; i <= strlen(target_array) + 1; i++) {
        random_shuffle(&target_array[1], &target_array[strlen(target_array)]);
        cout << target_array << endl;
    }
}

int main() {
    int max_input_len{64}, counter{};

    char *user_input = new char[max_input_len];
    char *divider = new char[10]; strcpy(divider, " .,:;!?-()");
    char *last_word_buffer = new char[1];

    cout << "Enter a phrase:"; fgets(user_input, max_input_len, stdin);

    for(int i{}; i <= max_input_len; i++) {
        for(int j{}; j <= 9; j++) {
            if (user_input[i] == divider[j]) {
                counter = i;
            }
        }
    }

    for (int i{counter + 1}, k{}; i <= strlen(user_input) - 1; i++, k++) {
        last_word_buffer[k] = user_input[i];
    }

    shuffleOutput(last_word_buffer);

    exit(0);
}

