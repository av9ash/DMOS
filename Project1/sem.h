#include <malloc.h> 
#include "threads.h"
typedef struct semap{
     TCB_t *queue;
     int count;
} semaphore_t;

extern TCB_t * Q;
void init_sem(semaphore_t *s, int i)
{  
	s->count = i;
	InitQ(&s->queue);
}


/*
 * The P routine decrements the semaphore, and if the value is less than
 * zero then blocks the process 
 */
void P(semaphore_t *sem)
{    
	sem->count--;
	if (sem->count < 0) 
	{
		TCB_t *p=DelQ(Q);

		AddQ(sem->queue,p);
		if(Q->next!=Q&&p!=Q)
		{ 
			swapcontext(&(p->context),&(Q->next->context));
		}
	}
}


/*
 * The V routine increments the semaphore, and if the value is 0 or
 * negative, wakes up a process and yields
 */

void V(semaphore_t *sem)
{    
	sem->count++;
	if (sem->count <= 0)
	{
		if(sem->queue->next!=sem->queue)
		{
			TCB_t *temp = DelQ(sem->queue);
			AddQ(Q,temp);
		}
		yield();
	}
}


