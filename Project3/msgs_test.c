/*******************************************************************/
/*      CSE 531 Distributed Multiprocessor Operating Systems       */
/*      Project 3 : Message passing via ports                      */
/*      Group members: Nitesh Kedia,Tejas M U                      */
/*******************************************************************/

#include "msgs.h"

int a[] = {0,1,2,3,4};
TCB_t * Q;

void printSend(int *a,int client,int clientId,int port) {
 int i =0;

 char c = ' ';
 if(client == 1) c ='C';
 else c ='S';

 printf("Sending... from %c%d on %d  :",c,clientId,port);
 for(i=0;i<10;i++) {
  a[i] = i+(clientId+1)*10;
  printf("%d ",a[i]);
 }
 printf("\n"); 
}

void printRecv(int *a,int client,int clientId,int port) {
 int i = 0 ;
 char c = ' ';
 if(client == 1) c ='C';
 else c ='S';

 printf("\t\t\t\t\t\t\tReceived... by %c%d on %d  :",c,clientId,port);
 for(i=0;i<10;i++) {
  printf("%d ",a[i]);
}
 printf("\n");
}

void client()
{
while(1){
  P(&p[99].empty);
  int a[10];
  printSend(a,1,0,99);
  send(&p[99], a,99);
  printf("Client 0: Send success\n");
  sleep(1);
  V(&p[99].full);
  P(&p[0].full);
  int b[10];
  receive(&p[0],b,0);
  printRecv(b,1,0,0);
  printf("\n");
  sleep(1);
  V(&p[0].empty);
  
}
}

void client1()
{
while(1){
  P(&p[99].empty);
  int a[10];
  printSend(a,1,1,99);
  send(&p[99], a,99);
  printf("Client 1: Send success\n");
  sleep(1);
  V(&p[99].full);
  P(&p[0].full);
  int b[10];
  receive(&p[0],b,0);
  printRecv(b,1,1,0);
  sleep(1);
  V(&p[0].empty);
}
}

void server()
{
while(1){
  P(&p[99].full);
  int a[10];
  receive(&p[99],a,99);
  printRecv(a,0,0,99);
  int i=0;
  sleep(1);
  V(&p[99].empty);
  P(&p[0].empty);
  printSend(a,0,0,0);
  send(&p[0], a,0);
  printf("Server 0: Send success\n");
  sleep(1);
  V(&p[0].full);
}
}


//-------------------------------------------------------

int main()
{   //int a[] = {0,1,2,3,4};
	InitQ(&Q);
   p[0].in=0; p[0].out=0;
   p[20].in=0; p[20].out=0;
   p[99].in=0; p[99].out=0;
    init_port();
	printf("\nCreating a client\n");
    start_thread(client);
	printf("\nCreating a client\n");
    start_thread(client1);
	printf("\nCreating a server\n");
    start_thread(server);
	run();
    while (1) sleep(1);
}   



	
