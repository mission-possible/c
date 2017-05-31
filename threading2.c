#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

//long long sum=0;
struct threads_info{
	long long int limit;
	long long int buffer;
};

void* summer(void *arg){
	struct threads_info *temp=(struct threads_info*)arg;
	//long long no=*temp;
	long long sum=0;
	for(long long i=0;i<temp->limit;++i){
		printf("i m thread_id=%lu\n",pthread_self());
		sum+=i;
	}
	temp->buffer=sum;
	//printf("\n\ni m thread_id=%lu\tresult= %lld\n\n",pthread_self(),sum);
	pthread_exit(0);
}

int main(int argc,char **arg){

	if(argc<2){
		printf("incorrect arguments\nCorrect format:filename <num1> <num2>...\n");
		exit(0);	
	}
	printf("\n%s\n",arg[1]);
	struct threads_info args[argc-1];

	//thread id
	pthread_t tid[argc-1];
	for(int i=0;i<argc-1;++i){
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	args[i].limit=atoll(arg[i+1]);
	pthread_create(&tid[i],&attr,summer,&args[i]);
	}
	for(int i=0;i<argc-1;++i){
	//wait until thread is done its work
	pthread_join(tid[i],NULL);
	printf("\nsum is %lld\n\n",args[i].buffer);
	}
return 0;
}
