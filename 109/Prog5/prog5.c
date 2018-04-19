
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
#include "ListFile.h"

	int main(int argc, char **argv)
	{
		if(argc == 4)
		{
			struct ListFile* list1 = readFile(argv[2]);
			saveToFile(list1, argv[3]);
			return 0;
		}
		else if(argc == 5 && strcmp(argv[1], "2"))
		{
			struct ListFile* list2 = readFile(argv[2]);
			appendFromFile(list2, argv[3]);
			saveToFile(list2, argv[4]);
			return 0;
		}
		else if(argc == 5 && strcmp(argv[1], "3"))
		{
			struct ListFile* list3 = readFile(argv[2]);
			struct ListFile* list4 = readFile(argv[3]);
			int result = 1;
			char* elem = (char*)malloc(100000);
			elem = NULL;
			int count = 1;
			elem = getElementName(list4, 0);
			removeByName(list3, elem);
			while(elem != NULL)
			{
				elem = getElementName(list4, count);
				count++;
				result = removeByName(list3, elem);
			}
			saveToFile(list3, argv[4]);
			free(elem);
		}
		else
		{
			printf("invalid, try again\n");
		}
		/*
		struct ListFile* myList = makeList();

		char * data1 = (char*)malloc((strlen("rich homie quan")+1 ) * sizeof(char));
		strcpy(data1, "rich homie quan");

		char * name1 = (char*)malloc((strlen("homie") + 1) * sizeof(char));
        strcpy(name1, "homie");

		insert(myList, name1, data1, (strlen("rich homie quan") + 1) * sizeof(char));

		char * data2 = (char*)malloc((strlen("batman") +1) * sizeof(char));
        strcpy(data2, "batman");

        char * name2 = (char*)malloc((strlen("bat") + 1) * sizeof(char));
        strcpy(name2, "bat");

        insert(myList, name2, data2, (strlen("batman") ) * sizeof(char));

		char* name3 = (char*)malloc((strlen("dawg") + 1) * sizeof(char));
		strcpy(name3, "dawg");

		char* data3 = (char*)malloc((strlen("bobby shmurda")+1) * sizeof(char));
        strcpy(data3, "bobby shmurda");

		struct ListFile* list2 = copyList(myList);
		printf("remove by name\n");
		removeByName(list2, name1);
		printf("%d\n", findByData(list2, data1, (strlen("rich homie quan")+1 ) * sizeof(char)));
		printf("%d\n", findByData(myList, data1, (strlen("rich homie quan") +1) * sizeof(char)));
//		printf("rem data\n");
		removeByData(list2, data2, (strlen("batman") +1) * sizeof(char));
//		printf("insert\n");
		insert(list2, name3, data3, (strlen("bobby shmurda")+1 ) * sizeof(char));
//		readFile(name3);
//		printf("y\n");

		char* output1 = (char*)malloc((strlen("output.1") + 1) * sizeof(char));
        strcpy(name4, "output.1");

		char* output0 = (char*)malloc((strlen("output.0") + 1) * sizeof(char));
        strcpy(name5, "output.0");

		 char* input1 = (char*)malloc((strlen("input.1") + 1) * sizeof(char));
        strcpy(name4, "input.1");

        char* input0 = (char*)malloc((strlen("input.0") + 1) * sizeof(char));
        strcpy(name5, "input.0");

//		appendFromFile(list2, name4);
//		saveToFile(myList, name4);
		printf("get element\n");
//		printf("get element %s\n", (char*)getElement(list2, 0));
		printf("get element name %s\n", getElementName(list2, 0));
		saveToFile(myList, output0);
		struct ListFile* newList = readFile(input1);
		printf("rev get element name %s\n", getElementName(newList, 1));
		appendFromFile(list2, name4);
		printf("get element name %s\n", getElementName(list2, 0));
		printf("get element name %s\n", getElementName(list2, 1));
		printf("get element name %s\n", getElementName(list2, 2));
		free(data1);
		free(name1);
		free(data2);
		free(name2);
		free(name3);
		free(data3);
		free(name4);
		free(name5);
		destroyList(myList);
		destroyList(list2);
		destroyList(newList);
		*/
		return 0;
	}
