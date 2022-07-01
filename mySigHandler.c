#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include<time.h>
#include <string.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        mySigHandler.c
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
int globalCounterSignalNumber = 0;

/* handler for alarm handling, recursivly calls alarm each 3 seconds 
 *
 * param int, not used
 * no return value
 */

static void handler(int num)
{
	
	printf("PID: %ld ", (long) getpid() );
	time_t currentTime;
	time(&currentTime);
	if(currentTime == -1)
	{
		printf("time issue");
		return;
	}
	if(*ctime(&currentTime) == -1)
	{
		printf("error with current time");
	}
    printf("CURRENT TIME: %s", ctime(&currentTime));
	alarm(3);
	
}


/* handler for triggering SIGUSER1
 *
 * param int, not used
 * no return value
 */

static void handler1(int num)
{
	printf("SIGUSER1 handled and counted\n");
	globalCounterSignalNumber ++;
	
}



/* handler for ctrol-c handling, exits program
 * no params
 * no return value
 */

static void controlC()
{
	printf("\nSIGINT handled. \n");
	printf("SIGUSER1 was handled %d times. Exiting now. \n", globalCounterSignalNumber);
	exit(0);
}



/* main, triggers the alarm handler recursive function, sets up other handlers
 *
 * argc, number of command line arguments
 * argv command line arguments
 */

int main(int argc, char *argv[]) {

/*
	int pid = fork();
	if(pid == -1)
	{
		return 1;
	}
	else if(pid == 0)
	{
		sleep(5);
		kill(getppid(), SIGUSR1);
	}
	*/
	printf("PID and time print every 3 seconds. \n");
	printf("Type Ctrl-C to end the program.\n");
	
	//triggers alarm handler after 3 seconds
	alarm(3);

	//sets up the interrupt handler
	struct sigaction act3;
	memset (&act3, '\0', sizeof(act3)); //sets everything no 0
    act3.sa_sigaction = (void (*) ) &controlC;
	act3.sa_handler = controlC; //sets interrupt handler to controlC()
	act3.sa_flags = SA_RESTART; //sets flags to 0
	//checks if properly set up
	if (sigaction(SIGINT, &act3, NULL) < 0) {
		perror ("error registering action");
		return 1;
	}

	//sets up the alarm handler
    struct sigaction act;
	memset (&act, '\0', sizeof(act)); //sets everything no 0
    act.sa_sigaction = (void (*) ) handler;
	act.sa_handler = handler; //sets alarm handler to controlC()
	act.sa_flags = SA_RESTART; //sets flags to 0
	//checks if properly set up
	if (sigaction(SIGALRM, &act, NULL) < 0) {
	perror ("error registering action");
		return 1;
	}

	//sets up the SIGUSER1 handler
    struct sigaction act2;
	memset (&act2, '\0', sizeof(act2)); //sets everything no 0
    act2.sa_sigaction = (void (*) ) &handler1;
	act2.sa_handler = handler1;//sets up the handler to handler1()
	act2.sa_flags = SA_RESTART; //sets flags to 0
	//checks if properly set up
	if (sigaction(SIGUSR1, &act2, NULL) < 0) {
		perror ("error registering action");
		return 1;
	}

	//eternal while loop untill terminated
    while (1) {	
		
    }

    return 0;
}