#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <math.h>

void* BusyWork(void *t)
 {
    long i;
    long long result=1;
    for (i=0; i<*(long*)t; i++)
    {
       printf("Thread %lu running...\n",pthread_self());
       result+= pow(result,2);
    }
    printf("Thread %lu is ending. Result = %lld\n",pthread_self(), result);
    pthread_exit(NULL);
 }

int main (int argc, char *argv[])
 {
    if(argc<2){
	printf("incorrect arguments\nCorrect format:filename <num1> <num2>...\n");
	exit(0);	
    }    
    pthread_t thread[argc-1];
    long args[argc-1];
    //int rc;
    long t;
    void *status;

    /* Initialize and set thread detached attribute */
    
    for(t=0; t<argc-1; t++) {
       args[t]=atol(argv[t+1]);
       pthread_attr_t attr;
       pthread_attr_init(&attr);
       pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
       printf("Main: creating thread %lu\n", thread[t]);
       pthread_create(&thread[t], &attr, BusyWork, &args[t]);  
       }
    /* Free attribute and wait for the other threads */
    //pthread_attr_destroy(&attr);
    /*for(t=0; t<argc-1; t++) {
       pthread_join(thread[t], &status);
       printf("Main: completed join with thread %lu having a status of %ld\n",thread[t],(long)status);
       }*/
 
 printf("Main: program completed. Exiting.\n");
 pthread_exit(NULL);
 }

