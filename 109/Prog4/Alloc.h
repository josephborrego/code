

/*
CSE 109: Spring 2017
<Joseph Borrego>
<Job218>
<Memory Allocator>
Program #4
*/

    //if not defined, define a file of these things
    #ifndef ALLOC_H_
    #define ALLOC_H_

	struct Node
	{
		struct Node* nextNode;
		void *memLocation;
		int stored;
		int isUsed; //boolean
	};

	struct Alloc
	{
		struct Node* firstNode;
		void *memory;
		int capacity;
	};

	struct Alloc* constructAlloc(int);
	struct Alloc* destructAlloc(struct Alloc*);
	void *allocate(struct Alloc*, int);
	void deallocate(struct Alloc*, void*);
	int getCapacity(struct Alloc*);
	int getSize(struct Alloc*);
	void *getBase(struct Alloc*);
	void **getAllocations(struct Alloc*);
	void *riskyAlloc(struct Alloc*, int);

	#endif
