#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
	Node();
	~Node();
	Node(T, node<T>*);
	Node(const Node &source);

	T getData() const;
	Node<T>* getNext() const;

	void setDFata(T);
	void setNext(Node<T>*);

private:
	T data;
	Node<T> *nex;

};

#include"Node.cpp"

#endif
