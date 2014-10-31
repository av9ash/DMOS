/*******************************************************************/
/*	CSE 531 Distributed Multiprocessor Operating Systems	   */
/*	Project 2 : Implementing Semaphores			   */
/*	Group members: Nitesh Kedia,Tejas M U    		   */
/*******************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sem.h"

TCB_t * Q;
int readwritec = 0 , writewritec = 0 , readc = 0 , writec = 0, global_ID = 0;

semaphore_t read_sem,write_sem,mutex;

void reader_entry(int ID)
{

	printf("[reader: %d] Trying to read\n",ID);
	P(&mutex);
	if(writewritec > 0 || writec > 0)
	{
		printf("[reader: %d] blocking for writer\n", ID);
		//We then increment the read counter and let other
		//other process use this mutex
		readwritec++;
		V(&mutex);
		//Sleep on the read semaphore
		P(&read_sem);
		readwritec--;

	}
	readc++;
	if( readwritec > 0 )
		V(&read_sem);
	else{
		//printf("[reader: %d] Mutex Released\n",ID);
		V(&mutex);
		}
}

void reader_exit(int ID)
{
	P(&mutex);
	readc--;
	if(readc == 0 && writewritec > 0 )
	{
		//If the code enters here we have waiting writers
		//the write_sem is for these open writers
		V(&write_sem);
	}
	else
		V(&mutex);
	
}

void writer_entry(int ID)
{
	printf("\t\t\t\t\t\t\t\t\t[writer: %d] trying to write\n",ID);
	P(&mutex);
	if(readc > 0 || writec > 0 )
	{
		printf("\t\t\t\t\t\t\t\t\t[writer: %d] blocking for others\n", ID);
		writewritec++;
		V(&mutex);
		P(&write_sem);
		writewritec--;
	}
	writewritec++;
	V(&mutex);
}

void writer_exit(int ID)
{
	P(&mutex);
	writec--;
	if(readwritec > 0)
		V(&read_sem);
	else if( writewritec > 0 )
		V(&write_sem);
	else
		V(&mutex);
}

void reader()
{
	//printf("Entering reader");
	int ID;
	P(&mutex);
	ID = global_ID++;
	 //printf("[reader: %d] changing ID: \n",ID);
	V(&mutex);
	while(1)
	{
		reader_entry(ID);
		printf("[reader: %d] READING\n",ID);
		sleep(1);
		reader_exit(ID);
	};

}

void writer()
{
	int ID;
	P(&mutex);
	ID = global_ID++;
	V(&mutex);
	while(1)
	{
		writer_entry(ID);
		printf("\t\t\t\t\t\t\t\t\t[writer: %d] WRITING!!\n ",ID);
		sleep(1);
		writer_exit(ID);
	};
}
int main()
{
	InitQ(&Q);
	init_sem(&mutex, 1);
	init_sem(&read_sem, 0);
	init_sem(&write_sem, 0);
	
	start_thread(reader);
	start_thread(reader);
	start_thread(reader);
	start_thread(reader);
	start_thread(reader);
	start_thread(writer);
	start_thread(writer);
	start_thread(reader);
	start_thread(reader);
	start_thread(writer);
	
	
	run();
}
