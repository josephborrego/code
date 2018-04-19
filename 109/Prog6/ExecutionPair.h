/*
CSE 109: Spring 2017
<Joseph Borrego>
<Job218>
<command runner>
Program #6
*/

    //if not defined, define a file of these things
    #ifndef LISTFILE_H_
    #define LISTFILE_H_

	//include command.h
    struct ExecutionPair
	{
		unsigned char model;
		unsigned int sizeA, sizeB;
		struct Command* command1; //struct command object
		struct Command* command2;
	};

	void destroyExecPair(struct ExecutionPair*);
	int execute(struct ExecutionPair* pair);
	#endif
