#define NOWA 1
#define ZAJETA 0
#define CZEKAM -1


struct message
{
	int status;
	int razem;
	int zostalo;
	char mes[1024];
	int clients[1024]; //0 - przeczytane 1 - czeka 2 - moja
};
