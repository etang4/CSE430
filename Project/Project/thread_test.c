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
#include "unistd.h"

/*
 * Macros
 */
#define forever for(;;)
#define MAX_SIZE 5 

/*
 * Global variables
 */
TCB_t *RunQ = NULL;
my_sem_t mutex;
my_sem_t full;
my_sem_t empty;
int myBuffer[MAX_SIZE];
int inputIndex;
int outputIndex;

/*
 * Functions
 */
//Function Declaration 
void printBuffer();

/*func1 and func2 used for method1 
void func1(){
	forever{
		//Add something to print (from your notes:)
			P(&mutex);
			n++;
			printf("%d",n);
			V(&mutex);
		yield();
	}
}

void func2(){
	forever{
		//Same here:
			P(&mutex);
			n--;
			printf("%d",n);	
			V(&mutex);
		yield();
	}
}
*/

void producerA(){
	forever{	
		P(&full);
		P(&mutex);
		printf("Producer A inserts 2 to buffer\n");
		myBuffer[inputIndex] = 2;
		printBuffer();	
		inputIndex = (inputIndex + 1) % MAX_SIZE;
		sleep(2);
		V(&mutex);
		V(&empty);	
	}
}

void producerB(){
	forever{
		P(&full);
		P(&mutex);
		printf("Producer B inserts 3 to buffer\n");
		myBuffer[inputIndex] = 3;
		printBuffer();	
		inputIndex = (inputIndex + 1) % MAX_SIZE;
		sleep(2);
		V(&mutex);
		V(&empty);
	}
}

void consumerA(){
	forever{
		P(&empty);
		P(&mutex);
		printf("Consumer A consumes buffer data\n");
		myBuffer[outputIndex] = 0;
		outputIndex = (outputIndex + 1) % MAX_SIZE;
		printBuffer();	
		sleep(2);
		V(&mutex);
		V(&full); 
	}
}

void consumerB(){
	forever{
		P(&empty);
		P(&mutex);
		printf("Consumer B consumes buffer data\n");
		myBuffer[outputIndex] = 0;
		outputIndex = (outputIndex + 1) % MAX_SIZE;
		printBuffer();	
		sleep(2);
		V(&mutex);
		V(&full); 
	}
}

void printBuffer(){
	printf("[");
	int i;	
	for(i = 0; i < MAX_SIZE; i++){
		printf(" %d",myBuffer[i]);
	}
	printf(" ]\n");
}
int main(){
	InitSem(&empty, MAX_SIZE);
	InitSem(&full, 0);
	InitSem(&mutex, 1);
	inputIndex = 0;
	outputIndex = 0;
	
	start_thread(consumerA);
	start_thread(consumerB);

	start_thread(producerA);
	start_thread(producerB);

	run();

	return -1;
}
