#ifndef GENLIST_H_
#include<string>
#include<iostream>
#include"Node.h"

using namespace std;
template<typename T>
class genList
{
public:
	genList();
	genList(const genLIst &source);
	genList(const genList *source);

	~genList();

	bool insert(T data);
	bool remove(T data);
	bool find(T data) const;
	bool clear;

	string toString const;
	genList& operator = (const genList &source);

private:

	size_t size;
	Node<T> *head;
};
/*
genList<int> x;
cout<< x;
cout << &x;
genList<int> *y = &x;
genList<int> y = x;
genList<int> y(x);
y= x;*/

template<typename T>
ostream & operator<<(ostream & out, const genList<T> &rhs)
{
	out << rhs.toString();
	return out;
}
template<typename T>
ostream & operator<<(ostream & out, const genList<T> *rhs)

{

}
