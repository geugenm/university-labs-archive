/*
 * Perform the task using dynamic memory allocation for a one-dimensional array.
 * Given (in a text file) n>109 positive integers (each number 10^4). The memory
 * limit is 1 Mb. Get the array in one file elements view:
 *
 * 2. In which all the numbers in the source file are arranged in descending order
 * (without repetitions)
 *
 *	WARNING:
 *		This program requires external logger:
 *		> https://github.com/amrayn/easyloggingpp
 *		~ Easylogging for C++
 */

#include "../headers/config.h"
#include "classes/def_customVector.h"

#include <easylogging++.h>


 /// \Todo
 ///		1. Add R-value & L-value support for [] operator (Completed)
 ///		2. Define customVector methods in a separate file (Completed)
 ///		3. Add support for << out operator (Completed)
 ///		4. (Additional) Add custom logger (Completed)
 /// 
 /// > https://metanit.com/cpp/tutorial/8.4.php
 /// ~ Tutorial for >> and << operators



 //
 // ──────────────────────────────────────────────────────────────────────────────── I ──────────
 //   :::::: C U S T O M V E C T O R   M E T H O D S : :  :   :    :     :        :          :
 // ──────────────────────────────────────────────────────────────────────────────────────────
 //


 // ─── OPERATORS DEFINITION ───────────────────────────────────────────────────────

 //! L-value overload for operator []
 /*template<typename T>
 T & cvect::customVector<T>::operator [] (unsigned _index) const {
	 if (_index >= current_elements_number) {
		 std::cout << "Array index out of bound" << std::endl;
		 exit(2);
	 }
	 else {
		 return custom_vector[_index];
	 }
 } */

 //! R-value overload for operator []
template<typename T>
T cvect::customVector<T>::operator [] (unsigned _index) {
	if (_index >= current_elements_number) {
		LOG(ERROR) << "Indexing operator error: array index out of bound";
		return EXIT_FAILURE;
	}
	else {
		return custom_vector[_index];
	}
}

//! Overload for operator >>
template <typename T>
std::ifstream & operator >> (std::ifstream & _in, cvect::customVector<T> & _object) {
	unsigned object_size = _object.getSize();
	for (unsigned i {}, element; i < object_size; i++) {
		_in >> element;

		_object.editElement(1, element); // R-value return case

		//_object[element] = 1; // L-value return case
	}
	return _in;
}

//! Overload for operator <<
template <typename T>
std::ostream & operator << (std::ostream & _out, cvect::customVector<T> & _object) {
	unsigned object_size = _object.getSize();
	const char delimiter[2] = {' ', '\0'};

	for (unsigned i {}; i < object_size; i++) {
		_out << _object.getElementByIndex(i) << delimiter[0];
	}

	return _out;
}


// ─── METHODS DEFINITIONS ────────────────────────────────────────────────────────

//! Add element to the end of vector method
template <typename T>
void cvect::customVector<T>::addElement(T _data) {
	if (current_elements_number == capacity) {
		auto * temp = new T[capacity + 2];
		std::fill_n(temp, capacity + 2, 0);

		for (unsigned i {}; i < capacity; i++) {
			temp[i] = custom_vector[i];
		}

		capacity += 2;

		custom_vector = temp;
	}

	// Inserting data
	custom_vector[current_elements_number] = _data;
	current_elements_number++;
}

//! Replace element of the vector by index method
template <typename T>
void cvect::customVector<T>::editElement(T _data, unsigned _index) {
	if (_index == capacity) {
		addElement(_data);
	}
	else {
		custom_vector[_index] = _data;
	}
}

//! Get element by index method
template <typename T>
T cvect::customVector<T>::getElementByIndex(unsigned _index) {
	if (_index < current_elements_number) {
		return custom_vector[_index];
	}
	LOG(ERROR) << "getElementByIndex() error: retrieved index is larger than current elements number";
	return EXIT_FAILURE;
}



//
// ──────────────────────────────────────────────────────────────────── II ──────────
//   :::::: T A S K   F U N C T I O N S : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────
//

void createFile(std::string _file_name, const unsigned _max_array_number);


//! runBeta_2_1() core function section
void runBeta_2_1() {
	std::string file_name = "filename.txt";
	const unsigned MAX_ARRAY_NUMBER = 10000;

	createFile(file_name, MAX_ARRAY_NUMBER);

	cvect::customVector<bool> task_vector(MAX_ARRAY_NUMBER + 1);

	// Reading file section
	std::ifstream Myfile(file_name, std::ios_base::in);

	Myfile >> task_vector;

	Myfile.close();


	for (unsigned i = MAX_ARRAY_NUMBER; i > 0; i--) {
		if (task_vector.getElementByIndex(i)) {
			std::cout << i << " ";
		}
	}

	std::cout << std::endl;

}

//! CreateFile definition section
void createFile(std::string _file_name, const unsigned _max_array_number) {
	const int MAX_FIGURE_NUMBER = INT_MAX;

	std::random_device random_figure;
	std::mt19937 generate_figure(random_figure());
	std::uniform_int_distribution<> distr(1, _max_array_number);

	std::ofstream MyFile(_file_name);

	for (unsigned i {}; i < MAX_FIGURE_NUMBER; i++) {
		MyFile << distr(generate_figure) << " ";
	}

	MyFile.close();
}