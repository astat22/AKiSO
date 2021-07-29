#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<netdb.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include<netinet/in.h>
#include "socketfun.h"

int main(int argc, char **argv)
{
	//printf("%d",sizeof(int));
	char *hn;
	hn="localhost";
	int port=7844,sock,fd;
	if(argv[1][0]=='s')
	{
		sock=server_tcp_socket(hn,port);
		fd=accept_tcp_connection(sock);
	}
	else
	{
		fd=request_tcp_connection(hn,port);
	}
	printf("Nawiązano połączenie. Klient powinien zacząć rozmowę.\n");
	if(argv[1][0]=='s')
		if(readwrite(fd,1)==0) exit(0);
	while(1)
	{
		if(readwrite(0,fd)==0) exit(0);
		if(readwrite(fd,1)==0) exit(0);
	}
}
