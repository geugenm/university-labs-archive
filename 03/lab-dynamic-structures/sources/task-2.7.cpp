#include "../headers/config.h"


struct Branch {
	int element {};
	Branch * LeftBranch = nullptr;
	Branch * RightBranch = nullptr;
};


void addTreeMember(int _insert_element, Branch *& _branch) {
	if (!_branch) {
		_branch = new Branch;
		_branch->element = _insert_element;
		_branch->LeftBranch = 0;
		_branch->RightBranch = 0;
		return;
	}
	else
		if (_branch->element > _insert_element) {
			addTreeMember(_insert_element, _branch->LeftBranch);
		}
		else {
			addTreeMember(_insert_element, _branch->RightBranch);
		};
}

void printBinaryTree(const string & _prefix, Branch * _node, bool _isLeft) {
	if (_node != nullptr) {
		cout << _prefix;

		cout << (_isLeft ? "├──" : "└──");

		cout << _node->element << endl;

		// Entering the next tree level - left and right branch
		printBinaryTree(_prefix + (_isLeft ? "│   " : "    "), _node->LeftBranch, true);
		printBinaryTree(_prefix + (_isLeft ? "│   " : "    "), _node->RightBranch, false);
	}
}

void printBinaryTree(Branch * _node) {
	printBinaryTree("", _node, false);
}


void getLeavesNumber(Branch * aBranch, unsigned int & _counter) {
	if (aBranch != nullptr) {
		getLeavesNumber(aBranch->LeftBranch, _counter);
		if (aBranch->LeftBranch == nullptr && aBranch->RightBranch == nullptr) {
			_counter++;
			cout << aBranch->element << endl;
		}
		getLeavesNumber(aBranch->RightBranch, _counter);
	}
}

void clearTree(Branch * aBranch) {
	if (!aBranch) {
		return;
	}

	clearTree(aBranch->LeftBranch);
	clearTree(aBranch->RightBranch);

	delete aBranch;
	return;
}

void runBeta_2_7() {
	random_device random_number;
	mt19937 random_generator(random_number());
	uniform_int_distribution<int> distribution(0, 100);

	Branch * Root = 0;
	unsigned int tree_elements_count {}, leaves_count {};


	cout << "Determine the size of the binary tree: "; cin >> tree_elements_count; cout << endl;

	for (unsigned int i {}; i < tree_elements_count; i++) {
		addTreeMember(distribution(random_generator), Root);
	}


	cout << "\nBinary tree output:" << endl << endl;
	printBinaryTree(Root); cout << endl;

	cout << "Binary tree leaves:" << endl;
	getLeavesNumber(Root, leaves_count); cout << endl;
	cout << "Total leaves: " << leaves_count << endl;

	clearTree(Root);
}