#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

long long sum=0;

void* summer(void *arg){
	long long *temp=(long long*)arg;
	long long no=*temp;
	for(long long i=0;i<no;++i)
		sum+=i;
	printf("lets see who is fast %lld\n\n",sum);
	pthread_exit(0);
}

int main(int argc,char **arg){

	if(argc<2){
		printf("incorrect arguments\n");
		exit(0);	
	}
	printf("\n%s\n",arg[1]);
	long long int a=atoll(arg[1]);

	//thread id
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,summer,&a);
	//wait until thread is done its work
	pthread_join(tid,NULL);
	printf("sum is %lld\n\n",sum);
return 0;
}
