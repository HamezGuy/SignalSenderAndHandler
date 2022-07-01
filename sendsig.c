#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include<time.h>
#include <string.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
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




/* this function sends a signal to user inputted pid
 *can only send USER1 signal or CTRL-C signal
 * argc, number of command line arguments
 * argv the command line arguments
 */

int main(int argc, char *argv[]) {

    // check if the number of command line args is corrects, if
    // not it exits
    if(argc > 3)
    {
        printf("Usage: sendsig <signal type> <pid> \n");
        exit(0);
        
    }
    else if(argc < 3)
    {
        printf("Usage: sendsig <signal type> <pid> \n");
         exit(0);
    }
    


    //initializes local var tmpInt to store signal number
    int tempInt = 0;
    

    //sets signal number according to user command line argument
    if(strcmp(argv[1], "-u") )
    {
        tempInt = 10;
    }
    else if(strcmp(argv[1], "-i"))
    {
        tempInt = 2;
    }
    else{
        printf("Usage: sendsig <signal type> <pid> \n");
        
        exit(0);
    }

    //this checks for if user input is a valid pid
    int tempIntn = (int) (atoi(argv[2]));
    if( tempIntn == 0)
    {
        printf("Usage: sendsig <signal type> <pid> \n");
        
        exit(0);
    }
   

    //converts integer user input into pid_t;
    pid_t tempProcessId;
   
    tempProcessId = (pid_t) atoi(argv[2]);

    //sends the signal
    if(kill(tempProcessId, tempInt) != -1)
    {
        return 0;
    }
    else{
        printf( "kill command issue \n");
    }
    return 0;
    

    
}