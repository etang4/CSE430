/*
Testing

Write test routines that thoroughly test the queue implementation. Use multiple queues. Pay special attention to deleting the last element of a q. 
Also make sure “RotateQ” is behaves properly (strange behavior of this routine means the insert/delete routines have bugs.)

One suggested test case: Add three elements to queue Q1, and then add 3 more to queue Q2. Rotate each Q twice. 
Delete elements from each q, one by one and print values till the queues are empty. Repeat the above test again.

Further warning: Bugs in the Q routines have been the #1 cause for strange errors in the project, always.
*/

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

//creates a empty queue, pointed to by the variable head
TCB_t *InitQueue(TCB_t *head){
	if(!head){
		head = (TCB_t *) malloc(sizeof(TCB_t));
		memset(head, 0, sizeof(TCB_t));
	}
	else
		puts("Head is not NULL!\nReturning head unchanged.");

	return head;
}

//Adds an item to the queue
TCB_t *AddQueue(TCB_t *head, TCB_t *item){
	//If queue is empty.
	if(!head){
		head = item;
	}
	else{
		head->prev->next = item;
		item->prev = head->prev;
	}
	head->prev = item;
	item->next = head;

	return head;
}

// deletes an item from head and returns a pointer to the deleted item
TCB_t *DelQueue(TCB_t *head){
	TCB_t *deletedElement = head;
	//last element in queue
	if (!head) {
		//empty queue. Do nothing.
	}
	else if (head->next = head) {
		head = NULL;
	}
	else {
		head = head->next;
		head->prev = deletedElement->prev;
		deletedElement->prev->next = head;
	}

	return deletedElement;
}

//equivalent to AddQ(&head, DeleteQ(&head)), but is simpler to use and more efficient to implement
TCB_t *RotateQ(TCB_t *head){
	head = head->next;
}

//Free an item's space for future use
void FreeItem(TCB_t *item){
	/*
	 * When freeing an item, we don't care if the item points to something or not, because
	 * we will not be touching it ever again (and if we try, we will get a seg fault). The
	 * pointers in the list need to change any pointers to the element prior to calling this
	 * funciton (since we cannot make changes to the stackframe that this is called from),
	 * and this fact (in my opinion) makes this function completely trivial.
	 */
	free(item);
}

#endif //__Q_H_
