#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

struct Node {
	int value;
	Node* left = NULL;
  Node* right = NULL;
  Node(int num) {
		value = num;
	}
};

void print(Node* root);
void add(Node *& root, int num);
bool search(Node * root, int num);

void removeLargest(Node *& root) {
	if (root->right == NULL) {
		//case 1: leaf case
		if (root->right == NULL && root->left == NULL) {
			root = NULL;
			delete root;
		}
		//case 2: left child case
		else if (root->left != NULL) {
			Node* todelete = root;
			root = root->left;
			delete todelete;
		}
	} else {
		removeLargest(root->right);
	}
}

int main() {
	Node* root = NULL;
	int input;
	int num;
	bool notdone = true;
	
	while (notdone) {
		cout << "Press 1 to add, 2 to print, 3 to search, 4 to remove largest" << endl;
		cin >> input;
		
		if (input == 1) {
			cout << "Enter number: " << endl;
			cin >> num;
			add(root, num);
		} else if (input == 2) {
			print(root);
		} else if (input == 3) {
			cout << "Enter number: " << endl;
			cin >> num;
			if (search(root, num)) {
				cout << "In the tree" << endl;
			} else {
				cout << "Not in the tree" << endl;
			}
		} else if (input == 4) {
			removeLargest(root);
		} else {
			notdone = false;
		}		
	}
	return 0;
}

void print(Node* root) {
	queue<Node*> queue;
	queue.push(root);
	bool moredata = true;
	
	while(moredata) {
		moredata = false;
		int levelsize = queue.size();
		int counter = 0;
		while(counter != levelsize) {
			Node* current = queue.front();
			queue.pop();
			counter++;
			if (current == NULL) {
				cout << "-,";
				queue.push(NULL);
				queue.push(NULL);
			} else {
				cout << current->value << ",";
				moredata = true;
				queue.push(current->left);
				queue.push(current->right);
			}		
		}
		cout << endl;
	}
}

void add(Node *& root, int num) {
	if (root == NULL) {
		root = new Node(num);
	} else if (root->value < num) {
		add(root->right, num);
	} else if (root->value > num) {
		add(root->left, num);
	}
}

bool search(Node* root, int num) {
	if (root == NULL) {
		return false;
	} else if (root->value == num) {
		return true;
	} else if (root->value < num) {
		return search(root->right, num);
	} else if (root->value > num) {
		return search(root->left, num);
	}
}