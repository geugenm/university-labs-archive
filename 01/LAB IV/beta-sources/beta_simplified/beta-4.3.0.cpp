#include "../headers/config.h"

string reverseString(string _user_input) {
    _user_input = _user_input.erase(0, _user_input.find_last_of(' ') + 1);
    
    cout << _user_input << "\n";

    return _user_input;
}

int main() {
    string initial_phrase, letters, result;

    cout << "Enter a phrase:"; getline(cin, initial_phrase);

    istringstream is(reverseString(initial_phrase));

    is >> letters; // Read the first word from the stream

    for(int i{}; i < 5; i++) {
        random_shuffle(letters.begin(), letters.end());
        result += letters + ' ';
    }
    cout << result;
}
