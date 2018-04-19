#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include "support.h"
//read stdin to determine behavior
void task();
//head node w/ attributes
struct node* head;
struct node
{
    int value;
    struct node* other;
};
//sort node function
void sort(struct node* pnode, struct node* znode)
{
    int daval = pnode->value;
    //temp node
    struct node* temp = head;
    //other temp node
    struct node* space;
    if(daval <= head->value)
    {
        head = pnode;
        head->other = temp;
        znode->other = NULL;
    }
    else
    {
        space = temp;
        temp = temp->other;
        while(daval >= temp->value && temp->other != NULL)
        {
            space = temp;
            temp = temp->other;
        }
        if(temp->other != NULL)
        {
            pnode->other = temp;
            space->other = pnode;
            znode->other = NULL;
        }
    }
}
//add function
void add(int val)
{
    if(head == NULL)
    {
        head = (struct node*)malloc(sizeof(struct node));
        head->value = val;
        head->other = NULL;
    }
else
    {
        struct node* temp = head;
        while(temp->other != NULL)
        {
            temp = temp->other;
        }
        temp->other = (struct node*)malloc(sizeof(struct node));
        temp->other->value = val;
        temp->other->other = NULL;
        sort(temp->other, temp);
    }
}
//remove function
void remoove(int val)
{
    struct node* temp = head;
    struct node* spooky;
    if(head == NULL)
    {
        return;
    }
    if(head->value == val)
    {
        head = head->other;
        free(temp);
    }
    else
    {
        while(temp->value != val && temp->other != NULL)
        {
            spooky = temp;
            temp = temp->other;
        }
        if(temp->value == val)
        {
            if(temp->other == NULL)
            {
                spooky->other = NULL;
            }
			else
            {
                spooky->other = temp->other;
            }
            free(temp);
        }
    }
}


//free list
void flist()
{
    struct node* poop;
    while(head != NULL)
    {
        poop = head;
		head = poop->other;
        free(poop);
    }
}


//task manager
//read stdin then execute
void taskmanage()
{
    FILE* fp = stdin;
    int num;
    int val;
    struct node* sponge;
    while((num = fgetc(fp)) != EOF)
    {
        char cval[100];
        switch(num)
        {
            case 'i':
                fgets(cval, sizeof(cval), fp);
                val = atoi(cval);
                add(val);
                break;
            case 'r':
                fgets(cval, sizeof(cval), fp);
                val = atoi(cval);
                remoove(val);
                break;
            case 'p':
                sponge = head;
                fgets(cval, sizeof(cval), fp);
                while(sponge != NULL)
                {
                    fprintf(stdout, "%i", sponge->value);
                    if(sponge->other != NULL)
                    {
                        fprintf(stdout, "->");
                    }
                    sponge = sponge->other;
                }
                fprintf(stdout, "\n");
                break;
            case 'x':
                flist();
                exit(1);
                break;
            default:
                fgets(cval, sizeof(cval), fp);
                fprintf(stderr, "enter command\n");
                break;
        }
    }
    fclose(fp);
}


//helper method
void help(char* progname)
{
    fprintf(stdout, "used %s\n", progname);
    fprintf(stdout, "i = insert, r = remove, p = print, x = exit\n");
}
//main
int main(int argc, char** argv)
{
    long op;
    check_student(argv[0]);
    while((op = getopt(argc, argv, "h")) != -1)
    {
        switch(op)
        {
            case 'h': help(argv[0]);
            break;
        }
    }
    taskmanage();
}

