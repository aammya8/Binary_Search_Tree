//Node cpp file

#include <cstdlib>
#include "Node.h"


//constructor
Node::Node() {
	left = NULL;
	right = NULL;
	data = 0;
}

/*
//destructor
Node::~Node() {
	delete left;
	delete right;
}
*/



//return left
Node* Node::getLeft() {
	return left;
}

//return right
Node* Node::getRight() {
	return right;
} 

//return data
int Node::getData() {
	return data;
} 




//set left
void Node::setLeft(Node* n) {
	left = n;
}

//set right
void Node::setRight(Node* n) {
	right = n;
}

//set data
void Node::setData(int d) {
	data = d;
}

