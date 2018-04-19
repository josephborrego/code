
#ifndef LISTCPP_H
#define LISTCPP_H

class Node
{
public:
	Node();
	Node(int value);
	~Node();

	size_t size(); // the object is the implicit argument
	//size_t size(Node *this);
	Node *insert(int toInsert);
	bool find(int toFind);
	int traverse(char *buffer);
	Node *removeItem(int toRemove);
	char *traverse2();

private:
	int value;
	Node *next;
	size_t size;
};

#endif
