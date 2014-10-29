  /* 
Participants:
============
1) Vishal Ruhela  
2) Sravya Narala

**************************
Used Strategy - 2
**************************

*/

#include "msgs.h"

int serverCount=0; //create a global counter

/* listening on port 5 */
void server_5()
    {
    int id = ++serverCount;  //increament the global counter
    int *rcv;
    while(1)
        {
        rcv = receive(5);    //try to listen on port 5, if element is not available then block untill the item is avialable
        printf("\tSERVER #%d DONE on port #5\n", id);
        sleep(1);
        yield();
        }
    }

/*
void server_5_2()
    {
    int id = ++serverCount;  //increament the global counter
    int *rcv;
    while(1)
        {
        rcv = receive(5);    //try to listen on port 5, if element is not available then block untill the item is avialable
        printf("\tSERVER #%d DONE on port #5\n", id);
        sleep(1);
        yield();
        }
    }*/

// listening on port 20 
void server_20()
    {
    int id = ++serverCount;
    int *rcv;
    while(1)
        {
        rcv = receive(20);
        printf("\tSERVER #%d DONE on port #%d \n", id,20);
        sleep(1);
        yield();
        }
    }

// listening on port 31 
void server_31()
    {
    int id = ++serverCount;
    int *rcv;
    while(1)
        {
        rcv = receive(31);
        printf("\tSERVER #%d DONE on port #%d\n", id,31);
        sleep(1);
        yield();
        }
    }



// listening on port 51 
void server_51()
    {
    int id = ++serverCount;
    int *rcv;
    while(1)
        {
        rcv = receive(51);
        printf("\tSERVER #%d DONE on port #%d\n", id,51);
        sleep(1);
        yield();
        }
    }


/* sending on port 5 */
void client_5()
    {
    int msg[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int id = 1;
    while (1)
        {
        message m;
        m.message = &msg[0];
        send(5, m);
        printf("\tCLIENT #%d DONE on port #%d\n", id, 5);
        sleep(1);
        yield();
        }
    }



// sending on port 20 
void client_20()
    {
    int msg[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    int id = 3;
    while(1)    
        {
        message m;
        m.message = &msg[0];
        send(20, m);
        printf("\tCLIENT #%d DONE on port 20 \n", id);
        
        sleep(1);
        yield();
        }
    }

//sending on port 51 
void client_51()
    {
    int msg[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    int id = 4;
    while(1)    
        {
        message m;
        m.message = &msg[0];
        send(51, m);
        printf("\tCLIENT #%d DONE on port 51\n", id);
        
        sleep(1);
        yield();
        }
    }

// sending on port 31 
void client_31()
    {
    int msg[] = { 3, 3, 6, 6, 6, 6, 6, 6, 6, 6};
    int id = 5;
    while(1)    
        {
        message m;
        m.message = &msg[0];
        send(31, m);
        printf("\tCLIENT #%d DONE on port 31 \n", id);
        
        sleep(1);
        yield();
        }
    }

void systemIdle()
    {   
    while(1) { sleep(1); yield();}
    }

void main()
    {
    
    init_ports(); 

    start_thread(systemIdle);
  
    /* 3 individual threads listening on 10, 20, 30 each */
    start_thread(server_5);	
	//start_thread(server_5_2);	
   start_thread(server_20);
    start_thread(server_31);
	start_thread(server_51);	
    /* two threads sending on port 10, one on port 20 */
   start_thread(client_5);
   
   start_thread(client_20);
	start_thread(client_31);
	start_thread(client_51);    
run();

    while(1)
        { 
        sleep(1);
        }
    }
