#include <malloc.h> 
#include "threads.h"
typedef struct semap{
     TCB_t *queue;
     int count;
} semaphore_t;

void init_sem(semaphore_t *s, int i)
{   
    s->count = i;
    
s->queue = (TCB_t *)malloc(sizeof(TCB_t));
	s->queue=NULL;
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
        TCB_t *p=delQ();
        if(sem->queue==NULL)
          sem->queue=p;
        else
          {
             TCB_t *temp;
             for(temp=sem->queue;temp->next!=NULL;temp=temp->next);
             temp->next=p;
             p->next=NULL;
          }
        if(head!=NULL&&p!=NULL)
          { 
              swapcontext(&(p->context),&(head->context));
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
    if (sem->count <= 0) {
	//deleting the semQ head
      if(sem->queue!=NULL)
       {
        TCB_t *temp=sem->queue;
        sem->queue=sem->queue->next;
        AddQ(temp);
       }
    }
    yield();
}


