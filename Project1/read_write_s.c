// (c) Partha Dasgupta 2009
// permission to use and distribute granted.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sem.h"

TCB_t *Q;

semaphore_t r_sem, w_sem, mutex;
int rwc = 0, wwc = 0, rc = 0, wc = 0, global_ID=0;

void reader_entry(int ID)
{
	printf("[reader: #%d]\ttrying to read\n", ID);
	P(&mutex);
	if (wwc > 0 || wc > 0) {
	    printf("[reader: #%d]\tblocking for writer\n", ID);
	    rwc++;		// increment waiting reader count.
	    V(&mutex);		// let other processes use the mutex.
	    P(&r_sem);		// sleep on r_sem
	    rwc--;		// program now has mutex and r_sem, go
			        // into CS.
	}
	rc++;
	if (rwc > 0)
	    V(&r_sem);
	else
	    V(&mutex);		// let other processes use the mutex.
}

void reader_exit(int ID)
{
	P(&mutex);
	rc--;			// i'm no longer a reader
	if (rc == 0 && wwc > 0) {
	    // if was the last reader, and there are waiting writers, open 
	    // the w_sem door for them.
	    V(&w_sem);
	} else
	    V(&mutex);

}

void writer_entry(int ID)
{
	printf("\t\t\t\t[writer: #%d]\ttrying to write\n", ID);
	P(&mutex);
	if (rc > 0 || wc > 0) {
	    printf("\t\t\t\t[writer: #%d] blocking for others\n",ID);
	    wwc++;		// increment waiting writers
	    V(&mutex);		// let go of the mutex, since i'll be
	    // blocked
	    P(&w_sem);		// wait in my line, when i wake up i DON'T 
		 	    	// need a P(mutex since i've been given it 
	    			// by the waking process.
	    wwc--;		// i'm no longer waiting
	}
	wc++;			// increment writers
	V(&mutex);		// let go of the mutex
}

void writer_exit(int ID)
{
	P(&mutex);
	wc--;
	if (rwc > 0) {		// first, i let all the readers go.
	    V(&r_sem);
	} else if (wwc > 0) {	// then i let another writer go
	    V(&w_sem);
	} else {		// lastly, i give up the mutex
	    V(&mutex);
	}
}



void reader(void)
{ 
  int ID;
  P(&mutex); ID = global_ID++; V(&mutex);
  while(1){
	reader_entry(ID);
	printf
	    ("[reader #%d]\t****READING****\n", ID);
	sleep(1);
	reader_exit(ID);
	yield();
  };
}

void writer(void)
{
  int ID;
  P(&mutex); ID = global_ID++; V(&mutex);
  while(1){
 	writer_entry(ID);
	printf
	    ("\t\t\t\t[writer: #%d]\t&&&WRITING!&&&\n", ID);
	sleep(1);
	writer_exit(ID);
	yield();
  };
}



//-------------------------------------------------------

int main()
{
	InitQ(&Q);
    init_sem(&mutex, 1);
    init_sem(&r_sem, 0);
    init_sem(&w_sem, 0);

	void (*fun1)(void);
        fun1 = &reader;
        void (*fun2)(void);
        fun2 = &writer;

    start_thread(fun2);
    start_thread(fun2);
    start_thread(fun2);
    start_thread(fun1);
    start_thread(fun1);
    run();
    while (1) sleep(1);
}   




