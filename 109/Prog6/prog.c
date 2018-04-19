int execute(struct ExecutionPair* pair)
{
    pid_t childIDa;
    int* frepair = (int*)malloc(sizeof(int));
    *frepair = 0;
    childIDa = fork();
    if(childIDa == -1)
    {
     	fprintf(stderr, "Fork failed (%d) :%s\n", errno, strerror(errno));
        return 1;
    }
    if(childIDa != 0)
    {
     	//parent
        return childIDa;
    }
    pid_t childIDb;
    //connects the two together
    int fd[2];
    //pipe is created
    int retval = pipe(&fd[0]);
    if(retval == -1)
    {
     	fprintf(stderr, "Pipe failed: (%d): %s\n", errno, strerror(errno));
        exit(1);
    }
    //output of the program
    int resultfd[2];
    retval = pipe(&resultfd[0]);
    if(retval == -1)
    {
     	fprintf(stderr, "Pipe failed: (%d): %s\n", errno, strerror(errno));
        exit(1);
    }
    childIDb = fork();
    if(childIDb == -1)
    {
     	fprintf(stderr, "Fork failed (%d) :%s\n", errno, strerror(errno));
  exit(1);
    }
    if(childIDb == 0)
    {
        //1in
        if(pair->model >> 6 == 3)
        {
            //1out
            if(((pair->model >>  4) & (3)) == 2)
            {
                //not logical output going to command2 and coming from command 2
                fprintf(stderr, "Error wrong 2-bit value1\n");
                exit(1);
            }
            //difficulty here
            //we're getting input from the pipe, so we're closing the output side of the pipe
            close(fd[1]);
            close(resultfd[0]);
            close(STDIN_FILENO); //closing standard in of this thread
            dup(fd[0]);
            close(fd[0]);
            close(STDOUT_FILENO);
            dup(resultfd[1]);
            close(resultfd[1]);
        }
        else
	{
            if(((pair->model >>  4) & (3)) == 1)
            {
                /* Later joseph's problem
                */
            }
            else
            {
                close(fd[0]);
                close(resultfd[1]);
                close(STDOUT_FILENO); //closing standard out of this thread
                dup(fd[1]);
                close(fd[1]);
                close(STDIN_FILENO);
                dup(resultfd[0]);
                close(resultfd[0]);
            }
        }
	//execution
        char* token;
        const char q[2] = " ";
 token = strtok(pair->command1, q);
        int count = 0;
        while( token != NULL)
        {
            count++;
            token = strtok(NULL, q);
        }
        char **argv = (char**)malloc(count * sizeof(char*));
        for(int i = 0; i < count; i++)
        {
            argv[i] = (char*)malloc(10000 * sizeof(char));
        }
	//we now have room for all the command line arguments, now we need to copy into what we$
        int c = 0;
        token = strtok(pair->command1, q);
        while(token != NULL)
        {
            strcpy(argv[c],token);
            token = strtok(NULL, q);
            c++;
        }
        int retval = execvp(argv[0], argv);
        if(retval == -1)
        {
            fprintf(stderr, "Exec failed (%d): %s\n", errno, strerror(errno));
            for(int i = 0; i < count; i++)
            {
             	free(argv[i]);
            }
            free(pair->command1);
            free(argv);
            exit(3);
        }
	for(int i = 0; i < count; i++)
        {
            free(argv[i]);
        }
        free(pair->command1);
        if(*frepair == 1)
        {
            free(frepair);
            free(pair);
        }
	else
	{
            *frepair = 1;
        }
        free(argv);
    }
    else
    {
        if(((pair->model >> 2) & (3)) == 1)
        {
            if((pair->model & (3)) == 0)
            {
                //not logical output going to command1 and coming from command1
                fprintf(stderr, "Error wrong 2-bit value2\n");
                exit(1);
            }
            close(fd[1]);
            close(resultfd[0]);
            close(STDIN_FILENO); //closing standard in of this thread
            dup(fd[0]);
            close(fd[0]);
            close(STDOUT_FILENO);
            dup(resultfd[1]);
            close(resultfd[1]);
        }
	else
	{
            close(fd[0]);
            close(resultfd[1]);
            close(STDOUT_FILENO); //closing standard out of this thread
            dup(fd[1]);
            close(fd[1]);
            close(STDIN_FILENO);
            dup(resultfd[0]);
            close(resultfd[0]);
        }
        //execution 2
        char* token;
        const char s[2] = " ";
        token = strtok(pair->command2, s);
        int count = 0;
        while( token != NULL)
        {
            count++;
            token = strtok(NULL, s);
        }
        char **argv = (char**)malloc(count * sizeof(char*));
        for(int i = 0; i < count; i++)
 {
            argv[i] = (char*)malloc(10000 * sizeof(char));
        }
	//we now have room for all the command line arguments, now we need to copy into what we$
        int c = 0;
        token = strtok(pair->command2, s);
        while(token != NULL)
        {
            strcpy(argv[c],token);
            token = strtok(NULL, s);
            c++;
        }
        int retval = execvp(argv[0], argv);
        if(retval == -1)
        {
            fprintf(stderr, "Exec failed (%d): %s\n", errno, strerror(errno));
            for(int i = 0; i < count; i++)
            {
                free(argv[i]);
            }
            free(pair->command2);
            free(argv);
            exit(3);
        }
	for(int i = 0; i < count; i++)
        {
            free(argv[i]);
        }
	free(pair->command2);
        if(*frepair == 1)
        {
            free(frepair);
            free(pair);
        }
	else
        {
            *frepair = 1;
        }
	free(argv);
    }
exit(1);
}

