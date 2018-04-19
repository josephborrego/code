
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{

	char *chunk = (char *)malloc(80 * sizeof(char));

	for(int i = 0; i < 80; i++)
	{
		chunk[i] = '\0';
	}

	fprintf(stdout, "The string is: %s\n", chunk);
    fprintf(stdout, "The string is : %s\n", &chunk[2]);
    fprintf(stdout, "The string is: %s\n", (chunk + 2));

	int *intToString = (int *)chunk;
	//int intToString[0] = 1819308129
	int intToString[0] = 0x6c707061;
	*(intToString + 1) = 0;

	//	fscanf(stdin, "%10s", chunk);

	fprintf(stdout, "The string is: %s\n", chunk);
	fprintf(stdout, "The string is : %s\n", &chunk[2]);
	fprintf(stdout, "The string is: %s\n", (chunk + 2));

	int *number = (int *)chunk;
	fprintf(stdout, "Number is %d[0x%x]\n", *number, *number);

	float *fNumber = (float *)chunk;
	fprintf(stdout, "Float value is %8.2f\n", *fNumber); //%8 is the minimum

	fprintf(stdout, "Location of chunk[0] is %p\n", chunk);
	fprintf(stdout, "Location of number[0] is %p\n", number);

	fprintf(stdout, "Location of chunk[1] is %p\n", (chunk+1));
	//fprintf(stdout, "Chunks are %d bytes large\n", sizeof(*chunk));

	fprintf(stdout, "Chunks are %d bytes large\n", sizeof(char));
	fprintf(stdout, "Location of number[1] is %p\n", (number+1));

//	fprintf(stdout, "Location of number[1] is %p\n", sizeof(*number));
	fprintf(stdout, "Numbers are %d bytes large\n", sizeof(int));

	char array[10];
	char *ptr = (char *)&array;
	int *intPtr = (int *)&array;

	fprintf(stdout, "All three pointers %p %p %p\n", array, ptr, intPtr);

	fprintf(stdout, "Array is at %p\n" array);
	fprintf(stdout, "&rray is at %p\n", (&array +0));

	fprintf(stdout, "Array[1] is at %p\n", (array + 1));
	fprintf(stdout, "&rray is at %p\n", (&array + 1));
	fprintf(stdout, "Ptr[1] is at %p\n", (ptr +1));
	fprintf(stdout, "intPt[1] is at %p\n");

//	fprintf(stdout
//
	return 0;


}
