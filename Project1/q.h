#include"TCB.h"
#include<stdio.h>
#include<stdlib.h>

initQ(TCB_t ** head)
{
	*head=(TCB_t *)malloc(1*sizeof(TCB_t));
	(*head)->next = *head; (*head)-> prev = *head;
	printf("Head Node:%p",*head);
}

enq( TCB_t * head,TCB_t * tcb)
{
	//TCB_t * new_node = malloc(sizeof(TCB_t));
	//new_node-> data = num;
	TCB_t *cur = head;
	while(cur->next!=head)
		cur=cur->next;
	cur -> next = tcb;
	tcb-> prev = cur;
	tcb->next = head;
	head-> prev = tcb;
	//printf("New TCB inserted at address%p with u_context address %p:",tcb,tcb->context);
	printf("New node prev address:%p\n",tcb->prev);	
	printf("New node address:%p\n",tcb);
	printf("New node next address:%p\n",tcb->next);
}

 TCB_t * deq( TCB_t * head)
{
	TCB_t *cur = head-> next;
	TCB_t *cur_next = cur->next;
	head->next = cur_next;
	cur_next->prev=head;
	return cur;
}




void display( TCB_t * head)
{
	TCB_t * cur = head;
	while(cur->next!=head){
		cur=cur->next;
		printf("%p -> ", cur);
	}
}

void rotate( TCB_t * head)
{
	if(head->next->next !=head && head->next !=head){
		TCB_t * cur = head->next;
		while(cur->next != head){
			cur = cur->next;
		}
		TCB_t * ret = deq(head);
		cur->next = ret;
		ret->prev = cur;
		ret->next = head;
		head->prev = ret;
		display(head);
	}
}
	

/*void main()
{

	TCB_t * head; 
		
	int no, ch,e;
	TCB_t * ret;
	printf("\n 1 - Enque");
	printf("\n 2 - Display");
	printf("\n 3 -dequeque");
	printf("\n 4 - rotate");
	initQ(&head);
	printf("head data : %d ",head->data);
	while (1)
	{
		printf("\n Enter choice : ");
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:
			printf("Enter data : ");
			scanf("%d", &no);
			enq(head,no);
			break;
		case 2:
			display(head);
			break;
		case 3:
			ret = deq(head);
			printf("%d deleted",ret->data);
			break;
		case 4:
			rotate(head);
			break;
		default:
			exit(0);
		}
	}
}*/
