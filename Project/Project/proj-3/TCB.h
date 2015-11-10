#ifndef __TCB_H_
#define __TCB_H_
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
#include <string.h>
#include <ucontext.h>

typedef struct TCB_t {
     struct TCB_t     *next;
     struct TCB_t     *prev;
     ucontext_t      context;
} TCB_t;

void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
	memset(tcb, 0, sizeof(TCB_t));
	getcontext(&tcb->context);
	tcb->context.uc_stack.ss_sp = stackP;
	tcb->context.uc_stack.ss_size = (size_t) stack_size;
	makecontext(&tcb->context, function, 0);
}

#endif //__TCB_H_
