/*
Project Description: Program to create a binary search tree. User can add, remove, print and search. 
					 Numbers can be inputted from a text file or through console.
Name: Aammya Sapra
Date: 05-13-2021
*/

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Node.h"

using namespace std;


//function prototypes
void add_node(Node* root, int num);
Node* remove_node(Node* root, int num);
Node* smallest(Node* root);
void search(Node* root, int num);
void display_tree(Node* root, int num_spaces);



//--------------------------------------------------MAIN FUNCTION-------------------------------------------------

int main() {

	//print out input options
	string input_option;
	cout << "BINARY SEARCH TREE" << endl;
	cout << "To input numbers from a text file, type \'F\'." << endl;
	cout << "To input numbers in the console, type \'C\'." << endl;
	cin >> input_option;
	cin.get();


	int num_numbers = 0; //number of input numbers
	int* array = new int[1000]; //array to hold input numbers


	//numbers inputted in the console (manually)
	if (input_option == "C" || input_option == "c") {
		cout << "Enter numbers 1-999. Seperate each with a space." << endl;
		char* input = new char[500];
		cin.getline(input, 500);
		char* number = strtok(input, " "); //break input into a series of tokens using the delimiter " "
		while (number != NULL) { //walk through the tokens
			array[num_numbers] = atoi(number);
			number = strtok(NULL, " ");
			num_numbers++;
		}
	}

	//file input
	else if (input_option == "F" || input_option == "f") {
		cout << "Enter file name. Current input files stored: \'input_numbers.txt\'" << endl;
		char file_name[50];
		cin.getline(file_name, 50, '\n');

		FILE* pfile = NULL; //file pointer
		pfile = fopen(file_name, "r");
		if (pfile == NULL) {
			cout << "Error x_x. File may not exist or permissions may not be granted. Please check that file name was inputted correctly." << endl;
			return 0;
		}

		//store input numbers into array[]
		int arr_index = 0;
		char file_line[5000];
		while (fgets(file_line, 500, pfile)) {
			char* buffer = new char[20];
			memset(buffer, '\0', 20);
			int pos = 0;
			while (buffer != NULL) {
				buffer = strchr(file_line + pos, ' ');
				if (buffer != NULL) {
					char line_buffer[20];
					memset(line_buffer, '\0', 20);
					strncpy(line_buffer, file_line + pos, sizeof(file_line - buffer));
					array[arr_index++] = stoi(line_buffer);
					num_numbers++;
					pos = (buffer - file_line) + 1;
				}
			}
		}
		fclose(pfile);

	}

	//invalid input option entered
	else {
		cout << "Invalid input option entered. Input options are \'F\' and \'C\'." << endl;
		return 0;
	}



	Node* root = new Node();
	for (int i = 0; i < num_numbers; i++) {
		add_node(root, array[i]);
	}





	//print out instructions
	cout << '\n' << "To display tree, branching out towards the right, type \'DISPLAY\'." << endl;
	cout << "To add a number, type \'ADD\'." << endl;
	cout << "To remove a number, type \'REMOVE\'." << endl;
	cout << "To search if a number exists in the tree, type \'SEARCH\'." << endl;
	cout << "To quit type \'QUIT\'." << endl << endl;

	bool inputting = true;
	char command[10];  //stores the command (ADD, DISPLAY, DELETE, QUIT) inputted by the user



	while (inputting) {
		cin >> command;

		//ADD NEW STUDENT(S)------------------------------------
		if (strcmp(command, "ADD") == 0) {
			int n;
			cout << "Enter number to add: ";
			cin >> n;
			cin.get();
			add_node(root, n); 
			cout << "Finished adding." << endl;
			cout << "\nEnter \'DISPLAY\', \'ADD\', \'REMOVE\', \'SEARCH\' to continue or \'QUIT\' to exit." << endl << endl;
		} 

		//DISPLAY TREE-------------------------------------
		else if (strcmp(command, "DISPLAY") == 0) {
			display_tree(root, 0);
			cout << "\nEnter \'DISPLAY\', \'ADD\', \'REMOVE\', \'SEARCH\' to continue or \'QUIT\' to exit." << endl << endl;
		}

		//REMOVE--------------------------------------
		else if (strcmp(command, "REMOVE") == 0) {
			int n;
			cout << "Enter number to delete: ";
			cin >> n;
			cin.get();
			if (root->getLeft() == NULL && root->getRight() == NULL) {
				root->setData(0);
			}
			else {
				root = remove_node(root, n);
			}
			cout << "Finished removing." << endl;
			cout << "\nEnter \'DISPLAY\', \'ADD\', \'REMOVE\', \'SEARCH\' to continue or \'QUIT\' to exit." << endl << endl;
		}

		//SEARCH--------------------------------------
		else if (strcmp(command, "SEARCH") == 0) {
			int n;
			cout << "Enter number to search: ";
			cin >> n;
			cin.get();
			search(root, n);
			cout << "\nEnter \'DISPLAY\', \'ADD\', \'REMOVE\', \'SEARCH\' to continue or \'QUIT\' to exit." << endl << endl;
		}

		//QUIT------------------------------------------------
		else if (strcmp(command, "QUIT") == 0) {
			inputting = false;
			break;
		}

		//INVALID INPUT---------------------------------------
		else { //prompt user to re-enter command if something invalid was entered
			cout << "\nPlease enter either \'DISPLAY\', \'ADD\', \'REMOVE\', \'SEARCH\', or \'QUIT\'." << endl;
		}
	} //end of while loop 



	return 0;
}



//--------------------------------------------------------FUNCTIONS------------------------------------------------------------



//function to add node to tree
void add_node(Node* root, int num) {
	if (root->getData() == 0) {
		root->setData(num);
		return;
	}
	else if (root->getData() > num) {
		if(root->getLeft() != 0) {
			add_node(root->getLeft(), num);
		}
		else {
			Node* newNode = new Node();
			newNode->setData(num);
			root->setLeft(newNode);
			return;
		}
	}
	else if (root->getData() < num) {
		if (root->getRight() != 0) {
			add_node(root->getRight(), num);
		}
		else {
			Node* newNode = new Node();
			newNode->setData(num);
			root->setRight(newNode);
			return;
		}
	}
	return;
}



//function to remove node from tree
Node* remove_node(Node* root, int num) {
	if (root->getData() > num) {
		root->setLeft(remove_node(root->getLeft(), num));
	}
	else if (root->getData() < num) {
		root->setRight(remove_node(root->getRight(), num));
	}
	else {
		if (root->getLeft() == NULL) {
			Node* temp = root->getRight();
			delete root;
			return temp;
		}
		else if (root->getRight() == NULL) {
			Node* temp = root->getLeft();
			delete root;
			return temp;
		}
		Node* temp = smallest(root->getRight());
		root->setData(temp->getData());
		root->setRight(remove_node(root->getRight(), temp->getData()));
	}

}


//function to find smallest 
Node* smallest(Node* root) {
	Node* current = root;
	while (current->getLeft() != NULL) {
		current = current->getLeft();
	}
	return current;
}




//function to search tree for given number
void search(Node* root, int num) {
	if (root == NULL) {
		cout << "Tree empty." << endl;
		return;
	}

	if (root != NULL) {
		if (root->getData() > num) {
			search(root->getLeft(), num);
		}
		else if (root->getData() < num) {
			search(root->getRight(), num);
		}
		else if (root->getData() == num) {
			cout << num << " exists in tree." << endl;
			return;
		}
	}

	return;
}




//function to print tree (root on left, branches out towards the right)
void display_tree(Node* root, int num_spaces) {

	if (root != NULL) {
		num_spaces = num_spaces + 10;
		display_tree(root->getRight(), num_spaces);
		cout << endl;

		for (int i = 0; i < num_spaces; i++) {
			cout << " ";
		}
		cout << root->getData() << endl;
		display_tree(root->getLeft(), num_spaces);
	}

	return;
}
