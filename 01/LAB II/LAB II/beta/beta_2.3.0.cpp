#include "../headers/config.h"

/*
	* That is a program that outputs all supersimple 
	* numbers in the range from a to b.
	* 
	* NOTE: A number is called supersimple if it is prime, 
	* and the number obtained from the original number by 
	* writing the digits of the original number in
	* reverse order("flip") will also be prime.
	*/


void beta_2_3_0() {
	/* Local variables */
	long long int num{}, reversed_num{}, num_size, a, b;

	cout << "Input 'a':"; cin >> a;
	cout << "Input 'b':"; cin >> b;

	class {
		public: 
			bool operator()(long long int _number) {
				for (long long i{ 2 }; i <= sqrt(_number); i++) {
					// an algorithm that checks a '_number' for simplicity
					if ((_number % i == 0)) {
						printf("Number '%d' is not simple and can be divided by %d \n", int(_number), int(i));
						return false;
					}
				}
				return true;
			}
	} number_prime;
	
	for (a; a <= b; a++) {
	    num = a;
	    num_size = trunc(log10(num)) + 1;
	    
	    auto num_digit_array = make_unique<int[]>(num_size);
	    
	    for (int i{}; i <= num_size; i++) { 
    		// allocate digits of a number to an array
    		num_digit_array[i] = num % 10;
    		num /= 10;
	    }

    	reversed_num = num_digit_array[0];
    
    	for (int i{ 1 }; i < num_size; i++) {
    		// assembling a reversed number
    		reversed_num *= 10;
    		reversed_num += num_digit_array[i];
    	}
    
    	// printf("Revesred 'num' is:%d \n", int(reversed_num));
    
    	if ((number_prime(a) == true) && (number_prime(reversed_num) == true)) {
    		cout << a << " is supersimple! \n";
    	} 
    	else {
    	    ;
    	}
    	
    	reversed_num = 0;
	
	}

	exit(0); // Fixes the console freeze
}