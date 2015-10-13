/*****************************************************************************************************
 * Name: 	Easa El Sirgany 1001361972 eelsirga@asu.edu
 * 		Eric Tang 1206899599 etang4@asu.edu
 * 
 * File: 	thread_test.c
 *
 * Description:	This is the C file to test our implementation of the queueing routins, implementing
 * 		running multiple functions as threads, using non-preemptive scheduling.
 *
 * 		Please contact the authors with any questions that you may have.
 ****************************************************************************************************/
#include <stdio.h>
#include "threads.h"
#include "q.h" //This is why we use preprocessor guards

/*
 * Macros
 */
#define forever for(;;)

/*
 * Global variables
 */
TCB_t *RunQ;


/*
 * Functions
 */
void printhw(){
	forever{
		puts("Hello world!");
		yield();
	}
}

void printgbw(){
	forever{
		puts("Goodbye cruel world!");
		yield();
	}
}

int main(int argc, char *argv[]){
	start_thread(printhw);
	start_thread(printgbw);

	run();
}
