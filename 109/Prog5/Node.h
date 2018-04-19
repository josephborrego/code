
/*
CSE 109: Spring 2017
<Joseph Borrego>
<Job218>
<inorder insertion Linked List>
Program #5
*/

    //if not defined, define a file of these things
    #ifndef NODE_H_
    #define NODE_H_

	struct Node
	{
		struct Node* nextNode;
		char* name;
		void* data;
		size_t dataSize;
	};

	#endif

