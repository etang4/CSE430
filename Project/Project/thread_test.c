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
#include "sem.h"

/*
 * Macros
 */
#define forever for(;;)

/*
 * Global variables
 */
TCB_t *RunQ = NULL;
my_sem_t mutex;
int n;


/*
 * Functions
 */
void func1(){
	forever{
		//Add something to print (from your notes:)
		//f1(){
		//	P(S);
		//	n++;
		//	print(n);
		//	V(S);
		//}
		yield();
	}
}

void func2(){
	forever{
		//Same here:
		//f2(){
		//	P(S);
		//	n--;
		//	print(n);
		//	V(S);
		//}
		yield();
	}
}

int main(){
	initSem(mutex, 2);

	start_thread(printhw);
	start_thread(printgbw);

	run();
}
