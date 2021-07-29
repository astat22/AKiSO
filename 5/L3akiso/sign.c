#include <signal.h>
#include <stdio.h>


void sigcatch(int sign)
{
      signal(sign,sigint);
      printf("Otrzymano sygnał %d\n", sign);
}

int main(void)
{
   int i,j,k;
   for(k=1;k<65;k++)
      signal(k,sigcatch);
   for(i=0;i<200000;i++)
      for(j=0;j<400000;j++);
}

//uruchamiam
//w drugim terminalu: ps -a
//odczytuję pid
//kill -sygnał pid
//nie działa dla sygnał=9
