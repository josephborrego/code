/*
CSE 109: Spring 2017
<Joseph Borrego>
<job218>
<text changer>
Program #1
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<ctype.h>
#include<getopt.h>


// reverse word function
//-r
void swap(char* pot, char* que)  
{
    while(pot < que)
    {
     	char hold = *pot;
        *pot = *que;
        pot++;
        *que = hold;
        que--;
    }
}

// reverse word
//-r also
void revword(char *line)
{
    char *pot = line;
    char *que = line;

    while(*que != '\0')
    {
        if (isspace(*que)) // Get a word?  ******changed
        {
            swap(pot, que - 1);
            que++;
            pot = que;
        }
	else
		{
 		que++;
		}
    }
    swap(pot, que - 1);
}



// reverse line function
//-e
void reverse(char *line)
{
    //we do -1 because we don't move the new line character to the front
    size_t los = strlen(line) - 1; // ******* changed
    ssize_t v;
    ssize_t n;
    n=los-1;

    for (v=0; v<n; v++, n--)
    {
       char hold=line[v];
        line[v]=line[n];
        line[n]=hold;
    }

}


// change from lowercase to upper case and vice versa
//-t
void upanddown(char *line)
{

size_t q = 0;
char character;

while (line[q] != '\0') {
      character = line[q];
      if (character >= 'A' && character <= 'Z')
         line[q] = line[q] + 32;
      else if (character >= 'a' && character <= 'z')
         line[q] = line[q] - 32;
      q++;
   }
}



int main(int argc, char *argv[])
{
    FILE *input = stdin; //*********changed
  //  char word;
 //   char *string;  // going to need to use this a lot
//    size_t index = 0;
//    size_t  i = 1;
    size_t doReverse = 0;
    size_t doLine = 0;
    size_t doChange = 0;
    size_t opt;


// our argument counters
    while ((opt = getopt(argc, argv, "ret")) != -1)
    {
     	switch(opt)
        {
			case 'r': doReverse = 1; // increment doReverse counter *****changed
        		break;
    		case 'e': doLine = 1;// increment doLine counter // ******* changed
        		break;
			case 't': doChange = 1; // increment doChange counter ******* changed
        		break;
			default: return 1; // // ******* changed
        }
    }

    size_t len = 21000; // ******* changed
    //size_t cap = 0; // realloc memory if need be
    char* line = (char *)malloc(len * sizeof(char));

//do commands on each line
    while(fgets(line, len, input) != NULL)
    {
        if(doLine == 1)
        {
        	reverse(line);
        }

        if(doReverse == 1)
        {
			revword(line);
        }

        if(doChange == 1)
        {
			upanddown(line);
        }
  		printf("%s", line);
    }

free(line);
fclose(input);
return 0;
}


