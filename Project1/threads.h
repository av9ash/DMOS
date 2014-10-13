#include"q.h"
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

extern TCB_t * Q;
void start_thread(void *function)
{
	//printf("Inside start thread....\n");
	int stack_size = 8192;
	void *stack = malloc(stack_size);
	TCB_t *tcb = malloc(sizeof(TCB_t));
	//printf("Address of TCB:%p\n",tcb);
	init_TCB(tcb,function,&stack,stack_size);
	
	//call addQ to add this TCB into the “RunQ” which is a global header pointer
	AddQ(Q,tcb);
}


void run()
{   // real code
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(Q->next->context));  // start the first thread
}


void yield() // similar to run
{
	RotateQ(Q);
	run();
   //rotate the run Q;
   //swap the context, from previous thread to the thread pointed to by runQ
}
