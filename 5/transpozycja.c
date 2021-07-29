#include<stdio.h>
#include<time.h>
#include <sys/time.h> 

int main(int argc, char *argv)
{
	srand(time(NULL));
	int n=900,i,j,k;
	short A[n][n], B[n][n], C[n][n], D[n][n];
//generowanie macierzy losowych
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			A[i][j]=rand();
			B[j][i]=rand();
			C[i][j]=0;
			//D[i][j]=0;
		}
	}
//inicjalizacja stopera
printf("Bez transpozycji: ");
	struct timeval t1, t2;
    double elapsedTime;
    gettimeofday(&t1, NULL);
//bez transpozycji
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			for(k=0;k<n;k++)
				C[i][j]+=A[i][k]*B[k][j];
   gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    printf("%lf\n", elapsedTime);
//z transpozycją
	short tmp[n][n];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			C[i][j]=0;
		}
	}
    gettimeofday(&t1, NULL);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			tmp[i][j]=B[j][i];
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			for(k=0;k<n;k++)
				C[i][j]+=A[i][k]*tmp[j][k];	
   gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    printf("Z transpozycją: %lf\n", elapsedTime);
}

























