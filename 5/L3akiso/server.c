#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "messtr.h"



int main(int argc,char *argv[])
{
	printf("Serwer: Startuję.\n");
	key_t mkey=ftok(".",'x');
	struct message *mmes;
	int mshmid,i;
	mshmid=shmget(mkey,sizeof(struct message) ,IPC_CREAT | 0666); //identyfikator segmentu pamięci współdzielonej
	if(mshmid<0)
	{
		printf("Serwer: błąd shmget\n"); exit(1);
	}
	mmes = (struct message *) shmat(mshmid,NULL,0); //wskaźnik do segmentu danych, gdzie dowiązana jest pw
	mmes->status=CZEKAM;
	mmes->zostalo=0;
	mmes->razem=0;
	for(i=0;i<1024;i++) mmes->clients[i]=0;
//kontrola
	int nadawca=0;
	while(1)
	{
		printf("stat=%d zostalo=%d razem=%d mes=%s ",mmes->status, mmes->zostalo,mmes->razem,mmes->mes);
		for(nadawca=0;nadawca<mmes->razem;nadawca++) { printf("%d:%d ",nadawca,mmes->clients[nadawca]);}
		printf("\n");
		nadawca=0;
		if(mmes->zostalo==1 && mmes->status==NOWA)
		{
			mmes->status=ZAJETA;
			while(mmes->clients[nadawca]!=2)//wyzeruj nadawcę
				nadawca++;
			
			printf("Klient %d: %s",nadawca,mmes->mes);
			mmes->clients[nadawca]=0;
			mmes->zostalo--;
			mmes->status=CZEKAM;
		}
		sleep(1);
	}
	return 0;
}
