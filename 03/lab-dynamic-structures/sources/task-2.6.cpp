/*
 * Perform tasks using bi-linked dynamic data structures in the form of
 * as linked components. Estimate the asymptotic complexity of the algorithm.
 *
 *
 *  2. Given a natural number n, the real numbers x1, x2, ... xn. Develop
 *  a program of evaluating the value of the following expression:
 *	(x1 + xn) * (x2 + xn-1) ... (xn + x1).
 *
 */


#include "../headers/config.h"


 // ─── TYPE AND FUNCTION INITIALIZATION ───────────────────────────────────────────

struct Link {
	double sequence_element;
	Link * next;
	Link * previous;
};


void addListMember(Link *& top, Link *& end, double key);

void randomFillList(Link *& top, Link *& end, unsigned int quantity);

void outputList(Link * top);

double calculateSequenceEquation(Link * top, Link * end, unsigned int quantity);

// ────────────────────────────────────────────────────────────────────────────────



// ─── CORE FUNCTION ──────────────────────────────────────────────────────────────

void runBeta_2_6() {
	unsigned int sequence_members_number;
	cout << "Determine the number of members of the sequence: "; cin >> sequence_members_number;
	cout << endl;

	Link * sequence_start = NULL, * sequence_end = NULL;
	randomFillList(sequence_start, sequence_end, sequence_members_number);
	outputList(sequence_start);

	cout << "Multiplication result: " << fixed << calculateSequenceEquation(sequence_start, sequence_end, sequence_members_number) << endl;
	delete sequence_start, sequence_end;
}

// ────────────────────────────────────────────────────────────────────────────────



// ─── FUNCTION DEFINITION ────────────────────────────────────────────────────────

void addListMember(Link *& top, Link *& end, double key) {
	Link * new_value;

	new_value = new Link;
	new_value->sequence_element = key;
	new_value->next = NULL;
	new_value->previous = NULL;

	if (!top) {
		top = new_value;
		end = new_value;
	}
	else {
		new_value->next = top;
		top->previous = new_value;
		top = new_value;
	}
}

void randomFillList(Link *& top, Link *& end, unsigned int quantity) {
	random_device random_figure;
	mt19937 generate_figure(random_figure());
	uniform_real_distribution<double> real_range(0.0, 100.0);

	double key;
	for (unsigned int i {}; i < quantity; i++) {
		key = real_range(generate_figure);
		addListMember(top, end, key);
	}
}

void outputList(Link * top) {
	cout << "Formed list:" << endl;
	while (top) {
		cout << top->sequence_element << ' ';
		top = top->next;
	}
	cout << endl << endl;
}

double calculateSequenceEquation(Link * top, Link * end, unsigned int quantity) {
	double multiplication = 1;

	for (unsigned int i {}; i < quantity; i++) {
		multiplication *= top->sequence_element + end->sequence_element;
		top = top->next;
		end = end->previous;
	}

	return multiplication;
}

// ────────────────────────────────────────────────────────────────────────────────