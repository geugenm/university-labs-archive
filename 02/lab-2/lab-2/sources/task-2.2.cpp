/*
 * Declare a template of the "Linear list" class. Define the class structure
 * and its methods. The class must have a default constructor, a constructor with
 * formal parameters, a copy constructor and a destructor.
 *
 * Define methods:
 * 	- initializing the first element of the structure
 * 	- adding a new element to the structure
 * 	- deleting an element
 * 	- searching for an element by the specified search key
 *	- displaying the list items on the screen
 *	- list deletions
 *
 * Using the objects of the "Linear list" class the 2nd variant of task 2.4 is realized:
 * 		Describe a function that forms a character list L2, including those characters
 *		from L1, which enter it more than once.
 *
 * Used materials:
 * 	> https://prog-cpp.ru/data-ols-oop/
 * 	~ A single-link linear list based on OOP classes
 *
 * External dependecies:
 * 	> https://github.com/amrayn/easyloggingpp
 * 	~ EasyLogging++ custom logger
*/

/// \Todo
///		1. Add support for any type (???)
///		2. Add parameter constructor (Completed)
///		3. Complete task 2.4 from computing internship (Completed)
///		4. Refactor the code + create comments & docs (Completed)

#include "headers/config.h"
#include "classes/def_customVector.h"

#include <easylogging++.h>

//
// ──────────────────────────────────────────────────────────────────────────────────────── I ──────────
//   :::::: C L A S S   D E F I N I T I O N   S E C T I O N : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────────────────────────
//

class Node {
	char field{};
	class Node * pointer = nullptr;
	friend class List;
};

class List {
private:
	Node * head_node = nullptr;
	unsigned node_count{};
	Node * getPreviousNode(Node const *);
public:
	List() {
		LOG(INFO) << "List Constructor: List succesfully created";
	}

	explicit List(char _value) {
		auto element = std::make_unique<Node>();

		element->field = _value;
		element->pointer = nullptr;
		head_node = element.release();

		LOG(INFO) << "Argument List Constructor: List succesfully created";
	}

	~List() {
		class Node * buffer = head_node;

		if (buffer == nullptr) {
			LOG(INFO) << "List Destructor : List is already empty";
			return;
		}

		// It's safer just to redefine private section, than to delete it

		do {
			Node * local = buffer;
			buffer = getNextNode(buffer);
			local->pointer = nullptr;
			local->field = 0;
		} while (buffer != nullptr);

		node_count = 0;
		head_node = nullptr;

		LOG(INFO) << "List Destructor : List succesfully deleted";
	}

	// The same logic is used by 'insertNode' method
	List & operator = (List _source) noexcept {
		if (_source.head_node == nullptr) {
			LOG(INFO) << "Assigment operator : Sample list is empty";
			return *this;
		}

		class Node * source_ptr_buffer = _source.head_node;

		do {
			auto element = std::make_unique<Node>();
			element->field = source_ptr_buffer->field;

			if (head_node == nullptr) {
				element->pointer = nullptr;
				head_node = element.release();
			}
			else {
				element->pointer = head_node;
				head_node = element.release();
			}

			node_count++;

			source_ptr_buffer = getNextNode(source_ptr_buffer);
		} while (source_ptr_buffer != nullptr);

		LOG(INFO) << "Assigment operator : List is succesfully copied";

		return *this;
	}

	bool listIsEmpty() const {
		return head_node == nullptr;
	}

	char getNodeValue(const Node * _node) const {
		return _node->field;
	}

	void clearList();
	void printList();

	Node * insertNode(char _value, Node * _node);
	Node * getNodeByKey(char _key);
	Node * deleteNode(Node * _node);

	Node * getNextNode(Node * _node);
};

// ─── CLASS METHODS ──────────────────────────────────────────────────────────────

//! getPreviousNode() method
Node * List::getPreviousNode(Node const * _node) {
	if (listIsEmpty()) {
		LOG(INFO) << "getPreviousNode() : head_node is empty, skipping";
		return nullptr;
	}

	if (_node == head_node) {
		LOG(INFO) << "getPreviousNode() : got head_node, skipping";
		return nullptr;
	}

	Node * buffer = head_node;

	while (buffer->pointer != _node) {
		buffer = buffer->pointer;
	}

	return buffer;
}

//! insertNode() method
Node * List::insertNode(char _value, Node * _node = nullptr) {
	// Creating c-style vector, final type would be 'std::unique_ptr'
	auto element = std::make_unique<Node>();
	element->field = _value;

	node_count++;

	// Add first node case
	if (_node == nullptr) {
		if (head_node == nullptr) {
			element->pointer = nullptr;
			head_node = element.release();
		}
		else {
			element->pointer = head_node;
			head_node = element.release();
		}
		return element.release();
	}

	// Add next node case
	else {
		element->pointer = _node->pointer;
		_node->pointer = element.release();
		return element.release();
	}
}

//! deleteNode() method
Node * List::deleteNode(Node * _node) {
	if (_node == nullptr) {
		return nullptr;
	}

	node_count--;

	if (_node == head_node) {
		head_node = _node->pointer;
		return head_node;
	}

	Node * interim = getPreviousNode(_node);
	interim->pointer = _node->pointer;
	return interim;
}

//! getNextNode() method
Node * List::getNextNode(Node * node) {
	if (listIsEmpty()) {
		return nullptr;
	}

	return node->pointer;
}

//! printList() method
void List::printList() {
	if (listIsEmpty()) {
		LOG(INFO) << "printList() : The list is empty";
		return;
	}

	Node * buffer = head_node;
	LOG(INFO) << "printList() : Printing current list:";

	do {
		std::cout << getNodeValue(buffer) << " ";
		buffer = getNextNode(buffer);
	} while (buffer != nullptr);

	std::cout << std::endl;
}

//! getNodeByKey() method
Node * List::getNodeByKey(char _key) {
	if (listIsEmpty()) {
		LOG(INFO) << "getNodeByKey() : The list is empty";
		return nullptr;
	}

	Node * buffer = head_node;

	while (buffer != nullptr) {
		if (buffer->field == _key) {
			LOG(INFO) << "getNodeByKey() : Found an element equal to " << _key;
			return buffer;
		}
		buffer = getNextNode(buffer);
	}

	LOG(INFO) << "getNodeByKey() : There was no element equal to " << _key;
	return nullptr;
}

//! clearList() Method
// This method is the same as destructor
void List::clearList() {
	class Node * buffer = head_node;

	if (buffer == nullptr) {
		return;
	}

	while (buffer != nullptr) {
		Node * local = buffer;
		buffer = getNextNode(buffer);
		local->pointer = nullptr;
		local->field = 0;
	}

	node_count = 0;
	head_node = nullptr;

	LOG(INFO) << "clearList() : List succesfully deleted";
}

//
// ────────────────────────────────────────────────────────────────────────────────── II ──────────
//   :::::: C O R E   F U N C T I O N   S E C T I O N : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────────────────
//

void runBeta_2_2() {
	std::string user_input;

	std::cout << "Input chars (without spaces): "; std::cin >> user_input;

	auto * chars_in_list = new unsigned[CHAR_MAX];
	std::fill_n(chars_in_list, CHAR_MAX, 0);

	List user_chars;
	List repetetive_chars;

	// Filling the list with data from 'user_input'
	for (unsigned i{}; i < user_input.length(); i++) {
		user_chars.insertNode(user_input[i]);
		chars_in_list[user_input[i]]++;
	}

	user_chars.printList();

	// Checking if the element was mentioned more than once
	for (unsigned i{}; i < CHAR_MAX; i++) {
		if (chars_in_list[i] > 1) {
			repetetive_chars.insertNode(char(i));
		}
	}

	// There we are testing assigment operator before 'repetetive_chars'
	// is printed, because 'List' is not following Zero-rule and destructor is used
	List test_assigment_operator = repetetive_chars;
	test_assigment_operator.printList();

	repetetive_chars.printList();
}