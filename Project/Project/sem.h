#ifndef __SEM_H_
#define __SEM_H_
/*****************************************************************************************************
 * Name: 	Easa El Sirgany 1001361972 eelsirga@asu.edu
 * 		Eric Tang 1206899599 etang4@asu.edu
 * 
 * File: 	sem.h
 *
 * Description:	This is the header file for the seamphores modified utilize the queue 
 created in the previous project.
 ****************************************************************************************************/
#include "TCB.h" //For TCB_t
#include "threads.h"
#include "q.h"

extern TCB_t *RunQ; //Defined in thread_test.c

typedef struct my_sem_t {
     int count;
     TCB_t *Q;
} my_sem_t;

void InitSem(my_sem_t *S, int val){
	memset(S, 0, sizeof(my_sem_t)); //Initialize Q
	S->count = val;
}

void P(my_sem_t *S){
	S->count--;
	if(S->count < 0){
		TCB_t *tmp = DelQueue(&RunQ);
		AddQueue(&(S->Q),tmp);
		swapcontext(&(tmp->context), &(RunQ->context));		
	}
}

void V(my_sem_t *S){
	S->count++;
	if(S->count <= 0){
		TCB_t *tmp = DelQueue(&(S->Q));
		AddQueue(&RunQ, tmp);
	}
	yield();
}

#endif //__SEM_H_
