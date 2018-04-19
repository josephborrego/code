#ifndef SUPPORT_H__
#define SUPPORT_H__
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "support.h"

/*
 * Store information about the team who completed the assignment, to
 * simplify the grading process.  This is just a declaration.  The definition
 * is in team.c.
 */
extern struct team_t
{
	const char* name1;
	const char* email1;
	const char* name2;
	const char* email2;
} team;

/*
* Make sure that the student name and email fields are not empty.
*/
/*
void check_team(char * progname) {
   if((strcmp("", team.name1) == 0) || (strcmp("", team.email1) == 0))
   {
	   printf("%s: Please fill in the student struct in team.cc\n", progname);
	   exit(1);
   }
   printf("Student 1: %s\n", team.name1);
   printf("Email 1  : %s\n", team.email1);
   printf("Student 2: %s\n", team.name2);
   printf("Email 2  : %s\n", team.email2);
   printf("\n");
}
*/
/*
 * This function verifies that the student name is filled out
 */
void check_team(char *);

#endif

