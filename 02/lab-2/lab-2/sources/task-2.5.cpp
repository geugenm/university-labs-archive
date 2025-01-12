/*
 * Declare a template of the "Binary Tree" class. Define the structure of the class
 * and its methods. The class must have a default constructor, a constructor with
 * formal parameters, a copy constructor and a destructor.
 *
 * Define the methods:
 *
 *  - initializing the first element of the structure
 *  - writing a new element to the structure
 *  - deleting an element (sheet)
 *  - searching for an element by a specified search key
 *  - displaying tree elements on the screen
 *  - deleting all tree elements.
 */

#include "headers/config.h"

#include <easylogging++.h>

#define get_object_name(x) #x


 //
 // ──────────────────────────────────────────────────────────────────────────────────────────────────────── I ──────────
 //   :::::: C L A S S   D E F I N I T I O N   A N D   S U P P L I A N C E S : :  :   :    :     :        :          :
 // ──────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 //

const unsigned char DEAFULT_CONSOLE_COLOR = 7;

struct Node {
	int value{};
	Node * LeftBranch = nullptr;
	Node * RightBranch = nullptr;
};

class BinaryTree {
private:
	Node * root = nullptr;

	std::string object_name = "<object_name>";

	void removeBackend(int _value);
	void copyBackend(const Node * _node);
	void clearBackend(Node * _leaf) const;

	void insertBackend(int _target, Node * _leaf) const;
	void leavesNumberBackend(Node * aBranch, unsigned & _counter);
	void showBackend(const std::string & _prefix, Node * _node, bool _isLeft);


	Node * minValueNode(Node * _node);
	Node * searchBackend(int _value, Node * _leaf, bool & _isExist);

public:
	BinaryTree() = default;
	explicit BinaryTree([[maybe_unused]] int _element) {};
	~BinaryTree() = default;


	void show();
	void clear();


	void remove(int key);
	void insert(int _value);
	bool search(int _value);

	void copy(BinaryTree _sample);
	void setName(std::string _name);

	unsigned leavesNumber();
};


//
// ─── METHODS BACKEND DEFINITION ─────────────────────────────────────────────────
//

void BinaryTree::clearBackend(Node * _leaf) const {
	if (_leaf != nullptr) {
		clearBackend(_leaf->LeftBranch);
		clearBackend(_leaf->RightBranch);

		_leaf->LeftBranch = nullptr;
		_leaf->RightBranch = nullptr;
		_leaf->value = 0;
	}
}

void BinaryTree::insertBackend(int _value, Node * _leaf) const {
	if (_value < _leaf->value) {
		if (_leaf->LeftBranch != nullptr) {
			insertBackend(_value, _leaf->LeftBranch);
		}
		else {
			_leaf->LeftBranch = std::make_unique<Node>().release();
			_leaf->LeftBranch->value = _value;
			_leaf->LeftBranch->LeftBranch = nullptr;
			_leaf->LeftBranch->RightBranch = nullptr;
		}
	}
	else if (_value >= _leaf->value) {
		if (_leaf->RightBranch != nullptr) {
			insertBackend(_value, _leaf->RightBranch);
		}
		else {
			_leaf->RightBranch = std::make_unique<Node>().release();
			_leaf->RightBranch->value = _value;
			_leaf->RightBranch->LeftBranch = nullptr;
			_leaf->RightBranch->RightBranch = nullptr;
		}
	}
}

void BinaryTree::showBackend(const std::string & _prefix, Node * _node, bool _isLeft) {
	if (_node != nullptr) {
		std::cout << _prefix;

		std::cout << (_isLeft ? "|--" : "^--");

		std::cout << _node->value << std::endl;

		showBackend(_prefix + (_isLeft ? "|   " : "    "), _node->LeftBranch, true);
		showBackend(_prefix + (_isLeft ? "|   " : "    "), _node->RightBranch, false);
	}
}

void BinaryTree::removeBackend(int _value) {
	// https://www.techiedelight.com/deletion-from-bst/

	Node * parent = nullptr;
	Node * current = root;

	while (current != nullptr && current->value != _value) {
		parent = current;

		if (_value < current->value) {
			current = current->LeftBranch;
		}
		else {
			current = current->RightBranch;
		}
	}

	if (current != nullptr) {
		// Case 1: node to be deleted has no children
		if (current->LeftBranch == nullptr && current->RightBranch == nullptr) {
			if (current != root) {
				if (parent->LeftBranch == current) {
					parent->LeftBranch = nullptr;
				}
				else {
					parent->RightBranch = nullptr;
				}
			}

			else {
				root->value = NULL;
				root = nullptr;
			}
		}

		// Case 2: node to be deleted has two children
		else if (current->LeftBranch && current->RightBranch) {
			const Node * successor = minValueNode(current->RightBranch);

			const int successor_value = successor->value;

			// The successor will have at most one child (right child)
			removeBackend(successor->value);

			current->value = successor_value;
		}

		// Case 3: node to be deleted has only one child
		else {
			Node * child = (current->LeftBranch) ? current->LeftBranch : current->RightBranch;

			if (current != root) {
				if (current == parent->LeftBranch) {
					parent->LeftBranch = child;
				}
				else {
					parent->RightBranch = child;
				}
			}

			else {
				root = child;
			}
		}
	}

}

void BinaryTree::leavesNumberBackend(Node * aBranch, unsigned & _counter) {
	if (aBranch != nullptr) {
		leavesNumberBackend(aBranch->LeftBranch, _counter);
		if (aBranch->LeftBranch == nullptr && aBranch->RightBranch == nullptr) {
			_counter++;
		}
		leavesNumberBackend(aBranch->RightBranch, _counter);
	}
}

Node * BinaryTree::searchBackend(int _value, Node * _leaf, bool & _isExist) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (_leaf != nullptr) {
		if (_value == _leaf->value) {
			const unsigned char OUTPUT_COLOR = 11;
			SetConsoleTextAttribute(hConsole, OUTPUT_COLOR);

			LOG(INFO) << object_name << " | searchBackend() : Element '" << _value << "' is in the tree";
			SetConsoleTextAttribute(hConsole, DEAFULT_CONSOLE_COLOR);
			_isExist = true;
			return _leaf;
		}
		if (_value < _leaf->value) {
			return searchBackend(_value, _leaf->LeftBranch, _isExist);
		}
		else {
			return searchBackend(_value, _leaf->RightBranch, _isExist);
		}
	}
	else {
		const unsigned char OUTPUT_COLOR = 14;
		SetConsoleTextAttribute(hConsole, OUTPUT_COLOR);

		LOG(INFO) << object_name << " | searchBackend() : Element '" << _value << "' is not present in the tree";
		SetConsoleTextAttribute(hConsole, DEAFULT_CONSOLE_COLOR);
		_isExist = false;
		return nullptr;
	}
}

Node * BinaryTree::minValueNode(Node * _node) {

	while (_node->LeftBranch != nullptr) {
		_node = _node->LeftBranch;
	}

	return _node;

}

void BinaryTree::copyBackend(const Node * _node) {
	if (_node != nullptr) {
		insert(_node->value);

		copyBackend(_node->LeftBranch);
		copyBackend(_node->RightBranch);
	}
}

//
// ─── METHODS CALLERS DEFINITION ─────────────────────────────────────────────────
//

void BinaryTree::insert(int _value) {
	if (root != nullptr) {
		insertBackend(_value, root);
	}
	else {
		root = std::make_unique<Node>().release();
		root->value = _value;
		root->LeftBranch = nullptr;
		root->RightBranch = nullptr;
	}
}

bool BinaryTree::search(int _value) {
	if (root != nullptr) {
		bool isExist = false;
		searchBackend(_value, root, isExist);
		LOG(INFO) << object_name << " | search() : Search completed successfully";
		return isExist;
	}
	else {
		LOG(INFO) << object_name << " | search(): Tree is empty";
		return false;
	}
}

void BinaryTree::show() {
	LOG(INFO) << object_name << " | show(): Printing tree...";
	if (root != nullptr) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		const unsigned char OUTPUT_COLOR = 13;
		SetConsoleTextAttribute(hConsole, OUTPUT_COLOR);

		showBackend(" ", root, false);

		SetConsoleTextAttribute(hConsole, DEAFULT_CONSOLE_COLOR);
		LOG(INFO) << object_name << " | show(): Tree successfully printed";
	}
	else {
		LOG(INFO) << object_name << " | show(): Tree is empty";
	}
}

void BinaryTree::remove(int _target) {
	bool isExist = false;
	searchBackend(_target, root, isExist);

	if (isExist) {
		removeBackend(_target);
	}
	LOG(INFO) << object_name << " | remove() : Element " << _target << " successfully deleted";
}


unsigned BinaryTree::leavesNumber() {
	unsigned counter{};
	leavesNumberBackend(root, counter);
	return counter;
}

void BinaryTree::copy(BinaryTree _sample) {
	copyBackend(_sample.root);
	LOG(INFO) << object_name << " | copy() : Tree successfully copied";
}

void BinaryTree::clear() {
	clearBackend(root);
	LOG(INFO) << object_name << " | clear() : Tree successfully deleted";
}

void BinaryTree::setName(std::string _name) {
	object_name = _name;
}


//
// ──────────────────────────────────────────────────────────── II ──────────
//   :::::: U N I T   T E S T S : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────
//

void removeTest(BinaryTree _object) {
	int target;
	std::cout << "Input value to delete: ";
	std::cin >> target;

	_object.remove(target);
	_object.show();

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const unsigned char OUTPUT_COLOR = 10;
	SetConsoleTextAttribute(hConsole, OUTPUT_COLOR);
	LOG(INFO) << "removeTest passed";
	SetConsoleTextAttribute(hConsole, DEAFULT_CONSOLE_COLOR);
}

void searchTest(BinaryTree _object) {
	int target;
	std::cout << "Input searching value: ";
	std::cin >> target;
	_object.search(target);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const unsigned char OUTPUT_COLOR = 10;
	SetConsoleTextAttribute(hConsole, OUTPUT_COLOR);
	LOG(INFO) << "searchTest passed";
	SetConsoleTextAttribute(hConsole, DEAFULT_CONSOLE_COLOR);
}

void copyTest(BinaryTree _sample) {
	BinaryTree Copy;
	Copy.setName(get_object_name(Copy));
	Copy.copy(_sample);
	Copy.show();

	Copy.clear();

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const unsigned char OUTPUT_COLOR = 10;
	SetConsoleTextAttribute(hConsole, OUTPUT_COLOR);
	LOG(INFO) << "copyTest passed";
	SetConsoleTextAttribute(hConsole, DEAFULT_CONSOLE_COLOR);
}


//
// ────────────────────────────────────────────────────────────────── III ──────────
//   :::::: C O R E   F U N C T I O N : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────
//

void runBeta_2_5() {
	const int RANDOM_MIN = 0;
	const int RANDOM_MAX = 255;

	std::random_device random_number;
	std::mt19937 random_generator(random_number());
	std::uniform_int_distribution<int> distribution(RANDOM_MIN, RANDOM_MAX);

	BinaryTree task_tree;
	task_tree.setName(get_object_name(task_tree));
	unsigned int tree_elements_count;


	std::cout << "Determine the size of the binary tree: ";
	std::cin >> tree_elements_count;


	for (unsigned i{}; i < tree_elements_count; i++) {
		task_tree.insert(distribution(random_generator));
	}

	task_tree.show();


	std::cout << "There are " << task_tree.leavesNumber() << " leaves" << std::endl;

	copyTest(task_tree);

	removeTest(task_tree);

	searchTest(task_tree);
}
