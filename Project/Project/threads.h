#ifndef __THREADS_H_
#define __THREADS_H_
/*****************************************************************************************************
 * Name: 	Easa El Sirgany 1001361972 eelsirga@asu.edu
 * 		Eric Tang 1206899599 etang4@asu.edu
 * 
 * File: 	threads.h
 *
 * Description:	This is the header file for the thread_test.c file, containing the definition of the
 * 		global vaiable RunQ, as well as a few functions to manipulate the threads that we are
 * 		creating.
 *
 * 		For any questions, please contact the authors.
 ****************************************************************************************************/
#include <stdlib.h>
#include "q.h"

/*
 * Global Variables
 */
extern TCB_t *RunQ; //Defined in thread_test.c
#define STACK_SIZE 8192

void start_thread(void (*function)(void))
{
	unsigned int *stack;
	stack = (unsigned int *) malloc(STACK_SIZE);
	memset(stack, '\0', STACK_SIZE);
	TCB_t *nTCB;
	nTCB = (TCB_t *) malloc(sizeof(TCB_t));
	init_TCB(nTCB, function, stack, STACK_SIZE);
	AddQueue(&RunQ, nTCB);
}

void run(){
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	swapcontext(&parent, &(RunQ->context));  // start the first thread
}

void yield(){
	ucontext_t tmp;
	RotateQ(&RunQ);
	swapcontext(&(RunQ->context), &tmp);
}

#endif //__THREADS_H_
