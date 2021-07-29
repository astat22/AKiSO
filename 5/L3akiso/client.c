//przez select

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <pthread.h>
#include <poll.h>
#include "messtr.h"

int myid, fd[2];
struct message *mmes;
//char line[1024];
int statwypisz;
pthread_t w2,w1;
pthread_mutex_t blokada=PTHREAD_MUTEX_INITIALIZER;

void *fw1()
{
	struct timeval tv;
	tv.tv_sec=1;
	tv.tv_usec=0;
	fd_set inputset;
	FD_ZERO(&inputset);
	FD_SET(0,&inputset);
	int rfr=0;

	char line[1024];
	int nadawca =0;
	int buforPelen=0;
	printf("Rozpoczynam nasłuch\n");
	while(1)
	{
		if(mmes->status!=NOWA)
			;
		else if(mmes->clients[myid]==1)
		{
			while(mmes->clients[nadawca]!=2)
				nadawca++;
			printf("Klient %d: %s\n",nadawca, mmes->mes);
			fflush(stdout);
			//strcpy(line,mmes->mes); statwypisz=1;
			mmes->zostalo--;
			mmes->clients[myid]=0;
			nadawca=0;
		}
		/*rfr=select(1,&inputset,NULL,NULL,&tv);
		buforPelen=read(0,line,1024);
		if(mmes->status==CZEKAM && buforPelen)
		{
			int nadaj;
			mmes->status=ZAJETA;
			strcpy(line,(mmes->mes));
			mmes->zostalo=mmes->zostalo+mmes->razem;
			for(nadaj=0;nadaj<mmes->razem;nadaj++)
				mmes->clients[nadaj]=1;
			mmes->clients[myid]=2;
			printf("Napisalem: %s %s\n",line, mmes->mes);
			mmes->status=NOWA;
			buforPelen=0;
		}*/
	}
}

void *fw2()
{
	char line[1024];
	int nadaj=0,num_readable;
	fd_set readfds;
	//struct pollfd mypoll = {STDIN_FILENO, POLLIN|POLLPRI};
	struct timeval tv;
	int fd_stdin=fileno(stdin);
	//pthread_mutex_init();
	while(1)
	{
		//pthread_mutex_lock(&blokada);
		//fflush(stdin); open(0);
		fgets(line,1024,stdin);
		//read(STDIN_FILENO,line,3);
		//line[3]='\0';
		pthread_mutex_unlock(&blokada);
		while(mmes->status!=CZEKAM);
		mmes->status=ZAJETA;
		strcpy(line,(mmes->mes));
		mmes->zostalo=mmes->zostalo+mmes->razem;
		for(nadaj=0;nadaj<mmes->razem;nadaj++)
			mmes->clients[nadaj]=1;
		mmes->clients[myid]=2;
		printf("Napisalem: %s %s\n",line, mmes->mes);
		mmes->status=NOWA;
	}
}

int main(int argc,char *argv[])
{
	printf("Klient: Startuję.\n");
	key_t mkey=ftok(".",'x');
	int mshmid;
	mshmid=shmget(mkey,sizeof(struct message) ,0666); 
	if(mshmid<0)
	{
		printf("Klient: błąd shmget\n"); exit(1);
	}
	mmes = (struct message *) shmat(mshmid,NULL,0);
	myid=mmes->razem++;//dołącza nowy użytkownik
	printf("Klient %d podłączył się do pamięci współdzielonej\n",myid);
//wątek pisania

	/*if(pthread_create(&w2,NULL,fw2,NULL)!=0)
	{
		perror("pthread_create");
		exit(1);
	}*/
//wątek nasłuchu //i pisania
	if(pthread_create(&w1,NULL,fw1,NULL)!=0)
	{
		perror("pthread_create");
		exit(1);
	}
	//pthread_setspecific(stdin_key,NULL);

	
	int nadaj=0,num_readable;
	
	while(1)
	{
		char line[1024];
		//if(!fgets(line,1024,stdin)) return 0;
		//printf("Wpisz coś: ");
		gets(line);
		//printf("Pobrano %s",line);
		/*FD_ZERO(&readfds);
		FD_SET(fileno(stdin),&readfds);
		tv.tv_sec=10;
		tv.tv_usec=0;	
		fflush(stdout);
		line=select(fd_stdin+1,&readfds,NULL,NULL,&tv);
		if(num_readable==0) break;
		//alarm(5);
		gets(line);*/
		while(mmes->status!=CZEKAM);
		mmes->status=ZAJETA;
		strcpy(mmes->mes,line);
		mmes->zostalo=mmes->zostalo+mmes->razem;
		for(nadaj=0;nadaj<mmes->razem;nadaj++)
			mmes->clients[nadaj]=1;
		mmes->clients[myid]=2;
		//printf("Napisalem: %s %s\n",line, mmes->mes);
		mmes->status=NOWA;
	}
	pthread_join(w1,NULL);
	//pthread_join(w2,NULL);
	return 0;
}
