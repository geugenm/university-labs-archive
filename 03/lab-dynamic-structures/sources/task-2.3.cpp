/*
 * Create a linked data structure - a list. Develop functions to perform basic
 * operations on linear related structures that contain records with information
 * about students: full name, date of birth, course, grades. When adding a data
 * item to the list, provide alphabetical ordering of the surnames.
 * Estimate asymptotic complexity of the algorithm.
 *
 *	 2. Using the initial list to determine the full name of the oldest student on
 *	 each course. Generate a list of these students by removing them from the initial list.
 *
 */


#include "../headers/config.h"


 //
 // ────────────────────────────────────────────────────────────────────────────────────────────────── I ──────────
 //   :::::: T Y P E   A N D   F U N C T I O N   D E F E N I T I O N S : :  :   :    :     :        :          :
 // ────────────────────────────────────────────────────────────────────────────────────────────────────────────
 //

struct UserStudent {
	string initials = " ";
	int birth_date {};

	int id {};

	int course {};
	int achievement {};
};

struct List {
	UserStudent _data;
	List * _next = nullptr;
};

void printStudentList(List * _list, int _list_size, string _list_name);

void addFrontElement(List ** _list, UserStudent & _student_info);


//
// ────────────────────────────────────────────────────────────────── II ──────────
//   :::::: C O R E   F U N C T I O N : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────
//

void runBeta_2_3() {


	// ─── INITIALIZATION SECTION ─────────────────────────────────────────────────────

	unsigned int student_amount;
	cout << "Input students amount:"; cin >> student_amount;

	const int CHAR_NUMBER = 128;

	int * surname_symbols = new int[CHAR_NUMBER];
	fill_n(surname_symbols, CHAR_NUMBER, 0);

	unsigned int courses = 10;

	int * course_max_age = new int[courses];
	fill_n(course_max_age, courses, 2022);


	List * iterator = nullptr;

	UserStudent buffer;


	List * initial_student_list = NULL;
	initial_student_list = new List;


	// ─── PROGRAM HOOK ───────────────────────────────────────────────────────────────

	for (unsigned int i {}; i < student_amount; i++) {
		// Filling the 'initial_student_list'
		cout << "Initials: "; cin >> buffer.initials;
		cout << "Birth date: "; cin >> buffer.birth_date;
		cout << "Course: "; cin >> buffer.course;
		cout << "Achievement: "; cin >> buffer.achievement;
		buffer.id = i;

		course_max_age[buffer.course] = min(course_max_age[buffer.course], buffer.birth_date);

		surname_symbols[int(buffer.initials[0])] = 1;

		addFrontElement(&initial_student_list, buffer);

		cout << endl;
	}

	delete & buffer;


	printStudentList(initial_student_list, student_amount, "Initial student list");

	List * sorted_student_list = NULL;
	sorted_student_list = new List;

	for (unsigned int i = CHAR_NUMBER - 1; i > 0; i--) {
		// Alphabetical sorting of the 'initial_student_list'
		if (surname_symbols[i]) {
			iterator = initial_student_list;
			for (unsigned int j {}; j < student_amount; j++) {
				if (i == iterator->_data.initials[0]) {
					addFrontElement(&sorted_student_list, iterator->_data);
				}

				iterator = iterator->_next;
			}
		}
	}

	printStudentList(sorted_student_list, student_amount, "Sorted student list");

	List * course_senior_student_list = NULL;
	course_senior_student_list = new List;

	unsigned int counter {};

	for (unsigned int i {}; i < courses; i++) {
		// Getting the oldest student from the course
		iterator = sorted_student_list;
		for (unsigned int j {}; j < student_amount; j++) {
			if (course_max_age[i] == iterator->_data.birth_date) {
				addFrontElement(&course_senior_student_list, iterator->_data);
				counter++;
			}
			iterator = iterator->_next;
		}

	}

	delete sorted_student_list;


	printStudentList(course_senior_student_list, counter, "Senior student list");

	List * final_student_list = NULL;
	final_student_list = new List;

	iterator = initial_student_list;

	for (unsigned int i {}; i < student_amount; i++) {
		// Building a final list, deleting the oldest students from the course
		List * senior_iterator = course_senior_student_list;
		for (unsigned int j {}; j < counter; j++) {
			if (senior_iterator->_data.id == iterator->_data.id) {

			}
			else {
				addFrontElement(&final_student_list, iterator->_data);
				senior_iterator = senior_iterator->_next;
			}
		}
		iterator = iterator->_next;
	}

	delete course_senior_student_list, initial_student_list;

	printStudentList(final_student_list, student_amount - counter, "Final student list");

	delete final_student_list;
}


//
// ──────────────────────────────────────────────────────────────────────────────── III ──────────
//   :::::: F U N C T I O N S   D E F I N I T I O N : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────────────────
//

void printStudentList(List * _list, int _list_size, string _list_name) {

	List * iterator = _list;

	cout << "\n" << _list_name << ":" << endl << endl;

	for (int i {}; i < _list_size; i++) {
		cout << "Initials: " << iterator->_data.initials << endl;
		cout << "Birth date: " << iterator->_data.birth_date << endl;
		cout << "Course: " << iterator->_data.course << endl;
		cout << "Achievement: " << iterator->_data.achievement << endl;
		cout << "ID: " << iterator->_data.id << " " << endl << endl;

		iterator = iterator->_next;
	}

}

void addFrontElement(List ** _list, UserStudent & _student_info) {

	List * iterator = new List;

	iterator->_data.initials = _student_info.initials;
	iterator->_data.birth_date = _student_info.birth_date;
	iterator->_data.course = _student_info.course;
	iterator->_data.achievement = _student_info.achievement;
	iterator->_data.id = _student_info.id;

	iterator->_next = *_list;

	*_list = iterator;
}
