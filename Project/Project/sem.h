#ifndef __SEM_H_
#define __SEM_H_
/*****************************************************************************************************
 * Name: 	Easa El Sirgany 1001361972 eelsirga@asu.edu
 * 		Eric Tang 1206899599 etang4@asu.edu
 * 
 * File: 	sem.h
 *
 * Description:	
 ****************************************************************************************************/
#include "tcb.h" //For TCB_t
#include "threads.h"

extern TCB_t *RunQ; //Defined in thread_test.c

typedef struct my_sem_t {
     int count;
     TCB_t *Q;
} my_sem_t;

void initSem(my_sem_t *S, int val){
	memset(S, 0, sizeof(my_sem_t)); //Just in case (I'm paranoid)
	S->count = val;
}

void P(my_sem_t *S){
	S->count--;
	if(S->count < 0){
		TCB_t *tmp = DelQueue(&RunQ);
		AddQueue(&(S->Q), tmp);
	}
}

void V(my_sem_t *S){
	S->count++;
	if(S->count < 1){
		TCB_t *tmp = DelQueue(&(S->Q));
		AddQueue(&RunQ, S->Q);
		yield();
	}
}

#endif //__SEM_H_
