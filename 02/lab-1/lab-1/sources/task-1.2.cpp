#include "../headers/config.h"

/**
 *  The components of file f are integers.
 *  This program obtains file g from the numbers of the original
 *  file, where all positive numbers are written first,
 *  then all negative numbers.
 */

void createTemplateBinFile(string file_name) {
    int amount_min{ 1 }, amount_max{ 2 },
        number_min{ -10 }, number_max{ 15 };

    ofstream outfile(file_name);

    for (int i{}; i <= amount_min + (std::rand() % (amount_max - amount_min + 1)); i++) {
        outfile << number_min + (std::rand() % (number_max - number_min + 1)) << endl;
    }

    outfile.close();
}

void runBeta_1_2() {
    long long max_file_size = 68719476736;
    string file_delimiter = _WIN64 or _WIN32 ? "/" : "\\";

    class UserBinFile {
        public:
            string name;
            string location;
    };

    UserBinFile Input, Output;
    Input.name = "input.bin";
    Input.location = "result" + file_delimiter + Input.name;
    Output.name = "output.bin";
    Output.location = "result" + file_delimiter + Output.name;

    createTemplateBinFile(Input.location);

    ifstream input_file(Input.location, ios::binary);
    ofstream output_file(Output.location, ios::binary);

    if (!input_file.is_open()) {
        cerr << "Could not open the file - '" << Input.name << "'" << endl;
        exit(404);
    }
    else {
        if (filesystem::file_size(Input.location) > max_file_size) {
            cerr << "File is too big";
            exit(400);
        }
        else {
            int file_number;
            while (input_file >> file_number) {
                if (file_number >= 0) {
                    output_file << file_number << endl;
                }
            }

            input_file.clear();
            input_file.seekg(0);

            while (input_file >> file_number) {
                if (file_number <= 0) {
                    output_file << file_number << endl;
                }
            }

            input_file.close();
            output_file.close();
        }
    }

}
