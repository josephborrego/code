#ifndef NODE_CPP
#define NODE_CPP

#include"Node.h"

template <typename T>
Node<T>::Node()
{
	//data = T();
	next = NULL;
}

template <typename T>

Node<T>::Node(T data, Node<T>* next)
: data(data), next(next)
()

template <typename T>
Node<T>::~Node() //destructor
{}

template <typename T>
Node<T>::Node(const Node<T> &source)
: data (source
