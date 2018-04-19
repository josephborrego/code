#include<stdio.h>
//#include"myowncode.h"
#include<stdlib.h>

int main(int argc, char **argv)
{
	fprintf(stdout, "Hello World\n");
	printf("Hello World\n");
	fprintf(stderr, "Uncaught line\n");

	for(int i =0; i <argc; i++)
	{
	fprintf(stdout, "Args %d: %s\n", i, argv[i]);
	}

	int number = 5;
	double dnumber = 10.3;
	float fnumber = 4.5;
	int otherNumber = 10;
	char word[10] = "bird";

	word[0] = 'b';
	word[1] = 'i';
	word[2] = 'r';
	word[3] = 'd';
	word[4] = '\0';
	word[4] = (char)0;

	char *wordPtr, letter;
	// Type of wordPtr is (char *)
	// Type of letter is (char)

	letter = 't';
	wordPtr =  &letter;
/*
	fprintf(stderr, "word lives at location: '%p'\n", &word);
	fprintf(stderr, "The word is '%s'\n", word);
/*	fprintf(stderr, "The word is '%c'\n", word);
	fprintf(stderr, "The word is '%c'\n", word[0]);
	fprintf(stderr, "The word is '%c'\n", word[1]);
	fprintf(stderr, "The word is '%c'\n", word[2]);
	fprintf(stderr, "The word is '%c'\n", *word);
	fprintf(stderr, "The word is '%c'\n", *(word+ 1));
	fprintf(stderr, "The word is '%c'\n", *(word+ 2));
*/
/*
	char temp = word[1];
	wordPtr =(char *) &word;
	temp = wordPtr[1];
	temp = *(wordPtr + 1);
	*(wordPtr + 1) = wordPtr[3];
	wordPtr[3] = temp;

	fprintf(stderr, "The word is '%9s'\n",word);  // the string is 9 letters long
	fprintf(stdout, "Enter a number ");
	fscanf(stdin, "%d", &number);
	fprintf(stdout, "The user inputted %d\n", number);

	fscanf(stdin, "%s", wordPtr);
	fprintf(stderr, "The word is '%s'\n", wordPtr);

	fprintf(stdout, "Our values are %d and %d\n",number, otherNumber);
	fprintf(stderr, "other number lives at location '%p'\n", &otherNumber); 

//	char *buffer = (char *)malloc(80* sizeof(char));
//	fscanf(stdin, "%s", buffer);

	char *buffer = NULL;
	fscanf(stdin, "%ms", %buffer);

	free(buffer);
	buffer = NULL;

*/
// TYPE *storage = (TYPE *)malloc(DESIRED_SIZE * sizeof(TYPE));

//use this for program 1
//man getline
//man getc/fgetc

	int size = 80;
	char *buffer = (char *)malloc(80 * sizeof(char));
	//char **sample = (char **)malloc(80 * sizeof(char *))
	fscanf(stdin, "%s", buffer);
	fprintf(stdout, "Input up to %d letters: ", size);
	fscanf(stdin, "%79s", buffer);

	for (int i = 0; i < size; i++)
	{
		buffer[i] = 'q';
	}

	for(int i = 0; i < size; i++)
	{
		fprintf(stdout, "%2d: %c (%d) \n", i, buffer[i], (int)buffer[i]);
	}
	free(buffer);
	buffer = NULL;
	fprintf(stdout, "Input something else, one wors, no size limit: ");
	fscanf(stdin, "%m[^\n]s\n". &buffer);
	fprintf(stdout, "Entered String: %s\n", buffer

/*
	fprintf(stderr, "Letter is '%c'\n",  letter);
	fprintf(stderr, "Letter lives at location: '%p'\n", &letter);
	fprintf(stderr, "We think Letter lives at location: '%p'\n", wordPtr);

	*wordPtr = 'q';
*/
	return 0;

}


