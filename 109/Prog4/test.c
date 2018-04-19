
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"Alloc.h"

int main(int argc, char **argv)
{

struct Alloc* ourAlloc = constructAlloc(261);
char* as = (char*)allocate(ourAlloc, 7);
printf("heyyy\n");
int* ass = (int*)allocate(ourAlloc, 21);
printf("yo\n");
char* aas = (char*)allocate(ourAlloc, 112);
strcpy(as, "hello\n");
printf("%s\n", as);
printf("%d\n", ass);
printf("capacity is %d\n", getCapacity(ourAlloc));
deallocate(ourAlloc, ass);
printf("size is %d\n", getSize(ourAlloc));
int* bua = (int*)allocate(ourAlloc, 16);
deallocate(ourAlloc, as);
printf("size is %d\n", getSize(ourAlloc));
destructAlloc(ourAlloc);
return 0;

}
