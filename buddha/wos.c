// I made this program for my buddhist class
//wos stands for wheel of samsara

#include<stdio.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<ctype.h>
#include<getopt.h>
#include<stdlib.h>


	int main(int argc, char*argv[])
	{

		const char* names[] = {"Catherine Fletcher", "Eliana Ginis", "Elizabeth (Liz) Gagliardi",
			"Hanna Brosky", "Heather Simoneau", "Jacob Jurecki", "Kalin Ojert", "Kianna Lauck",
			"Maximilian Ranzato", "Melody Walthers", "Nicholas Trovalli", "Samantha Smith",
			"Sumin Kim", "Sydney Glenn"};

		int opt;
		int max = 13;

		printf("Welcome to the Wheel of Samsara!!!!!!!\n");
		printf("rules of the game:\n");
		printf("There are only 6 questions \n");
		printf("If a user gets the correct answer then they will be elligible for a prize at the end\n");
		printf("if one gets an question incorrect you will be stuck in samsara for another lifetime\n");
		printf("Have FUN!!!!\n");
		printf("\n");

		int array[13];

		//char str2[20];
		//char *str2 = (char*)malloc(100 * sizeof(char));
		srand(time(NULL));
		int r;

		int arr[10];
    	int x, p;
    	int count;
    	int i=0;

    	for(count=0;count<10;count++)
		{
        	arr[count]=rand() % 13;
    	}
    	while(i<6)
		{
        	int r=rand()%13;
        	for (x = 0; x < i; x++)
        	{
            	if(arr[x]==r)
				{
                	break;
            	}
        	}
        	if(x==i)
			{
            	arr[i++]=r;
        	}
    	}

		char mat[] = "material";
		char skill[] = "skilled";
		char unsk[] = "unskilled";
		char natres[] = "resources";
		char conf[] = "conflict";
		char unl[] = "unlimited";
		char dep [] = "dependent happiness";
		char cons [] = "consumeristic happiness";
		char un[] = "unhappy";
		char any[] = "anything";
		char snake[] = "snake";
		int collect[10];

		for (int i = 1; i < 7; i++)
		{
			r = rand() % 13;
			char *str2 = (char*)malloc(100 * sizeof(char));
			int alt = 0;
			//probably one of my proudest moments
			while(alt == 0)
			{
				if(names[r] == NULL)
				{
				r = rand() % 13;
				}
				if(names[r] != NULL)
				{
				printf("Question %d is for %s\n", i, names[r]);
				alt =1;
				}
			}
			alt = 0;

			names[r] = NULL;
			int alternate = 0;

			switch(i)
			{
			case 1:
				while(alternate == 0)
				{
					printf("People in western society believe that they can achieve happiness through the consumption of the _____ ?\n");
					scanf("%s", str2);
					if(strcmp(mat, str2) == 0)
					{
							alternate = 1;
							free(str2);
							continue;
						}
					printf("hint: rhymes with matcereal\n");
				}
			case 2:
 				while(alternate == 0)
                {
                    printf("Consumption of the material is the consumption of natural ____\n");
                    scanf("%s", str2);
                    if(strcmp(natres, str2) == 0)
                    {
                            alternate = 1;
                            free(str2);
                            continue;
                    }
					printf("%s\n", natres);
                    printf("hint: rhymes with pea sources\n");
                }
			case 3:
 				while(alternate == 0)
                {
                    printf("People who enjoy consumeristic happiness tend to be _____\n");
                    scanf("%s", str2);
                    if(strcmp(un, str2) == 0)
                    {
                            alternate = 1;
                            free(str2);
                            continue;
                        }
                    printf("hint: rhymes with unpappy\n");
                }
			case 4:
 				while(alternate == 0)
                {
                    printf("Consumption / consumerism has led to _______ between nations\n");
                    scanf("%s", str2);
                    if(strcmp(conf, str2) == 0)
                    {
                            alternate = 1;
                            free(str2);
                            continue;
                        }
                    printf("hint: rhymes with con fit\n");
                }
			case 5:
 				while(alternate == 0)
                {
                    printf("Innately people have _____ wants and ______ desires\n");
                    scanf("%s", str2);
                    if(strcmp(unl, str2) == 0)
                    {
                            alternate = 1;
                            free(str2);
                            continue;
                        }
                    printf("hint: rhymes with limited\n");
                }
			case 6:
 				while(alternate == 0)
                {
                    printf("What did Venerable Khamkhien sleep next to in the forest?\n");
                    scanf("%s", str2);
                    if(strcmp(snake, str2) == 0)
                    {
                            alternate = 1;
                            free(str2);
                            continue;
                    }
                    printf("hint: rhymes with cake\n");
                }
		}
	printf("\n");
}
	printf("The winners are...\n");
	printf("EVERYONE!!!!!\n");
	return 0;
}

