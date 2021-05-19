//Node header file

//include guards
#ifndef NODE_H
#define NODE_H


class Node {

public:
	Node(); //constructor
	//~Node(); //destructor
	Node* getLeft(); //getter
	Node* getRight(); //getter
	int getData(); //getter
	void setLeft(Node* n); //setter
	void setRight(Node* n); //setter
	void setData(int d); //setter
private:
	Node* left;
	Node* right;
	int data;
};


#endif