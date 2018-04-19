
/*
CSE 109: Spring 2017
<Joseph Borrego>
<job218>
<Memory Allocate>
Program #4
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Alloc.h"

// if you create a node with 9 bytes, there should be one node with 16 bytes
// if user ask for 33, need to round to 40
// round up to 8 byte case, each node should be 8 bytes
// if they want to allocate 20 then round to 24
// if they want to allocate, just round up to 8
// not doing any rounding
// in construct alloc rounded up to 8
// in allocate need to round up to 8
// figure out why , somewhere i'm setting oldNode->stored equals 16

	int roundWord(int number)
	{
		//if num is divisble by 8
		if(number % 8 == 0)
		{
			return number;
		}
		else
		{
			int x = number % 8;
			int y = 8 - x;
			int z = number + y;
			return z;
		}
	}
	//creates an alloc object with the desired size and returns to user
	struct Alloc* constructAlloc(int size)
	{
		if(size < 0)
		{
			return NULL;
		}
		size = roundWord(size);
		//round size up to word size
//		 printf("start malloc alloc  ");
		struct Alloc* newAlloc = (struct Alloc*)malloc(sizeof(struct Alloc));
//		 printf("  end of malloc alloc\n ");
		if(newAlloc == NULL)
		{
			return NULL;
		}
		// created a new alloc struct and malloce for whatever size you specified 
		//  a pointer to memory
//		 printf("start malloc memory ");
		newAlloc->memory = (void *)malloc(size);
//		 printf("  end malloc memory\n  ");
//		printf(" malloc for firstNode   ");
		newAlloc->firstNode = (struct Node*)malloc(sizeof(struct Node));
//		printf(" malloc for firstNode work? \n   ");
		newAlloc->firstNode->nextNode = NULL;
		newAlloc->firstNode->memLocation = newAlloc->memory;
		newAlloc->firstNode->stored = size;
//		printf("in construct alloc firstNode stored is %d\n", newAlloc->firstNode->stored);
		newAlloc->firstNode->isUsed = 0;
		newAlloc->capacity = size;
		return newAlloc;
	}

	//destroys the alloc object that is given to it
	struct Node* destroyList(struct Node* oldNode)
	{
		if (oldNode == NULL)
		{
		//	printf("returning NULL\n");
			return NULL; // added this
		}
		destroyList(oldNode->nextNode);
		//Node* nextNode = oldNode->nextNode;
//		printf("Freeing %d node\n", oldNode->stored);
		//if (oldNode != NULL)
		free(oldNode);
		oldNode = NULL;
//		printf("returning next\n");
		return NULL;//destroyList(nextNode);
	}

	//destroys the alloc that is given to it
	struct Alloc* destructAlloc(struct Alloc* oldAlloc)
	{
		if(oldAlloc == NULL)
		{
			return NULL;
		}
//		printf("destroying list......first node size is equal to %d\n", oldAlloc->firstNode->stored);
		destroyList(oldAlloc->firstNode);
//		free(oldAlloc->firstNode);
		oldAlloc->firstNode = NULL;
//		printf("freeing memory\n");
		free(oldAlloc->memory);
		oldAlloc->memory = NULL;
//		printf("freeing alloc\n");
		free(oldAlloc);
		oldAlloc = NULL;
		return NULL;
	}

	//the alloc object returns a pointer of size bytes
	void *allocate(struct Alloc* theAlloc, int size)
	{
		if(size == 0)
		{
			return NULL;
		}
		size = roundWord(size);
//		printf("does size work? %d\n", size);
		//it exisited?
		if(theAlloc == NULL)
		{
			return NULL;
		}
		//enough size?
		if(size > (theAlloc->capacity))
		{
			return NULL;
		}
		struct Node* currentNode = theAlloc->firstNode;
		while(currentNode != NULL)
		{
			if(currentNode->stored >= size && currentNode->isUsed == 0)
			{
				if(size == currentNode->stored)
				{
					currentNode->isUsed = 1;
					void* memAlloc = currentNode->memLocation;
					//void *memAlloc[size] = currentNode->memLocation;
					// how do we do a pointer of a certain size but does it
					// need to be an array of a certain size
					return memAlloc;
					//give them a pointer, and we round up to the next mulitple of 8 •••••••
					//give them
				}
				//do we have more capacity than what is being asked for
				else
				{
					struct Node* tempNode = currentNode->nextNode;
//					printf("start malloc node  ");
					currentNode->nextNode = (struct Node*)malloc(sizeof(struct Node));
//					printf(" end of malloc node\n");
					currentNode->nextNode->stored = currentNode->stored - size; //put some print state
//					printf("CURRENTNODE->NEXTNODE->STORED IS NOW %d \n", currentNode->nextNode->stored);
					currentNode->stored = size;
//					printf("currentNode->stored is now %d\n", currentNode->stored);
					currentNode->isUsed = 1;
					currentNode->nextNode->isUsed = 0;
					currentNode->nextNode->nextNode = tempNode;
//					printf("memloc1: %d - ",currentNode->memLocation);
					currentNode->nextNode->memLocation = (void*)((char*)currentNode->memLocation + size);
//					 printf("memloc2: %d\n",currentNode->nextNode->memLocation);
					void *memAlloc = currentNode->memLocation;
					// void *memAlloc[size] = currentNode->memLocation;
                    return memAlloc;
				}
			}
			currentNode = currentNode->nextNode;
		}
		return NULL;
	}

	//helper function used in deallocate
	void sendNodes(struct Node* firstNode, struct Node* secNode)
	{
		firstNode->nextNode = secNode->nextNode;
		secNode->nextNode = NULL;
//		printf("in send nodes, firstnode stored is %d\n", firstNode->stored);
		firstNode->stored = firstNode->stored + secNode->stored;
//		printf("revised in send nodes, firstnode stored is now %d\n", firstNode->stored);
		free(secNode);
	}

	//this returns data back to the alloc object
	void deallocate(struct Alloc* deAlloc, void *ptr)
	{
		if( ptr == NULL)
		{
			return;
		}
		struct Node* currentNode = deAlloc->firstNode;
		struct Node* previousNode = deAlloc->firstNode;
		while(currentNode != NULL)
		{
//			printf("looking for %d \n", ptr);
			if(currentNode->memLocation == ptr)
			{
//				printf("current node is now storing %d\n", currentNode->stored);
				break;
			}
			if(previousNode != currentNode)
			{
			//	printf("previous node is %d\n", previousNode->stored);
				previousNode = currentNode;
//				printf("in deallocate previous node is now %d\n", previousNode->stored);
			}
			currentNode = currentNode->nextNode;
		}
		if(currentNode == NULL)
		{
			fprintf(stderr, "corruption in free\n");
			exit(2);
		}
		if(previousNode->isUsed == 0)
		{
			currentNode->isUsed = 0;
//			printf("right before send Nodes, second node is now %d\n", currentNode->stored);
			sendNodes(previousNode, currentNode);
			if(previousNode->nextNode != NULL && previousNode->nextNode->isUsed == 0)
			{
				sendNodes(previousNode, previousNode->nextNode);
			}
		}
		else if(currentNode->nextNode != NULL && currentNode->nextNode->isUsed == 0)
		{
			currentNode->isUsed = 0;
			sendNodes(currentNode, currentNode->nextNode);
		}
	}

	//returns the maximum capacity of the alloc object
	int getCapacity(struct Alloc* allocCap)
	{
		//do if statement
		if(allocCap == NULL)
		{
			return 0;
		}
		return allocCap->capacity;
	}

	//returns the amount of data currently allocated by the Alloc Object
	int getSize(struct Alloc* theOtherAlloc)
	{
		if(theOtherAlloc == NULL)
		{
			return 0;
			//ask him about this
			//fixed this
		}
		int size = 0;
		struct Node* currentNode = theOtherAlloc->firstNode;
        while(currentNode != NULL)
        {
			if(currentNode->isUsed == 1)
			{
			size = size + currentNode->stored;
//			printf("in get size, size is now %d\n", size);
			}
			currentNode = currentNode->nextNode;
		}
		return size;
	}

	// returns a void * that is the base of the alloc object's data
	// namely memory
	void *getBase(struct Alloc* baseAlloc)
	{
		if(baseAlloc == NULL)
		{
			return NULL;
		}
		return baseAlloc->memory;
	}

	// returns an list of void*s that represent all of the
	// locations that the alloc object has given to users which has
	// given to users which has not yet been returned
	void **getAllocations(struct Alloc* getAlloc)
	{
		if(getAlloc == NULL)
		{
			return NULL;
		}

		struct Node* currentNode = getAlloc->firstNode;
		int total = 0;

		while(currentNode != NULL)
		{
			if(currentNode->isUsed == 1)
			{
				total++;
			}
			currentNode = currentNode->nextNode;
		}
//		printf(" malloc for retPointer   ");
		void** retPointer =(void**)malloc(total * sizeof(void *));
//		printf(" malloc for ret end \n   ");
		int currenLoc = 0;

		while(currentNode != NULL)
        {
            if(currentNode->isUsed == 1)
            {
                retPointer[currenLoc] = currentNode->memLocation;
				currenLoc++;
            }
            currentNode = currentNode->nextNode;
        }
		return retPointer;
	}

	// same as allocate except in the case that we don't have
	// enough memory available, use realloc to get more memory
	void *riskyAlloc(struct Alloc* riskAlloc, int size)
	{
		if(riskAlloc == NULL)
		{
			return NULL;
		}
		if(size == 0)
		{
			return NULL;
		}
		size = roundWord(size);
		void *var = allocate(riskAlloc, size);
		if(var == NULL)
		{
		struct Node* currentNode = riskAlloc->firstNode;
			while(currentNode->nextNode != NULL)
			{
				currentNode = currentNode->nextNode;
			}
		int newSize = size + riskAlloc->capacity - currentNode->stored;
//		printf(" malloc for risky   ");
		riskAlloc->memory = (void *) realloc(riskAlloc->memory, newSize);
//		printf(" malloc for risky end \n  ");
		if(riskAlloc->memory == NULL)
		{
			fprintf(stderr, "Bad Alloc\n");
			exit(3);
			return NULL;
		}
		riskAlloc->capacity = newSize;
		currentNode->stored = size;
		currentNode->isUsed = 1;
		return currentNode->memLocation;
		}
		else
		{
			return var;
		}
	}





