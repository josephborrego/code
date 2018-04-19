
/*
CSE 109: Spring 2017
<Joseph Borrego>
<Job218>
<Linked List>
Program #3
*/

	//if not defined, define a file of these things
	#ifndef LIST_H_
	#define LIST_H_
			//what node is
			struct Node
			{
				// a pointer to another node
				struct Node* nextNode;
				int val;
			};
			struct Node* constructList(int);
			struct Node* destroyList(struct Node*);
			size_t size(struct Node*);
			struct Node* insert(struct Node *, int);
			int find(struct Node *, int);
			int traverse(struct Node *, char *);
			struct Node* removeItem(struct Node *, int);
			char* traverse2(struct Node*);

	#endif
	//end the file
