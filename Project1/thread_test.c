/* 
Author: Nitesh Kedia,Tejas M U 
CSE 531 – Distributed and Multiprocessor Operating Systems, Fall 2014
Project #1: Allow a program to run, with multiple threads, using NON-preemptive scheduling
*/

#include"threads.h"

TCB_t * Q;

void func1()
{
	printf("function  1 running...\n");
	int i;
	for(i=1;;i++){
		printf("%d\n",i);
		sleep(1);
		if(i==10){
			printf("function1  yielding ....\n");
			yield();
		}
		//yield on some condition
	} 
}

void func2()
{
        printf("function  2 running...\n");
        int i;
        for(i=1;;i++){
                printf("%d\n",i);
                sleep(1);
                if(i==10){
                        printf("function2  yielding ....\n");
                        yield();
                }
                //yield on some condition
        }
}
void func3()
{
        printf("function  3 running...\n");
        int i;
        for(i=1;;i++){
                printf("%d\n",i);
                sleep(1);
                if(i==10){
                        printf("function3  yielding ....\n");
                        yield();
                }
                //yield on some condition
        }
}


void main()
{
	InitQ(&Q);
	void (*fun1)();
	fun1 = &func1;
	start_thread(fun1);
	void (*fun2)();
        fun2 = &func2;
	start_thread(fun2);
	void (*fun3)();
        fun3 = &func3;
	start_thread(fun3);
	run();
}
