
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv)
{
	int size = 0;
	int capacity = 5;
	int *array = (int *)malloc(capacity * sizeof(int));
	int input = 0;

	fprintf(stdout, "Enter a number: ");

	while(fscanf(stdin, "%d", &input)) //put into address input = (&input)
	{
		printf("Enter how many times to insert it: ");

		int times = 0;

		fscanf(stdin, "%d", &times);

		if(size == capacity)
		{
			//array = expand()
		}
		for(size_t i = 0; i < times; i++)
		{
			array[size] = input;
			size++;
		}
	}

	free(array);
	return 0;
}
