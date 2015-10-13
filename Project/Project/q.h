#ifndef __Q_H_
#define __Q_H_
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
#include "tcb.h"

/*
 * Function definitions
 */
//Create a new Queue element
TCB_t *NewItem(){
	TCB_t *nnode;
	nnode = (TCB_t *) malloc(sizeof(TCB_t));

	//Apparently we are creating a new blank item . . .
	memset(nnode, 0, sizeof(TCB_t));
	return nnode;
}

//Create an empty queue pointed to by the variable head
void InitQueue(TCB_t *head){
}

//Adds an item to the queue
void AddQueue(TCB_t *head, TCB_t *item){
}

//Deletes the queue
TCB_t *DelQueue(TCB_t *head){
}

//equivalent to AddQ(&head, DeleteQ(&head)), but is simpler to use and more efficient to implement
void RotateQ(TCB_t *head){
}

//Free an item's space for future use
void FreeItem(TCB_t *item){
}

#endif //__Q_H_
