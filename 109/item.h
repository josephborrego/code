#ifndef ITEM_H
#define ITEM_H
#include<stdio.h>
#include"item.c"

struct Item
{
	char *name;
	int value;
	double weight;
};

//Construction, Destruction
//Default (noarg) constructor
struct Item* constructItem();
//Copy constructor
struct Item* copyItem(struct Item *source);
//Explicit value constructor
struct Item* explicitItem(char *name, int value, double weight);
//Shallow copy constructor (Bad, don't do)
struct Item* shallowItem(struct Item *source);
struct Item* destructItem(struct Item *toDestroy);

//Accessors
int getValue(struct Item* it);
double getWeight(struct Item* it);
char* getName(struct Item* it);

//Mutators
int setValue(struct Item* it, int update);
double setWeight(struct Item* it, double update);
char* setName(struct Item* it, char *update);

//Output
void printItem(struct Item* it, FILE *output);
void printPointers(struct Item* it, FILE *output);

struct Item* plusEqual(struct Item* first, struct Item* second);

#endif

/*
	Item x = new Item();
	x.getValue();
	getValue(x);
*/
