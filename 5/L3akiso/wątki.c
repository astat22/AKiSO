//gcc -pthread ./wątki.c -o wątki

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void *fw2();

void *fw1()
{
	printf("Wątek 1: Zaczynam pracę.\n");
	pthread_t w2;
	void *status2;
	printf("Tworzenie nowego wątku.\n");
	if(pthread_create(&w2,NULL,fw2,NULL)!=0)
	{
		perror("pthread_create");
		exit(1);
	}
	printf("Wątek 1: Sygnał wysłany. Idę spać.\n");
	sleep(3);
	printf("Wątek 1: Wstałem, kończę pracę.\n");
	return NULL;
}

void *fw2()
{
	printf("Wątek 2: Zaczynam pracę.\n");
	sleep(1);
	printf("Wątek 2: Kończę pracę.\n");
	return NULL;
}

int main(void)
{
	printf("Program: zaczynam pracę.\n");
	pthread_t w1;
	void *status1;
	if(pthread_create(&w1,NULL,fw1,NULL)!=0)
	{
		perror("pthread_create");
		exit(1);
	}
	sleep(7);
	printf("Program: kończę pracę.\n");
	return 0;
}
