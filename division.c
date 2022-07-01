#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include<time.h>
#include <string.h>
#include <stdlib.h>


////////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
// Other Files:      N/A
// Semester:         CS 354 Fall 2020
// Instructor:       deppeler
// 
// Discussion Group: 7
// Author:           James Gui
// Email:            jgui2@wisc.edu
// CS Login:         jgui2@wisc.edu
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          N/A
//
// Online sources:   https://man7.org/linux/man-pages/man2/getpid.2.html
//                   https://www.youtube.com/watch?v=_1TuZUbCnX0&t=162s
//////////////////////////// 80 columns wide ///////////////////////////////////

//global fields and values
int total_count_integer = 0; //counts the number of times the division has run

/* this function provides the divide by zero handler with code to terminate process
 *
 * int num, not nessecary to be used
 */

static void DivideByZeroError(int num)
{
    printf("Error: a division by 0 operation was attempted. \n");
    printf("\nTotal number of operatiions completed successfully %d. \n", total_count_integer);
	printf("This program will be terminated. \n");
    exit(0);
}

/* this function provides the divide by interrupt handler with code to exit upon interrupt
 *
 * no params
 */

static void controlC()
{
	printf("\nTotal number of operatiions completed successfully %d. \n", total_count_integer);
	printf("This program will be terminated. \n");
	exit(0);
}


/* main function that divides 2 user inputted numbers, formats 
 *  response to division, and handles errors
 *
 * argc, command line argument number
 * argv command line arguments
 * returns 0 upon completion
 */

int main(int argc, char *argv[]) {
    
    //this registers a sigaction for divide by zero error
    struct sigaction act;
	memset (&act, '\0', sizeof(act));
    act.sa_sigaction = (void (*) ) DivideByZeroError;
	act.sa_handler = DivideByZeroError;//registers to DivideByZeroError()
	act.sa_flags = SA_RESTART;
    //checks sigaction
	if (sigaction(SIGFPE, &act, NULL) < 0) {
	perror ("error registering action");
		return 1;
	}

    //registers control-c handler
    struct sigaction act3;
	memset (&act3, '\0', sizeof(act3));
    act3.sa_sigaction = (void (*) ) &controlC;
	act3.sa_handler = controlC; //links to func controlC()
	act3.sa_flags = SA_RESTART;
    //checks sigaction
	if (sigaction(SIGINT, &act3, NULL) < 0) {
		perror ("error registering action");
		return 1;
	}



    //forever loop unless interrupted or killed
    while(1)
    {
        //initilzes pointer values
        char *ptr1 = malloc(100 * sizeof(char));
        if(ptr1 == NULL)
        {
            printf("no space for malloc");
            exit(0);
        }

        char *ptr2 = malloc(100 * sizeof(char));
        if(ptr2 == NULL)
        {
            printf("no space for malloc");
            exit(0);
        }


        //prompts user inputted integer 1, formats with atoi to convert strings
        printf("Enter first integer: ");

        if( fgets(ptr1, 100, stdin) != NULL)   //stores value in ptr1
        { 
            *ptr1 = atoi(ptr1);
        }
        else{
            printf("issue, no readable input \n");
        }

        //prompts user inputted integer 2, formats with atoi to convert strings
        printf("Enter second integer: ");

        if( fgets(ptr2 , 100, stdin) != NULL)
         {
             *ptr2 = atoi(ptr2); //stores value in ptr2
         }
         else{
             printf("issue, no readable input \n");
         }
        //no error checking
        
        //divides the two user inputted numbers, 
        int tempInt = *ptr1 / *ptr2;
        //calculates remainder of the division
        int tempModulo = *ptr1 % *ptr2;
        
        //increases total number of divisions
        total_count_integer ++;
        //print out value
        printf("%d / %d is %d with a remainder of %d \n", *ptr1, *ptr2, tempInt, tempModulo);

        //fress pointers
        free(ptr1);
        ptr1 = NULL;

        free(ptr2);
        ptr2 = NULL;
    }
    return 0;
}