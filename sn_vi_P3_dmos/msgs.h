#include "Sem.h"

typedef struct msg
{
	int *message;
        int count;
} message;

typedef struct port
{
	int number;
    	int in;
    	int out;
    	semaphore_t full;
    	semaphore_t empty;
    	semaphore_t mutex;
	message messageQ [10];
} PORT;
PORT ports [100]; 

void init_ports()
    {
    int i;

    for (i = 0; i < 100; i++)
        {
	
        ports[i].number = i;
        ports[i].in = 0;
        ports[i].out = 0;
	
	init_sem(&ports[i].full,10);
	
	init_sem(&ports[i].empty,0);
        init_sem(&ports[i].mutex,1);       
 	
        }
    }

void init ()
    {
    init_ports();
    }

void send (int p, message m)
    {
    P(&(ports[p].full)); 
      P(&(ports[p].mutex)); 

         printf("Sending msg to Port #%d and its queue position is #%d\n", p, ports[p].in);

         ports[p].messageQ[ports[p].in] = m;
         ports[p].in++;
         if (ports[p].in == 10)
             {
             ports[p].in = 0;
             }  
	
      V(&(ports[p].mutex)); 
    V(&(ports[p].empty));    
    }

int * receive (int p)
    {
     P(&(ports[p].empty));
      P(&(ports[p].mutex));

            printf ("Received message on Port#%d and its queue position is #%d\n", p, ports[p].out);
	int* msg = ports[p].messageQ[ports[p].out].message;
            ports[p].out++;
            if (ports[p].out == 10)
			   {
			   ports[p].out = 0;
		       }

      V(&(ports[p].mutex));
    V(&(ports[p].full));
}
