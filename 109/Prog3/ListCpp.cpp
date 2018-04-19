
#ifndef LISTCPP_H
#define LISTCPP_H
#include"ListCpp.h"

Node::Node()
: value(0), next(NULL) // an initializer list
{
	this->value = 0;
	next = NULL;
	size = 1;
}//colon colon is the scoping operator

Node::Node(int value)
: value(value), next(NULL) // an initializer list
{
    this->value = value;
    next = NULL;
    size = value;
}

Node::~Node()
{
	free(next);
}

size_t Node::size() // the object is the implicit argument
{
	return size;
}
	//size_t size(Node *this);
	Node *insert(int toInsert);
	bool find(int toFind);
	int traverse(char *buffer);
	Node *removeItem(int toRemove);
	char *traverse2();

	//private:
	//	int value;
	//	Node *next;

#endif
