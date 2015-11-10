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
#include "TCB.h"

/*
 * Function definitions
 */
//Create a new Queue element
TCB_t *NewItem(){
	TCB_t *nnode;
	nnode = (TCB_t *) malloc(sizeof(TCB_t));

	memset(nnode, 0, sizeof(TCB_t));
	return nnode;
}

//creates a empty queue, pointed to by the variable head
void InitQueue(TCB_t **head){
	*head = (TCB_t *) malloc(sizeof(TCB_t));
	memset(*head, 0, sizeof(TCB_t));
}

//Adds an item to the queue
void AddQueue(TCB_t **head, TCB_t *item){
	//If queue is empty.
	if(!*head){
		*head = item;
	}
	else{
		(*head)->prev->next = item;
		item->prev = (*head)->prev;
	}
	(*head)->prev = item;
	item->next = *head;
}

// deletes an item from head and returns a pointer to the deleted item
TCB_t *DelQueue(TCB_t **head){
	TCB_t *deletedElement;
	//last element in queue
	if(!head){
		return NULL;
	}
	else if((*head)->next == *head){
		deletedElement = *head;
	}
	else{
		deletedElement = *head;
		*head = (*head)->next;
		(*head)->prev = deletedElement->prev;
		deletedElement->prev->next = *head;
	}

	return deletedElement;
}

//equivalent to AddQ(&head, DeleteQ(&head)), but is simpler to use and more efficient to implement
void RotateQ(TCB_t **head){
	if(*head)
		*head = (*head)->next;
}

#endif //__Q_H_
