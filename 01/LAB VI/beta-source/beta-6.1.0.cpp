/*
 * This is a program which creates an array of records with information
 * about students (name, age, course, gender, progress). To make the filling,
 * input and output of the array by separate functions. There is a function which
 * identifies the name of the youngest student in the n course.
 *
 * TODO:
 *  1. (Additional)Random Data generation function
 */

#include "../headers/config.h"

#define data_source "csv/students.csv"


struct user_student {
	string id = "";

	string surname = "";
	string name = "";
	string patronymic = "";

	string age = "";
	string course = "";
	string gender = "";
	string pass_rate = "";
};

void outputUserData(user_student group_name[], int student_id) {
	cout << "Id: " << group_name[student_id].id << endl;
	cout << "Surname: " << group_name[student_id].surname << endl;
	cout << "Name: " << group_name[student_id].name << endl;
	cout << "Patronymic: " << group_name[student_id].patronymic << endl;
	cout << "Age: " << group_name[student_id].age << endl;
	cout << "Course: " << group_name[student_id].course << endl;
	cout << "Gender: " << group_name[student_id].gender << endl;
	cout << "Pass Rate: " << group_name[student_id].pass_rate;
}


void runBeta_6_1_0() {
	const int student_amount = 4;
	int minimal_age = 256;
	int target_student;

	ifstream work_file(data_source);
	string line;
	char delimiter = ',';

	user_student* group = new user_student[student_amount];

	if (work_file.is_open()) {
		// Skipping the first label line
		getline(work_file, line);

		for (int i{}; i < student_amount; i++) {
			// Proceeding through the file
			getline(work_file, line);

			stringstream stream(line);

			string id, surname, name, patronymic,
				age, course, gender, pass_rate;

			// Taking the partitial data to local variables
			getline(stream, id, delimiter);
			getline(stream, surname, delimiter);

			getline(stream, name, delimiter);
			getline(stream, patronymic, delimiter);

			getline(stream, age, delimiter);
			getline(stream, course, delimiter);

			getline(stream, gender, delimiter);
			getline(stream, pass_rate, delimiter);

			stream.str("");

			// Distributing data by variable name into the structure
			group[i].id = id;
			group[i].surname = surname;

			group[i].name = name;
			group[i].patronymic = patronymic;

			group[i].age = age;
			group[i].course = course;

			group[i].gender = gender;
			group[i].pass_rate = pass_rate;

			if (minimal_age > stoi(age)) {
				// Finding the youngest user_student
				minimal_age = stoi(age);
				target_student = i;
			}
		}
		work_file.close();

		outputUserData(group, target_student);

	}
	else {
		cout << "File is not found";
	}

}