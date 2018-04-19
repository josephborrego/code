# Assign compiler:
CC=gcc

# Compiler options:
CFLAGS=-g -Wall -Werror -std=gnu99 -c

# Loader Flags:
LDFLAGS=

# Source files (.c or .cpp)
SRCS= ExecutionPair.c Piper.c Command.c

# Object files (Derived from SRCS)
OBJS=$(SRCS:.c=.o)

# Header files (.h)
HEADERS= ExecutionPair.h Command.h

# Executable
EXE= prog6

# Tar Archive
TAR=prog6.tgz

#all: struct
all: $(EXE)

#struct: Item.o struct.o
$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@


%.o: %.c Item.h
	$(CC) $(CFLAGS) $< -o $@
#	gcc -g.......-c %.c -o %.o

#struct.o: struct.c Item.h
#	$(CC) $(CFLAGS) struct.c -o struct.o
#
#Item.o: Item.c Item.h
#	$(CC) $(CFLAGS) Item.c -o Item.o
#Item.o: Item.c Item.h
#	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean tar
clean:
	rm -f $(OBJS) $(EXE) $(TAR)

tar:
	tar -czvf $(TAR) $(SRCS) $(HEADERS)

#depend: .depend
#.depend: $(SRCS)
#	rm -f ./.depend
#	$(CC) $(CFLAGS) -MM $^ -MF ./.depend;
#
#include .depend

