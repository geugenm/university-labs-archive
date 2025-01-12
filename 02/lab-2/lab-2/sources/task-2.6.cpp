#include "headers/config.h"

#include <easylogging++.h>

#define Object_Name(x) #x

//
// ─── COUNSOLE COLOR MODIFIER NAMESPACE ──────────────────────────────────────────
//
namespace console {
	void textColor(const unsigned char OUTPUT_COLOR) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, OUTPUT_COLOR);
	}

	void setDefaultColor() {
		const unsigned char DEAFULT_CONSOLE_COLOR = 7;

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, DEAFULT_CONSOLE_COLOR);
	}
}

//
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── I ──────────
//   :::::: M U L T I D I G I T N U M B E R   C L A S S   D E C L A R A T I O N : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
//

class MultidigitNumber {
private:
	long long unsigned digit_size{};
	std::vector<long long> digit_array{};

public:
	//
	// ─── CONSTRUCTORS ───────────────────────────────────────────────────────────────
	//

	MultidigitNumber() {
		digit_array.push_back(0);
		LOG(INFO) << "Default constructor : Object succesfully created";
	}

	explicit MultidigitNumber(long long unsigned size) {
		digit_size += size;
		for (long long unsigned i{}; i < digit_size; i++) {
			digit_array.push_back(0);
		}
		LOG(INFO) << "Parameter constructor : Object succesfully created";
	}

	MultidigitNumber(const MultidigitNumber & copy_template) : digit_size(copy_template.digit_size) {
		for (long long unsigned i{}; i < digit_size; i++) {
			digit_array.push_back(copy_template.digit_array[i]);
		}

		LOG(INFO) << "Copy constructor : Object '" << Object_Name(copy_template) << "' copying is successful";
	}

	~MultidigitNumber() {
		digit_array.clear();
		LOG(INFO) << "Destructor : Object succesfully deleted";
	}

	//
	// ─── OPERATORS ──────────────────────────────────────────────────────────────────
	//

	friend std::istream & operator >> (std::istream &, MultidigitNumber &);
	friend std::ostream & operator << (std::ostream &, const MultidigitNumber &);

	long long & operator [] (long long unsigned);
	const  long long & operator [] (long long unsigned) const;

	MultidigitNumber operator * (const MultidigitNumber &);
	MultidigitNumber operator + (const MultidigitNumber &);
	MultidigitNumber & operator = (const MultidigitNumber &);

	void operator += (const MultidigitNumber &);
	void operator *= (const MultidigitNumber &);

	//
	// ─── METHODS ────────────────────────────────────────────────────────────────────
	//

	void resize(long long unsigned);
};


//
// ──────────────────────────────────────────────────────────────────────────────── II ──────────
//   :::::: O P E R A T O R S   D E F I N I T I O N : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────────────────
//

std::ostream & operator << (std::ostream & out, const MultidigitNumber & target) {
	for (auto element : target.digit_array) {
		out << element << " ";
	}
	return out;
}

std::istream & operator >> (std::istream & in, MultidigitNumber & target) {
	for (long long unsigned i = target.digit_size - 1; i > 0; i--) {
		scanf_s("%d", &target[i]);
	}
	return in;
}


long long & MultidigitNumber::operator[](const long long unsigned index) {
	if (index >= digit_size) {
		console::textColor(12);
		LOG(ERROR) << "operator[const] : Index '" << index << "' is not valid";
		console::setDefaultColor();
		exit(1);
	}
	return digit_array[index];
}

const long long & MultidigitNumber::operator[](long long unsigned index) const {
	if (index >= digit_size) {
		console::textColor(12);
		LOG(ERROR) << "const operator[] : Index '" << index << "' is not valid";
		console::setDefaultColor();
		exit(1);
	}
	return digit_array[index];
}


MultidigitNumber & MultidigitNumber::operator = (const MultidigitNumber & target) {
	if (&target != this) {
		for (long long unsigned i{}; i < target.digit_size; i++) {
			digit_array[i] = target.digit_array[i];
		}
	}

	digit_size = target.digit_size;
	return *this;
}

MultidigitNumber MultidigitNumber::operator + (const MultidigitNumber & addendum) {
	long long unsigned new_size = max(addendum.digit_size, digit_size) + 1;

	MultidigitNumber result(new_size);

	for (long long unsigned i{}; i < addendum.digit_size; i++) {
		result[i] += addendum[i];
	}

	for (long long unsigned i{}; i < digit_size; i++) {
		result[i] += digit_array[i];
	}

	return result;
}

void MultidigitNumber::operator += (const MultidigitNumber & addendum) {
	resize(max(addendum.digit_size, digit_size) + 1);

	for (long long unsigned i{}; i < addendum.digit_size; i++) {
		if (digit_array[i] + addendum.digit_array[i] < max(digit_array[i], addendum.digit_array[i])) {
			digit_array[i + 1]++;
			digit_array[i] = digit_array[i] + addendum.digit_array[i];
		}
		else {
			digit_array[i] = digit_array[i] + addendum.digit_array[i];
		}
	}

	if (digit_array[digit_size - 1] == 0) {
		digit_size--;
	}
}

MultidigitNumber MultidigitNumber::operator * (const MultidigitNumber & multiplier) {
	long long unsigned new_size = max(multiplier.digit_size, digit_size) * 2;
	MultidigitNumber result(new_size);

	for (long long unsigned i{}; i < multiplier.digit_size; i++) {
		for (long long unsigned j{}; j < digit_size; j++) {
			long long Pro = digit_array[j] * multiplier.digit_array[i];

			long long first = Pro % 4294967296;
			long long second = (Pro - first) / 4294967296;

			result[j + i] += first;
			result[j + i + 1] += second;
		}
	}

	while (result[result.digit_size - 1] == 0) {
		result.digit_size--;
	}
	return result;
}

void MultidigitNumber::operator *= (const MultidigitNumber & multiplier) {
	long long unsigned new_size = max(multiplier.digit_size, digit_size) * 2;
	MultidigitNumber result(new_size);

	for (long long unsigned i{}; i < multiplier.digit_size; i++) {
		for (long long unsigned j{}; j < digit_size; j++) {
			long long Pro;
			Pro = digit_array[j] * multiplier.digit_array[i];

			long long first = Pro % 4294967296;
			long long second = (Pro - first) / 4294967296;

			result.digit_array[j + i] += first;
			result.digit_array[j + i + 1] += second;
		}
	}

	while (result[result.digit_size - 1] == 0) {
		result.digit_size--;
	}

	*this = result;
}

//
// ──────────────────────────────────────────────────────────────────────────────── III ──────────
//   :::::: F U N C T I O N S   D E F I N I T I O N : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────────────────
//

void MultidigitNumber::resize(long long unsigned new_size) {
	std::vector<long long> resize_buffer;
	resize_buffer.resize(new_size, 0);

	if (new_size <= digit_size) {
		for (long long unsigned i{}; i < new_size; i++) {
			resize_buffer.push_back(digit_array[i]);
		}
	}
	else {
		for (long long unsigned i{}; i < digit_size; i++) {
			resize_buffer[i] = digit_array[i];
		}
	}

	digit_array.clear();

	for (long long unsigned i{}; i < resize_buffer.size(); i++) {
		digit_array.push_back(resize_buffer[i]);
	}

	digit_size = new_size;
}

//
// ────────────────────────────────────────────────────────────────── IV ──────────
//   :::::: C O R E   F U N C T I O N : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────
//

void runBeta_2_6() {
	long long foundation = 3;
	MultidigitNumber positive;
	MultidigitNumber negative;

	positive.resize(1);
	negative.resize(1);

	positive[0] = foundation;
	negative[0] = -foundation;

	MultidigitNumber result_0 = positive;
	MultidigitNumber result_1 = negative;
	MultidigitNumber result_2 = positive;
	MultidigitNumber result_3 = negative;

	for (unsigned char i = 1; i < 12; i++) {
		result_0 *= positive;
		if (i < 11) {
			result_1 *= negative;
		}
		if (i < 10) {
			result_2 *= positive;
		}
		if (i < 9) {
			result_3 *= negative;
		}
	}

	std::cout << "Expression result: " << result_0 + result_1 + result_2 + result_3 << std::endl;
}
