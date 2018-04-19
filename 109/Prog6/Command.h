
#ifndef COMMAND_H
#define COMMAND_H

 struct Command
{
	char *comstring;
	char **argv;
	int argsize;
	int size;
	int argc;
};
struct Command* createCommand(char* string, int size);
struct Command* destroyCommand(struct Command*);

#endif
