/*
CSE 109: Spring 2017
<Joseph Borrego>
<job218>
<Linked List>
Program #5
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "List.h"

	struct Node* constructList(int newVal)
	{
		struct Node* newNode = (struct Node*)malloc(1000);//sizeof(struct Node));
		//newNode's value is going to be set equal to newVal
		newNode->val = newVal;
		newNode->nextNode = NULL; //so when looping to check for null*****
		//returning the pointer to the node
		return newNode;
		//returning a seg fault, because the memory is going out of scope when the fucntion ends
	}


	//fix this
	struct Node* destroyList(struct Node* oldNode)
	{
		if (oldNode == NULL)
		{
			 return NULL; // added this
		}
		Node* nextNode = oldNode->nextNode;
		free(oldNode);
		oldNode = NULL;
		return destroyList(nextNode);
	}


	//counting how many are in the linked list
	size_t size(struct Node* firstNode)
	{
		if(firstNode == NULL)
		{
			return 0;
		}
		int count = 1;
		struct Node* currentNode = firstNode;
		//keep looping until it hits the end of the linked list
		while(currentNode->nextNode != NULL)
		{
			count++;
			currentNode =  currentNode->nextNode;
		}
		return count;
	}

	struct Node* insert(struct Node* firstNode, int newVal)
	{
		if(firstNode == NULL)
		{
			struct Node* firstNode = (struct Node*)malloc(sizeof(struct Node));
			firstNode->val = newVal;
			firstNode->nextNode = NULL;
			return firstNode;
		}
		struct Node* currentNode = firstNode;
		while(currentNode->nextNode != NULL)
		{
			currentNode = currentNode->nextNode;
		}
		currentNode->nextNode = (struct Node*)malloc(sizeof(struct Node));
		//giving the new node the new value
		currentNode->nextNode->val = newVal;
		currentNode->nextNode->nextNode = NULL;
		return firstNode;
	}


	int find(struct Node * firstNode, int searchNum)
	{
		if(firstNode == NULL)
		{
			return 0;
		}
		struct Node* currentNode = firstNode;
		while(currentNode->nextNode != NULL)
		{
			if(currentNode->val == searchNum)
			{
				return 1;
			}
			currentNode = currentNode->nextNode;
		}
	//we're at the very end check to see if the last node is the value we're looking
	//for
		if(currentNode->val == searchNum)
		{
			return 1;
		}
		return 0;
	}


	int traverse(struct Node* firstNode, char* outString)
	{
		if(firstNode == NULL)
		{
			strcpy(outString, "");
			return 0;
		}
		strcpy(outString,"");
		struct Node* currentNode = firstNode;
		while(currentNode->nextNode != NULL)
		{
			char str[10];
			sprintf(str, "%d", (currentNode->val));
			strcat(outString, str);
			strcat(outString, ", ");
			currentNode = currentNode->nextNode;
		}
		char str[10];
		sprintf(str, "%d", (currentNode->val));
		strcat(outString, str);
		return 1;
	}

	struct Node* removeItem(struct Node* firstNode, int num)
	{
		if(firstNode == NULL)
		{
			return NULL;
		}
		struct Node* startNode = firstNode;
		struct Node* currentNode = firstNode;
		struct Node* savedNode = firstNode;
		struct Node* tempNode;
		while(currentNode->nextNode != NULL)
		{
			if(currentNode->val == num)
			{
				//temp node = next one
				tempNode = currentNode->nextNode;
				if(currentNode == startNode)
				{
					startNode = currentNode->nextNode;
				}
				if(currentNode == savedNode)
            	{
					savedNode = currentNode->nextNode;
           	 	}
				//free the current one
				free(currentNode);
				//step to the next node
				currentNode = tempNode;
			}
			else
				{
					if(savedNode != currentNode)
					{
						savedNode->nextNode = currentNode;
						savedNode = currentNode;
					}
					currentNode = currentNode->nextNode;
					//savedNode = currentNode;
				}
		}

		if(currentNode->val == num)
		{
			savedNode->nextNode = NULL;
			if(currentNode == startNode)
			{
				startNode = NULL;
			}
			free(currentNode);
		}
		else{
			if(savedNode != NULL){
				if (savedNode != currentNode){
					savedNode->nextNode = currentNode;
				}
				else{
					savedNode->nextNode = NULL;
				}
			}
		}
		return startNode;
	}


	char* traverse2(struct Node* firstNode)
	{
		if(firstNode == NULL)
		{
			return NULL;
		}
		if(size(firstNode) == 0)
        {
			char* word = (char*)malloc(2*sizeof(char));
			strcpy(word, "");
            return word;
        }
		//the string is #, space and -1 for the last number (null)
		size_t outputSize = 4*size(firstNode) - 1; //***output size needed to account for two digit numbers
		char* outputString = (char*)malloc(sizeof(char) * outputSize);
		traverse(firstNode, outputString);
		return outputString;
	}

