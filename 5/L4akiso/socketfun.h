int server_tcp_socket(char *hn, int port)
{
	struct sockaddr_in sn;
	int s;
	struct hostent *he;
	if(!(he=gethostbyname(hn)))
	{
		printf("gethostbyname()\n");
		exit(1);
	}
	bzero((char *)&sn,sizeof(sn));
	sn.sin_family=AF_INET;
	sn.sin_port=htons((short)port);
	sn.sin_addr=*(struct in_addr *)(he->h_addr_list[0]);
	if((s=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("bind()");
		exit(1);
	}
	printf("STS success s=%d;\n",s);
	return s;
}

int accept_tcp_connection(int s)
{
	printf("begin accepting\n");
	struct sockaddr_in sn;
	socklen_t l = sizeof(sn);
	int x;
	sn.sin_family=AF_INET;
	if(listen(s,50)==-1)
	{
		perror("listen()");
		exit(1);
	}
	x=accept(s,(struct sockaddr*)&sn,(socklen_t *)&l);
	printf("x=%d\n",x);
	if(x==-1)
	{
		perror("accept()");
		exit(1);
	}
	return x;
}

int request_tcp_connection(char *hn, int port)
{
	printf("begin sending request %s %d\n",hn,port);
	struct sockaddr_in sn;
	int s,ok;
	struct hostent *he;
	if(!(he=gethostbyname(hn)))
	{
		printf("gethostbyname()\n");
		exit(1);
	}
	//else { printf("get host by name=%d",he);}
	ok=0;
	while(!ok)
	{
		sn.sin_family=AF_INET;
		sn.sin_port=htons((unsigned short) port);
		sn.sin_addr.s_addr = *(uint32_t *)(he->h_addr_list[0]);
		if((s=socket(AF_INET,SOCK_STREAM,0))==-1)
		{
			printf("socket()");
			exit(1);
		}
		printf("Wywołuję connect(), s=%d\n",s);
		ok=(  connect( s,(struct sockaddr *)&sn, sizeof(sn) )!=-1  );
		if(!ok) { sleep(1);} 
	}
	return s;
}


int readwrite(int in, int out)
{
	char s[1024];
	int i=0;
	while(read(in,s+i,1)!=0)
	{
		if(s[i]=='\n')
		{
			write(out,s,i+1);
			return i+1;
		}
		i++;
	}
	return 0;
}



















