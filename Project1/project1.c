/* Nitesh Kedia
   Tejas M U */

#include"threads.h"

TCB_t * Q;

func1()
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

func2()
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
}func3()
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


int main()
{
	initQ(&Q);
	start_thread(func1);
	start_thread(func2);
	start_thread(func3);
	run();
	return 0;
}
