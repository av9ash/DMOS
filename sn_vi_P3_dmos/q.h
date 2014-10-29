#include<stdio.h>
#include<malloc.h>
#include "TCB.h"
/*struct TCB_t
{
	ucontext_t context;
      struct TCB_t *prev  ;
      struct TCB_t *next  ;
}*/
TCB_t *head=NULL;
TCB_t *tail=NULL;

void InitQ (TCB_t *p)
{
	p->next=head;
	p->prev=head;
    head=p;
	tail=p;
	head->prev=head;
	head->next=head;
}
void AddQ(TCB_t *p)
{
	p->next=head;
	p->prev=head;

	if(head==NULL)
	{
       InitQ(p); 
	}
	else
	{
	p->prev=tail;
	tail->next=p;
	p->next=head;
	head->prev=p;
	tail=p;
	
	}
}
 

TCB_t* delQ()
{
   TCB_t *temp1=head;
   if(head==NULL) 
   {
        TCB_t *t=NULL;
        return(t);
    }

  else if(head==tail) 
   { 
     temp1->context=head->context; 
      head->next=NULL;
      head->prev=NULL;    
      head=NULL; 
	tail=NULL;      
      return(temp1);
 } 
  else 
   {  
     temp1->context=head->context;
     head=head->next; 
     head->prev=tail;  
     tail->next=head; 
     return(temp1);
    }

}

void RotateQ()
  {
	if(head==NULL)
	{
	printf("No element to delte\n");
	}
else
{
TCB_t *ptr=delQ();
AddQ(ptr);
//head=head->next;
}
}
