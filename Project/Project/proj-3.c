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
unsigned int inputIndex;
unsigned int outputIndex;

/*
 * Functions
 */
//Function Declaration 
void printBuffer();

/*func1 and func2 used for method 1. 
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

// Producer and Consumer Functions used for method 2.

//First Producer Method
void producerA(){
	forever{	
		P(&full);
		//Critical Section
		myBuffer[inputIndex] = 2;
		inputIndex = (inputIndex + 1) % MAX_SIZE;
		printf("Producer A inserts 2 to buffer\n");
		printBuffer();	
		sleep(1);
		//End of Critical Section
		V(&empty);	
	}
}

//Second Producer Method
void producerB(){
	forever{
		P(&empty);
		//Critical Section
		myBuffer[inputIndex] = 3;
		inputIndex = (inputIndex + 1) % MAX_SIZE;
		printf("Producer B inserts 3 to buffer\n");
		printBuffer();	
		sleep(1);
		//End of Critical Section
		V(&full);
	}
}

//First Consumer Method
void consumerA(){
	forever{
		P(&empty);
		//Critical Section
		myBuffer[outputIndex] = 0;
		outputIndex = (outputIndex + 1) % MAX_SIZE;
		printf("Consumer A consumes buffer data\n");
		printBuffer();	
		sleep(1);
		//End of Critical Section
		V(&full); 
	}
}

//Second Consumer Method
void consumerB(){
	forever{
		P(&full);
		//Critical Section
		myBuffer[outputIndex] = 0;
		outputIndex = (outputIndex + 1) % MAX_SIZE;
		printf("Consumer B consumes buffer data\n");
		printBuffer();	
		sleep(1);
		//End of Critical Section
		V(&empty); 
	}
}

//Prints buffer content
void printBuffer(){
	printf("[");
	int i;	
	for(i = 0; i < MAX_SIZE; i++){
		printf(" %d",myBuffer[i]);
	}
	printf(" ]\n");
}

int main(){
	//Initialize Semaphores and variables
	InitSem(&empty, MAX_SIZE);
	InitSem(&full, 0);
	InitSem(&mutex, 1);
	inputIndex = 0;
	outputIndex = 0;
	
	//Initialize Buffer
	int i;	
	for(i = 0; i < MAX_SIZE;i++){
		myBuffer[i] = 1;
	}	

	//Add process to threads
	start_thread(consumerA);
	start_thread(consumerB);
	start_thread(producerA);
	start_thread(producerB);

	//Begin Execution
	run();

	return -1;
}
