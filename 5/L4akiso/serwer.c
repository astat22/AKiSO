//protokół: token 1. kto 2. do kogo 3. co
// login server "" - wyślij mi listę kontaktów
// server login LISTA_KONTAKÓW - przesyłam listę kontaktów
// login1 login2 wiadomość 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<netdb.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/time.h>
#include<netinet/in.h>
#include "socketfun.h"

typedef struct clList
{
   char *login;
   int id;
   struct clList *next;
} client;

int clients=0;

int main(int argc, char **argv)
{
	char *hn,tome[1024+256],*rec_adr,*test_adr, *tmmes,*listofClients;
	char *mes;
	int port,sock,fd,n;
	fd_set readfds,masterfds;
	client *first, *clientNode, *prev;
	if(argc!=3)
	{
		printf("minitalk hostname port\n");
		exit(1);
	}
	hn=argv[1];
	port=atoi(argv[2]);
	if(port<5000)
	{
		printf("port>5000\n");
		exit(1);
	}
	sock=server_tcp_socket(hn,port);
	fd=accept_tcp_connection(sock); //ciągle trzeba akceptować nowych
	//close(sock);
	FD_ZERO(&masterfds);
	FD_SET(0,&masterfds);
	FD_SET(fd,&masterfds);
	while(1)
	{

		memcpy(&readfds,&masterfds,sizeof(fd_set));
		if( select(fd+1,&readfds,NULL,NULL,NULL)<0)
		{
			perror("błąd - select");
			exit(1);
		}
		if(FD_ISSET(fd,&readfds))//otrzymałem wiadomość
		{
			n=read(fd,tome,1024+256);
			if(n==0)
			{
				close(0);
				close(fd);
				exit(1);
			}
			//formatowanie otrzymanej wiadomości
			rec_adr=strtok(tome,"\n"); //kto mi wysłał
			test_adr=strtok(NULL,"\n");
			tmmes=strtok(NULL,"\n");
			printf("%s\n",tome);
			if(strcmp("server",test_adr)==0)//jeśli to do serwera, to trzeba odesłać
			{
//dodawanie do listy klientów
				if(!clients)
				{
					first=malloc(sizeof(client));
					first->id=clients;
					clients++;
					strcpy(first->login,rec_adr);
					strcpy(listofClients,rec_adr);
					first->next=NULL;
					clientNode=first;
					printf("Nowy klient\n");
				}
				else
				{
					prev=clientNode;
					clientNode=malloc(sizeof(client));
					prev->next=clientNode;
					clientNode->id=clients++;
					strcpy(clientNode->login,rec_adr);
					clientNode->next=NULL;	
					printf("Nowy klient\n");
//wysyłanie listy zalogowanych użytkowników
					strcat(listofClients,"; ");
					strcat(listofClients,rec_adr);
					mes="server\n";
					strcat(mes,rec_adr);
					strcat(mes,"\n");
					write(fd,mes,strlen(mes));
				}
			}
		}
	}
}



















