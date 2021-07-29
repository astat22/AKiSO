#include <stdio.h>

int main(int args, char *argv[])
{
	int i=1;
	for(i=1;i<257;i++)
	{
		printf("\e[38;5;%dm %d.qo nuqneH!\n",i,i);
	}
	for(i=0;i<8;i++)
	{
		printf("\e[%dmHello, World!\n",i+30);
		printf("\e[%dmHello, World!\n",i+90);
	}
	return 0;
}

