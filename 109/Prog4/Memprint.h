#ifndef MEMPRINT_H
#define MEMPRINT_H

//This function takes a pointer and pretty prints the first size bytes to FILE output.
void printData(FILE *output, void *src, int size);

#endif
