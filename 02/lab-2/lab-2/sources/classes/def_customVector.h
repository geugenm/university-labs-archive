#pragma once

#include "dec_customVector.h"
#include "../../headers/config.h"

namespace cvect {
	template <typename T>
	class customVector {
	private:
		T * custom_vector;

		unsigned capacity {};

		unsigned current_elements_number {};

	public:
		explicit customVector() {
			customVector = new T[1];
			custom_vector[0] = 0;

			capacity += 1;
			current_elements_number += 1;
		}

		explicit customVector(unsigned _size) {
			custom_vector = new T[_size];

			std::fill_n(custom_vector, _size, 0);

			capacity += _size + 1;
			current_elements_number += _size;
		}

		explicit customVector(const customVector & _sample) {
			custom_vector = _sample.custom_vector;
			capacity += _sample.capacity;
			current_elements_number += _sample.current_elements_number;
		}

		~customVector() {
			std::fill_n(custom_vector, current_elements_number, 0);
			capacity *= 0;
			current_elements_number *= 0;
		}


		//T & operator [] (unsigned _index); // L-value return case

		T operator [] (unsigned _index); // R-value return case

		friend std::istream & operator >> (std::istream & _in, customVector & _object);

		friend std::ostream & operator << (std::ostream & _out, customVector & _object);


		void addElement(T _data);

		void editElement(T _data, unsigned _index);

		T getElementByIndex(unsigned _index);


		unsigned getSize() {
			return current_elements_number;
		}

		unsigned getCapacity() {
			return capacity;
		}
	};
}
