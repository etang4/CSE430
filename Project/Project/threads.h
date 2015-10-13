#ifndef __THREADS_H_
#define __THREADS_H_
/*****************************************************************************************************
 * Name: 	Easa El Sirgany 1001361972 eelsirga@asu.edu
 * 		Eric Tang 1206899599 etang4@asu.edu
 * 
 * File: 	tcb.h
 *
 * Description:	This is the header file for the TCB_t that was provided to us. I made some small
 * 		adjustments (like adding a preprocessor guard) based off of my personal preferences.
 * 		Please contact the authors with any questions.
 ****************************************************************************************************/
#include <stdlib.h>
#include "q.h"

/*
 * Global Variables
 */
TCB_t *RunQ;
#define STACK_SIZE 8192

void start_thread(void (*function)(void))
{
	unsigned int *stack;
	stack = (int *) malloc(sizeof(STACK_SIZE));
	TCB_t *nTCB;
	nTCB = (TCB *) malloc(sizeof(TCB_t));
	init_TCB(nTCB, function, stack, STACK_SIZE);
	AddQueue(RunQ, nTCB);
}

void run(){
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	swapcontext(&parent, &(RunQ->conext));  // start the first thread
}

void yield(){
	ucontext_t tmp;
	RotateQ(RunQ);
	swapcontext(&(RunQ->context), &tmp);
}

#endif //__THREADS_H_
