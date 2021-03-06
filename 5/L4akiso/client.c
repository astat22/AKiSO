//Jacek Mucha
//11/12/2015
//na podstawie slajdów z wykładu
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

int receivedList=0; //czy otrzymałem już listę kontaktów

int main(int argc, char **argv)
{
	char *hn;
	char tmes[1024],mes[1024+256], adr[128],*login,tome[1024+256],*rec_adr,*test_adr, *tmmes;
	int port,sock,fd,n;
	fd_set readfds,masterfds;
	if(argc!=4)
	{
		printf("minitalk hostname port login\n");
		exit(1);
	}
	hn=argv[1];
	port=atoi(argv[2]);
	if(port<5000)
	{
		printf("port>5000\n");
		exit(1);
	}
	login=argv[3];
	printf("łączę %s %d %s\n",hn, port,login);
	fd=request_tcp_connection(hn,port);
	printf("Nawiązano połączenie\n");
	close(sock);
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
//##### Logowanie ######
		if(!receivedList)
		{
	//formatuję wiadomość do serwera: żądanie podania listy loginów
			strcpy(mes,login);
			strcat(mes,"\n");
			strcat(mes,login);
			strcat(mes,"\n");
			n=strlen(mes);
			write(fd,mes,n);
		}
//############# WYSYŁANIE #######################
		if(FD_ISSET(0,&readfds))//wysyłam wiadomość
		{
			//mes=NULL;
			n=read(0,adr,128); //czytam adres
			n=n+read(0,tmes,1024);	//czytam komunikat
			n=n+strlen(login);
			strcpy(mes,login);//formatowanie wiadomości do wysłania
			strcat(mes,"\n");
			strcat(mes,adr);
			strcat(mes,"\n");
			strcat(mes,tmes);
			if(n==0)
			{
				close(0);
				close(fd);
				exit(1);
			}
			else
			{
				write(fd,mes,n);
			}
		}
		else
		{
// ############### ODBIERANIE #####################
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
				if(strcmp(login,test_adr)==0)//jeśli to do mnie, to wyświetlę
				{
					if(strcmp("server",test_adr)!=0)
						printf("Wiadomość od %s:\n%s\n",rec_adr,tmmes);
					else //wiadomość od serwera
					{
						receivedList=1;
						printf("Zalogowani użytkownicy:\n%s\n",tmmes);
					}
				}
			}
		}
	}
}
