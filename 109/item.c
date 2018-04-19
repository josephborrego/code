#ifndef ITEM_C
#define ITEM_C

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"item.h"


struct Item* constructItem()
{
	struct Item *retval = (struct Item *)malloc(1 * sizeof(struct Item));
	retval->name = NULL;
	retval->value = 0;
	retval->weight = 0.0;
	return retval;

//	return explicitItem(NULL, 0, 0.0);
}

struct Item* copyItem(struct Item *source)
{

//	struct Item *retval = constructItem();
//	setValue(retval, getValue(source));
//	setWeight(retval, getWeight(source));
//	setName(retval, getName(source));
//	return retval;


	struct Item *retval = (struct Item *)malloc(1 * sizeof(struct Item));
	retval->value = source->value;
	retval->weight = source->weight;
	if(source->name == NULL)
	{
		retval->name = NULL;
	}
	else
	{
		retval->name = (char *)malloc((strlen(source->name)+1) * sizeof(char));
		strcpy(retval->name, source->name);
	}
//	return retval;
//*/
	return explicitItem(source->name, source->value, source->weight);
}


struct Item* explicitItem(char *name, int value, double weight)
{
	struct Item *retval = (struct Item *)malloc(1 * sizeof(struct Item));
	retval->value = value;
	retval->weight = weight;
	if(name == NULL)
	{
		retval->name = NULL;
	}
	else
	{
		retval->name = (char *)malloc((strlen(name)+1) * sizeof(char));
		strcpy(retval->name, name);
	}
	return retval;
}


struct Item* shallowItem(struct Item *source)
{
	struct Item *retval = (struct Item *)malloc(1 * sizeof(struct Item));
	memcpy(retval, source, sizeof(struct Item));
	return retval;
}

struct Item* destructItem(struct Item *toDestroy)
{
	if(toDestroy == NULL)
	{
		return NULL;
	}
	if(toDestroy->name != NULL)
	{
		free(toDestroy->name);
	}

	free(toDestroy);
	return NULL;
}

int getValue(struct Item* it)
{
	return it->value;
}

double getWeight(struct Item* it)
{
	return it->weight;
}

char* getName(struct Item* it)
{
	return it->name;
}

int setValue(struct Item* it, int update)
{
	it->value = update;
	return it->value;
}

double setWeight(struct Item* it, double update)
{
	return it->weight = update;
}

char* setName(struct Item* it, char *update)
{
	free(it->name);

	if(update == NULL)
	{
		it->name = NULL;
		return NULL;
	}

//	void *temp = malloc(10);

	char *newSpace = (char *)malloc((strlen(update)+1) * sizeof(char));
	strcpy(newSpace, update);

	it->name = newSpace;
//	free(temp);
	return it->name;
}

void printItem(struct Item* it, FILE *output)
{
	//Prints as: Item: <name> with value <value> and weight <weight>.
	fprintf(output, "Item: %s with value %d and weight %8.2f.\n", getName(it), getValue(it), getWeight(it));
}

void printPointers(struct Item* it, FILE *output)
{
	fprintf(stdout, "Location of name     : %p\n", &it->name);
	fprintf(stdout, "Location of value    : %p\n", &it->value);
	fprintf(stdout, "Location of weight   : %p\n", &it->weight);
	fprintf(stdout, "Name points to       : %p\n", it->name);
}

struct Item* plusEqual(struct Item* first, struct Item* second)
{
	//if(first == NULL)
	if(!first)
	{
		return second;
	}
	if(!second)
	{
		return first;
	}

	first->value += second->value;
	first->weight += second->weight;

	int length = strlen(first->name);
	length += strlen(second->name);
	length++;

	char *temp = (char *)malloc(length * sizeof(char));
	for(int i=0; i<length; i++)
	{
		temp[i] = '\0';
	}
	strcpy(temp, first->name);
	strcat(temp, second->name);
	free(first->name);
	//first->name = NULL;
	first->name = temp;
//	strcat(first->name, second->name);


	return first;
}

#endif
