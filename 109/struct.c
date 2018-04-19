#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"item.c"
#include"item.h"

int main(int argc, char **argv)
{
	//Default NULL declaration for an object
	//struct Item *myItem = NULL;

	//Replicate the behavior of new:
	//struct Item *myItem = new struct Item();
	//myItem = (struct Item *)malloc(1 * sizeof(struct Item));
	//myItem = constructItem();
	struct Item *myItem = constructItem();

	fprintf(stdout, "Enter in an item name: ");
	fscanf(stdin, "%ms", &(myItem->name));
	fprintf(stdout, "The name you entered is: %s\n", myItem->name);

	struct Item *temp = myItem;
	fprintf(stdout, "The name you entered is: %s\n", temp->name);
	myItem = destructItem(myItem);
	//fprintf(stdout, "The name you entered is: %s\n", temp->name);
	//temp = NULL;		//temp is still pointing to the deallocated myItem

	myItem = constructItem();
	printItem(myItem, stdout);
	setWeight(myItem, 9.4);
	printItem(myItem, stdout);
	setValue(myItem, 30);
	printItem(myItem, stdout);

	char *word = (char *)malloc(10 * sizeof(char));
	strcpy(word, "Tomato");
	setName(myItem, word);
	free(word);

	printItem(myItem, stdout);
//	temp = myItem;
//	myItem = destructItem(myItem);
//	char *buffer = (char *)malloc(5 * sizeof(char));
//	strcpy(buffer, "donu");
//	printItem(temp, stdout);

	fprintf(stdout, "Structure is at %p\n", myItem);
	fprintf(stdout, "Value     is at %p\n", &myItem->value);
	fprintf(stdout, "Weight    is at %p\n", &myItem->weight);
	fprintf(stdout, "Name      is at %p\n", myItem->name);
	fprintf(stdout, "Name&     is at %p\n", &myItem->name);

	int testNumber = getValue(myItem);
	fprintf(stdout, "AccValue  is at %p\n", &testNumber);

	/*
		Item x = new Item();
		Item y = new Item(x);
		Item z = new Item("Apple", 10, 10.5);
	*/
	struct Item *newItem = copyItem(myItem);
	printItem(newItem, stdout);
//	newItem = copyItem(newItem);
//	printItem(newItem, stdout);
	struct Item *shallowCopy = shallowItem(newItem);
	fprintf(stdout, "Printing newItem and then the shallow copy\n");
	printItem(newItem, stdout);
	printItem(shallowCopy, stdout);

	printPointers(newItem, stdout);
	printPointers(shallowCopy, stdout);

	word = (char *)malloc(30 * sizeof(char));
	strcpy(word, "applesbananacarrotdonut");
	fprintf(stdout, "Changing newItem's name to %s\n", word);
	setName(newItem, word);
	free(word);

	printPointers(newItem, stdout);
	printPointers(shallowCopy, stdout);

	newItem->name[3] = 'q';

	fprintf(stdout, "Aftering changing one string, not both\n");
	printItem(newItem, stdout);
	printItem(shallowCopy, stdout);

	fprintf(stdout, "After using a void* to mess with newItem\n");
	void *something = (void *)newItem;
	int *number = ((int *)something) + 2;
	*number = 70;
	printItem(newItem, stdout);
	number += 3;
	*number = 0xFFEE5566;
	fprintf(stdout, "We put in %d %x into a double.\n", *number, *number);
	printItem(newItem, stdout);


	word = (char *)malloc(30 * sizeof(char));
    strcpy(word, "apple");

	struct Item *first = explicitItem(word, 30, 10.4);
	strcpy(word, "banana");
	struct Item *second = explicitItem(word, 50, 8.6);
	free(word);

	printItem(first, stdout);
	printItem(second, stdout);
	fprintf(stdout, "Let's plusEqual our items\n");
	first = plusEqual(first, second);
	printItem(first, stdout);
	first = plusEqual(first, second);
	printItem(first, stdout);

	first = plusEqual(first, first);
	printItem(first, stdout);



	myItem = destructItem(myItem);
	return 0;
}

