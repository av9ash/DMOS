
#include "msgs.h"

int a[] = {0,1,2,3,4};
TCB_t * Q;

void client()
{
while(1){
  P(&p[99].empty);
  int a[10];
  int i=0;
  printf("\nClient 0: Sending \n");
  for(i=0;i<10;i++) { 
  a[i]=i;
  printf("%d\t", a[i]); 
  }
  printf("\n");

  send(&p[99], a,99);
  printf("\n");
  printf("Client 0: Send success\n");
  sleep(1);
  V(&p[99].full);
  P(&p[0].full);
  int b[10];
  receive(&p[0],b,0);
  printf("\nClient 0: Receive success\n");
  sleep(1);
  V(&p[0].empty);
  printf("*******************************************************************\n");
}
}

void client1()
{
while(1){
  P(&p[99].empty);
  int a[10];
  int i=0;
  printf("\nClient 1: Sending \n");
  for(i=0;i<10;i++) { 
  a[i]=i+20;
  printf("%d\t", a[i]); 
  }
  printf("\n");

  send(&p[99], a,99);
  printf("Client 1: Send success\n");
  sleep(1);
  V(&p[99].full);
  P(&p[0].full);
  int b[10];
  receive(&p[0],b,0);
  printf("Client 1: Receive \n");
  for(i=0;i<10;i++)
  printf("%d\t", b[i]);
  printf("\nClient 1: Receive success\n");
  sleep(1);
  V(&p[0].empty);
  printf("*******************************************************************\n");
}
}

void server()
{
while(1){
  P(&p[99].full);
  printf("Server: Receiving \n");
  int a[10];
  receive(&p[99],a,99);
  int i=0;
 
  for(i=0;i<10;i++)
  printf("%d\t", a[i]);
  printf("\nServer: Receive Success \n");
  sleep(1);
  V(&p[99].empty);
  //yield();
  printf("server 0 started waiting for port 0\n");
  P(&p[0].empty);
  printf("Server: Sending \n");
  for(i=0;i<10;i++) {
  a[i]+=10;
  printf("%d\t", a[i]);
  }
  printf("\n");
  
  send(&p[0], a,0);
  for(i=0;i<10;i++)
  //printf("value of index %d",p[0].in]);
  printf("%d\t", p[0].msgs[p[0].in-1][i]);
  printf("\n");
  printf("Server: Send success");
  sleep(1);
  V(&p[0].full);
  //yield();
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



	
