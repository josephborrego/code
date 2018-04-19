
/*
CSE 109: Spring 2017
<Joseph Borrego>
<Job218>
<inorder insertion Linked List>
Program #5
*/

    //if not defined, define a file of these things
    #ifndef LISTFILE_H_
    #define LISTFILE_H_

	struct ListFile
	{
		struct Node* headNode;
	};

	struct ListFile* makeList();
	struct ListFile* copyList(struct ListFile*);
	struct ListFile* destroyList(struct ListFile*);
	void* findByName(struct ListFile*, char*);
	int findByData(struct ListFile*, void*, int);
	int removeByName(struct ListFile*, char*);
	int removeByData(struct ListFile*, void*, int);
	int insert(struct ListFile*, char*, void*, int);
	struct ListFile* readFile(char*);
	int appendFromFile(struct ListFile*, char*);
	int saveToFile(struct ListFile*, char*);
	void* getElement(struct ListFile*, int);
	char* getElementName(struct ListFile*, int);

	#endif
