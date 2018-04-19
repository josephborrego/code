
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


int *expand(int *old_nums, int new_size)
{
int *new_nums = (int *)malloc(new_size * sizeof(int));

    for(size_t k = 0; k< new_size - 1; k++)
    {
     	new_nums[k] = old_nums[k];
    }

free(old_nums);

return new_nums;
}

int main(int argc, char *argv[])
{

    size_t leng = 100;
    int *nums = (int *)malloc(sizeof(int)); //create num pointer

    size_t i =0; // increment counter
    size_t total = 0;

    while(1)
    {

     	// scanf  with a delimitter
        scanf("%d", &nums[i]);

         //sum of numbers
        total= nums[i] + total;

        if(nums[i] == 0)
        {
	break;
	}

	else
	{
	nums = expand(nums, i + 2);
    }

        i++;

    }
    printf("The sum of the numbers is %d.\n", total);

    for(size_t j ; j < i; j++)
    {
        printf("%d", nums[j]);
		//is this the last j?
		if(j != i -1)
		{
		printf(", ");
		}
    }
printf("\n");

free(nums);
return 0;
}

