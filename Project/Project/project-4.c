/*****************************************************************************************************
 * Name: 	Easa El Sirgany 1001361972 eelsirga@asu.edu
 * 		Eric Tang 1206899599 etang4@asu.edu
 * 
 * File: 	proj-4.c
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
#include "unistd.h"

/*
 * Macros
 */
#define forever for(;;)
#define R_COUNT 3 
#define W_COUNT 2 

/*
 * Global variables
 */
TCB_t *RunQ = NULL;
my_sem_t *mutex; 
my_sem_t *rsem;
my_sem_t *wsem;
unsigned int rc = 0;
unsigned int rwc = 0;
unsigned int wc = 0;
unsigned int wwc = 0;
unsigned int shared = 0;

/*
 * Functions
 */
//Function Declaration 
void printBuffer();
void reader();
void reader_entry();
void reader_exit();
void writer();
void writer_entry();
void writer_exit();
void printQ(TCB_t *);

void reader(){
	forever{
		sleep(1);	
//		printf("-wwc:%d | wc:%d | rwc:%d | rc:%d\n",wwc,wc,rwc,rc);
//		printf("Reader #%p Started\n",RunQ);
		reader_entry();
//		printf("Reader #%p Entered\n",RunQ);
		P(mutex);
		printf("Reader #%p reads %d\n",RunQ,shared);
		sleep(1);
		V(mutex);
	//	printf("Reader #%p Exiting\n",RunQ);
		reader_exit();
	//	printf("Reader #%p Exited\n",RunQ);	
	}
}

void reader_entry(){
	printf("Reader #%p Waiting\n", RunQ);
	sleep(2);
	P(mutex);
	if(wwc > 0 || wc > 0){
		rwc++;
		V(mutex);
//		printf("Reader #%p Adding to Queue\n",RunQ);
//		printf("-wwc:%d | wc:%d | rwc:%d | rc:%d\n",wwc,wc,rwc,rc);
		P(rsem);
		rwc--;
//		printf("Reader #%p Returned from Queue\n",RunQ);
//		printf("-wwc:%d | wc:%d | rwc:%d | rc:%d\n",wwc,wc,rwc,rc);
	}
	rc++;
	sleep(1);	
	if(rwc > 0){
//		printf("Reader #%p Releasing a reader\n",RunQ);
//		printf("-wwc:%d | wc:%d | rwc:%d | rc:%d\n",wwc,wc,rwc,rc);
		V(rsem);	
	}
	else{
		V(mutex);
	}	
}

void reader_exit(){
	P(mutex);
	rc--;
	if(rc==0 && wwc> 0){
//		printf("Reader #%p Releasing a writer\n", RunQ);
//		printf("-wwc:%d | wc:%d | rwc:%d | rc:%d\n",wwc,wc,rwc,rc);
		V(wsem);	
	}
	else {
		V(mutex);
	}
}

void writer(){
	forever{
		sleep(1);	
//		printf("-wwc:%d | wc:%d | rwc:%d | rc:%d\n",wwc,wc,rwc,rc);
		writer_entry();
//		printf("Writer #%p Entered\n", RunQ); 
		P(mutex);
		shared = rand() % 100;
		printf("Writer #%p writes %d\n",RunQ,shared);
		sleep(1);
		V(mutex);
//		printf("Writer #%p Exiting\n", RunQ);
		writer_exit();
//		printf("Writer #%p Exited\n", RunQ);	
	}
}

void writer_entry(){
	printf("Writer #%p Waiting\n", RunQ);
	sleep(2);	
	P(mutex);
	if(rc>0 || wc > 0){
		wwc++;
		V(mutex);
//		printf("Writer #%p Added to Queue\n", RunQ);
//		printf("-wwc:%d | wc:%d | rwc:%d | rc:%d\n",wwc,wc,rwc,rc);
		P(wsem);
		wwc--;
//		printf("Writer #%p Returned to Queue\n", RunQ);
//		printf("-wwc:%d | wc:%d | rwc:%d | rc:%d\n",wwc,wc,rwc,rc);
	}
	wc++;
	sleep(1);	
	V(mutex);
}

void writer_exit(){
	P(mutex);
	wc--;
	if(rwc >0){
//		printf("Writer #%p Releasing a reader\n", RunQ);
//		printf("-wwc:%d | wc:%d | rwc:%d | rc:%d\n",wwc,wc,rwc,rc);
		V(rsem);	
	}
	else if (wwc >0){
//		printf("Writer #%p Releasing a writer\n", RunQ);
//		printf("-wwc:%d | wc:%d | rwc:%d | rc:%d\n",wwc,wc,rwc,rc);
		V(wsem);
	}
	else{
//		printf("Writer #%p Releasing a resource\n", RunQ);
		V(mutex);
	}
}

void printQ(TCB_t *head){
	if(head == NULL){
		return;
	}
	if(head->next == head){
		printf("|%p\n",head);
	}
	else{
		TCB_t *curr = head;
		do{
			printf("|%p\n",curr);
			curr = curr->next;
		}while(curr != head);
	}	
}


int main(){
	//Initialize Semaphores and variables
	mutex = (struct my_sem_t*)malloc(sizeof(struct my_sem_t));
	rsem= (struct my_sem_t*)malloc(sizeof(struct my_sem_t));
	wsem= (struct my_sem_t*)malloc(sizeof(struct my_sem_t));

	InitSem(mutex, 0);
	InitSem(rsem, 0);
	InitSem(wsem, 1);
	
	start_thread(writer);
	start_thread(writer);
	start_thread(reader);
	start_thread(reader);
	start_thread(reader);
	printf("RunQ\n====\n");
	printQ(RunQ);
	
	//Begin Execution
	run();

	return -1;
}
