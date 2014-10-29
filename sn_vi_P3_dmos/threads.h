# include "q.h"
# include <malloc.h>
#include <pthread.h>

typedef struct ssnode
{
int n;
struct ssnode *next;
}snode;
snode *top=NULL;
void start_thread(void (*function)(void))
{
     //allocating a stack (via malloc) of a certain size (choose 8192)
     snode *sp=malloc(2048*(sizeof(snode)));
     //allocate a TCB (via malloc)
     TCB_t *tcb=malloc(sizeof(TCB_t));
     //call init_TCB with appropriate arguments
     init_TCB(tcb,function,sp,(2048*(sizeof(snode))));
     //call addQ to add this TCB into the “RunQ” which is a global header pointer
     AddQ(tcb);
}

void run()
{   // real code
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(head->context));  // start the first thread
}
void yield() // similar to run
{
   TCB_t *currentContext=head;//rotate the run Q
//	TCB_t *ele=delQ();
//	AddQ(ele);
	RotateQ();
   //swap the context, from previous thread to the thread pointed to by runQ
	swapcontext(&(currentContext->context),&(head->context));
}
