
/*
CSE 109: Spring 2017
<Joseph Borrego>
<job218>
<inorder insertion Linked List>
Program #5
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ListFile.h"
#include "Node.h"

struct ListFile* makeList()
{
	struct ListFile* newList = (struct ListFile*)malloc(sizeof(struct ListFile));
	newList->headNode = NULL;
	return newList;
}

struct ListFile* copyList(struct ListFile* list)
{
	if(list == NULL)
	{
		return NULL;
	}
	struct ListFile* theList = makeList();
	if(list->headNode == NULL)
	{
		return theList;
	}
	struct Node* currentNode = list->headNode;
	struct Node* prevNode = NULL;
	struct Node* newNode = NULL;
	while(currentNode != NULL)
	{
		newNode = (struct Node*)malloc(sizeof(struct Node));
 		newNode->name = (char*)malloc(sizeof(char) * (strlen(currentNode->name) + 1));
    	strcpy(newNode->name, currentNode->name);
	//	printf("cur.datSize is %d\n", currentNode->dataSize);
    	newNode->data = (void*)malloc(currentNode->dataSize);
    	memcpy(newNode->data, currentNode->data, currentNode->dataSize);
    	newNode->dataSize = currentNode->dataSize;
		newNode->nextNode = NULL;
		if(theList->headNode == NULL)
		{
			theList->headNode = newNode;
		}
		else
		{
			prevNode->nextNode = newNode;
		}
		prevNode = newNode;
		currentNode = currentNode->nextNode;
	}
	return theList;
}

struct ListFile* destroyList(struct ListFile* theList)
{
	if(theList == NULL)
	{
		return NULL;
	}
	if(theList->headNode == NULL)
	{
		free(theList);
		return NULL;
	}
	struct Node* danode = theList->headNode;
	struct Node* next = theList->headNode;
	while(next != NULL)
	{
		next = danode->nextNode;
		free(danode->name);
		free(danode->data);
		free(danode);
		if(next != NULL)
		{
			danode = next;
		}
	}
	free(theList);
	return NULL;
}

void* findByName(struct ListFile* filez, char* word)
{
	if(filez == NULL)
	{
		return NULL;
	}
	if(filez->headNode == NULL)
	{
		return NULL;
	}
	struct Node* currentNode = filez->headNode;
	while(currentNode != NULL)
	{
		if(strcmp(currentNode->name, word) == 0)
		{
			return currentNode->data;
		}
		currentNode = currentNode->nextNode;
	}
	return NULL;
}

int findByData(struct ListFile* files, void* serdata, int num)
{
	if(files == NULL)
	{
		return 0;
	}
	if(files->headNode == NULL)
	{
		return 0;
	}
	struct Node* currentNode = files->headNode;
	int count = 0;
	while(currentNode != NULL)
	{
		if(memcmp(currentNode->data, serdata, num) == 0)
		{
			count++;
		}
		currentNode = currentNode->nextNode;
	}
	return count;
}

int removeByName(struct ListFile* list, char* searchName)
{
	if(list == NULL)
	{
		return 0;
	}
	if(list->headNode == NULL)
	{
		return 0;
	}
	struct Node* currentNode = list->headNode;
	struct Node* prevNode = NULL;
	while(currentNode->nextNode != NULL)
	{
		if(strcmp(currentNode->name, searchName) == 0)
		{
			if(prevNode == NULL)
			{
				list->headNode = currentNode->nextNode;
			}
			else
			{
				prevNode->nextNode = currentNode->nextNode;
			}
			free(currentNode->data);
			free(currentNode->name);
			free(currentNode);
			return 1;
		}
		prevNode = currentNode;
		currentNode = currentNode->nextNode;
	}
	if(strcmp(currentNode->name, searchName) == 0)
	{
		free(currentNode->data);
		free(currentNode->name);
		free(currentNode);
		if(prevNode != NULL)
		{
			prevNode->nextNode = NULL;
		}
		else
		{
			list->headNode = NULL;
		}

		return 1;
	}
	return 0;
}

int removeByData(struct ListFile* list, void* ret, int nums)
{
	if(list == NULL)
	{
		return 0;
	}
	if(list->headNode == NULL)
	{
		return 0;
	}
	struct Node* startNode = list->headNode;
	struct Node* currentNode = list->headNode;
	struct Node* savedNode = list->headNode;
	struct Node* tempNode = NULL;
	int removed = 0;
	while(currentNode->nextNode != NULL)
	{
		if(nums == currentNode->dataSize && memcmp(currentNode->data, ret, nums) == 0)
		{
			removed++;
			tempNode = currentNode->nextNode;
			if(currentNode == startNode)
			{
				startNode = currentNode->nextNode;
			}
			if(currentNode == savedNode)
			{
				savedNode = currentNode->nextNode;
			}
			free(currentNode->name);
			free(currentNode->data);
			free(currentNode);
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
		}
	}
		//edge cases
	if(nums == currentNode->dataSize && memcmp(currentNode->data, ret, nums) == 0)
	{
		savedNode->nextNode = NULL;
		if(currentNode == startNode)
		{
			startNode == NULL;
		}
		removed++;
		free(currentNode->data);
		free(currentNode->name);
		free(currentNode);
		if(tempNode == NULL)
		{
			list->headNode = NULL;
		}

	}
	else
	{
		if(savedNode != NULL)
		{
			if(savedNode != currentNode)
			{
				savedNode->nextNode = currentNode;
			}
			else
			{
				savedNode->nextNode = NULL;
			}
		}
	}
	if(tempNode != NULL)
	{
		list->headNode = startNode;
	}
	return removed;
}



int insert(struct ListFile* lists, char* isname, void* dat, int numz)
{
	if(lists == NULL)
	{
		return NULL;
	}
	if(lists->headNode == NULL)
	{
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = (void*)malloc(numz);
        memcpy(newNode->data, dat, numz);
        newNode->name = (char*)malloc((strlen(isname) + 1) * sizeof(char*));
        strcpy(newNode->name, isname);
        newNode->dataSize = numz;
        newNode->nextNode = lists->headNode;
        lists->headNode = newNode;
        return 1;
	}
//	printf("after null check\n");
	if(strcmp(lists->headNode->name, isname) == 0)
	{
		return 0;
	}
	if(strcmp(lists->headNode->name, isname) > 0)
	{
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = (void*)malloc(numz);
		memcpy(newNode->data, dat, numz);
        newNode->name = (char*)malloc((strlen(isname) + 1) * sizeof(char*));
		strcpy(newNode->name, isname);
        newNode->dataSize = numz;
        newNode->nextNode = lists->headNode;
        lists->headNode = newNode;
        return 1;
	}
//	printf("current node\n");
	struct Node* currentNode = lists->headNode;
	while(currentNode->nextNode != NULL)
	{
//		printf("while\n");
//		printf("cur node.nex.name is %s\n", currentNode->nextNode->name);
//		printf("is name %s\n", isname);
		if(strcmp(currentNode->nextNode->name, isname) == 0)
		{
			return 0;
		}
		if(strcmp(currentNode->nextNode->name, isname) > 0)
		{
//			printf("strcmp \n");
			struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
			newNode->data = (void*)malloc(numz);
			memcpy(newNode->data, dat, numz);
        	newNode->name = (char*)malloc((strlen(isname) + 1) * sizeof(char*));
		 	strcpy(newNode->name, isname);
			newNode->dataSize = numz;
			newNode->nextNode = currentNode->nextNode;
			currentNode->nextNode = newNode;
	//		printf("about to return\n");
			return 1;
		}
		currentNode = currentNode->nextNode;
	}
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = (void*)malloc(numz);
	memcpy(newNode->data, dat, numz);
    newNode->name = (char*)malloc((strlen(isname) + 1) * sizeof(char*));
	strcpy(newNode->name, isname);
    newNode->dataSize = numz;
    newNode->nextNode = NULL;
    currentNode->nextNode = newNode;
    return 1;
}

struct ListFile* readFile(char* wordz)
{
	FILE *fp;
	fp = fopen(wordz, "r");
	if(fp == NULL)
	{
		return NULL;
	}
	int namesize, datasize;
	char* tempname;
	void* tempdata;
	struct ListFile* templist = makeList();
	while(fread(&namesize, 4, 1, fp) != 0)
	{
		if(fread(&datasize, 4, 1, fp) == 0)
		{
			return NULL;
		}
		tempname = (char*)malloc(namesize);
	//	printf("malloc tempname\n");
		tempdata = (void*)malloc(datasize);
	//	printf("malloc tempdata\n");
		if(fread(tempname, namesize, 1, fp) == 0)
		{
	//		printf("freeing tempname in if1\n");
			free(tempname);
	//		printf("freeing tempdata in if1\n");
        	free(tempdata);
			return NULL;
		}
		if(fread(tempdata, datasize, 1, fp) == 0)
		{
	//		printf("freeing tempname in if2\n");
		 	free(tempname);
	//		printf("freeing tempdata in if2\n");
        	free(tempdata);
			return NULL;
		}
		insert(templist, tempname, tempdata, datasize);
	//	printf("freeing tempname out\n");
		free(tempname);
	//	printf("freeing tempdata out\n");
        free(tempdata);
	}
	fclose(fp);
	//free(tempname);
	//free(tempdata);
	return templist;
}


int appendFromFile(struct ListFile* filey, char* wurd)
{
	FILE *fp;
	fp = fopen(wurd, "r");
	if(fp == NULL)
	{
		return -1;
	}
	int namesize, datasize;
	int counter = 0;
	char* tempname;
	void* tempdata;
	while(fread(&namesize, 4, 1, fp) != 0)
	{
//		printf("in while from appFile\n");
		if(fread(&datasize, 4, 1, fp) == 0)
		{
			return -1;
		}
		tempname = (char*)malloc(namesize);
		tempdata = (void*)malloc(datasize);
//		printf("fread tempname\n");
		if(fread(tempname, namesize, 1, fp) == 0)
		{
		 	free(tempname);
        	free(tempdata);
			return -1;
		}
//		printf("temp name is %s and namesize is %d\n", tempname, namesize);
		if(fread(tempdata, datasize, 1, fp) == 0)
		{
			free(tempname);
        	free(tempdata);
			return -1;
		}
//		printf("about to insert\n");
		if(insert(filey, tempname, tempdata, datasize) == 1)
		{
			counter++;
		}
		free(tempname);
    	free(tempdata);
	}
	//free(tempname);
	//free(tempdata);
	fclose(fp);
	return counter;
}


int saveToFile(struct ListFile* listr, char* werd)
{
	FILE *fp;
	fp = fopen(werd, "w");
	if(fp == NULL)
	{
		return -1;
	}
	struct Node* currentNode = listr->headNode;
	int namesize, datasize;
	while(currentNode != NULL)
	{
		namesize = (strlen(currentNode->name)+ 1) * sizeof(char);
//		printf("cur.name is %s and name size is %d\n", currentNode->name, namesize);
		datasize = currentNode->dataSize;
	//	printf("data size is %d\n", datasize);
		if(currentNode->name == 0)
		{
			return -1;
		}
		if(fwrite(&namesize, 4, 1, fp) == 0)
		{
			return -1;
		}
		if(fwrite(&datasize, 4, 1, fp) == 0)
		{
			return -1;
		}
	//	printf("if 1\n");
		if(fwrite(currentNode->name, namesize, 1, fp) == 0)
		{
			return -1;
		}
	//	printf("if 2\n");
//		printf("cur.data is %s\n", (char*)currentNode->data);
		if(fwrite(currentNode->data, datasize, 1, fp) == 0)
		{
	//		printf("about to return\n");
			return -1;
		}
	//	printf("after if\n");
		currentNode = currentNode->nextNode;
	}
	fclose(fp);
	return 0;
}

void* getElement(struct ListFile* filee, int thenum)
{
	if(filee == NULL)
	{
		return NULL;
	}
	if(filee->headNode == NULL)
	{
		return NULL;
	}
	//printf("creating node\n");
	struct Node* currentNode = filee->headNode;
	for(int i = 0; i < thenum && currentNode != NULL ; i++)
	{
	//	printf("in for\n");
		currentNode = currentNode->nextNode;
	}
	if(currentNode == NULL)
	{
	//	printf("cur node is null\n");
		return NULL;
	}
	//printf("ret\n");
	return currentNode->data;
}

char* getElementName(struct ListFile* filer, int numb)
{
	if(filer == NULL)
	{
		return NULL;
	}
	if(filer->headNode == NULL)
	{
		return NULL;
	}
	struct Node* currentNode = filer->headNode;
	for(int i = 0; i < numb && currentNode != NULL; i++)
	{
		currentNode = currentNode->nextNode;
	}
	if(currentNode == NULL)
	{
		return NULL;
	}
	return currentNode->name;
}
