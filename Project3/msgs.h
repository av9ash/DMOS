#include "sem.h"

typedef struct port 
{
	int msgs[10][10];
	int in, out;
	semaphore_t mutex, full, empty;
}PORT;

PORT p[100];


void init_port() 
{
	int i=0;
	for(i=0;i<100;i++)
	{
		/*p[i].mutex=CreateSem(1);
		p[i].full=CreateSem(0);
		p[i].empty=CreateSem(10);*/
		init_sem(&p[i].full,0);
		init_sem(&p[i].empty,10);
		init_sem(&p[i].mutex,1);
	}
}
	

void send(PORT *p, int *msg,int portnum)
{
    P(&p->mutex);
	int i=0;
    	
  	for(i=0;i<10;i++)
	{
		p->msgs[p->in][i] = msg[i];
    }

  	printf("Message sent to port %d at index: %d\n",portnum,p->in);
	p->in = ((p->in)+1)%10;
    V(&p->mutex);
}

void receive(PORT *p, int *msg,int portnum)
{
    P(&p->mutex);
	int i=0;
    //if(p->in==p->out)
  
	for(i=0;i<10;i++)
  	{
  		msg[i]=p->msgs[p->out][i];
  	}

  	printf("Message read from port %d at index: %d\n",portnum,p->out);
  	p->out = ((p->out)+1)%10;
    V(&p->mutex);
}
