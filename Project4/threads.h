#include"q.h"
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

extern TCB_t * Q;



void start_thread(void (*function)(void))
{
	int stack_size = 8192;
	void *stack = malloc(stack_size);
	TCB_t *tcb = (TCB_t *) malloc(sizeof(TCB_t));
	init_TCB(tcb,function,stack,stack_size);
	AddQ(Q,tcb);
}


void run()
{
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, (Q->next->context));  // start the first thread
    
}


void yield() // similar to run
{
	ucontext_t* parent;     // get a place to store the main context, for faking
	parent = (ucontext_t *)malloc(sizeof(ucontext_t));
	getcontext(parent);   // magic sauce
	Q->next->context = parent;
	RotateQ(Q);
	swapcontext(parent, (Q->next->context));



}
