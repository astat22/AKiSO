#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t zajmij_wiersz=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ctc=PTHREAD_COND_INITIALIZER; 
int currentRow=0;
int id=0;
int k,m,n,w;
int ** A;
int ** B;
int ** C;
int mod=2;


void *prod()
{
	int workingRow,i,j,myId=id++;
	while(currentRow<k) //warunek: doszliśmy do ostatniego wiersza w macierzy wynikowej
	{
		pthread_mutex_lock(&zajmij_wiersz);
		workingRow=currentRow;
		currentRow++;
		pthread_mutex_unlock(&zajmij_wiersz);//zwiększyłem bieżący wiersz, więc mogę zwolnić
		if(currentRow<=k)
		{
		printf("%d zajmuje wiersz %d\n",myId,workingRow);
		for(i=0;i<n;i++)
			for(j=0;j<m;j++)
			{	
				C[workingRow][i]+=A[workingRow][j]*B[j][i];
			}
		}
	}
}

int main(int argc, char *argv)
{
	srand(time(NULL));
	int i,j;
	printf("Liczba wierszy pierwszej macierzy: ");
	scanf("%d",&k);
	printf("Liczba kolumn pierwszej macierzy: ");
	scanf("%d",&m);
	printf("Liczba kolumn drugiej macierzy: ");
	scanf("%d",&n);
	printf("Liczba wątków: ");
	scanf("%d",&w);
	if(w>k)
	{
		w=k;
		printf("Liczba wątków jest większa niż liczba wierszy do obsłużenia. Ustawiam liczbę wątków na %d.\n",k);
	}
//inicjalizowanie macierzy
	A = malloc(sizeof(int *) * k); //[k][m];
	B = malloc(sizeof(int *) * m);//[m][n];
	C=malloc(sizeof(int *) * k);//[k][n];
	for(i=0;i<k;i++)
	{
		A[i]=malloc(sizeof(int *) * m);
		C[i]=malloc(sizeof(int *) * n);
	}
	for(i=0;i<m;i++)
	{
		B[i]=malloc(sizeof(int *) * n);
	}
//wypełnianie macierzy losowymi wartościami
	for(i=0;i<k;i++)
		for(j=0;j<m;j++)
		{
			A[i][j]=rand()%2;
			B[i][j]=rand()%2;
			C[i][j]=0;
		}
//tworzenie wątków
	pthread_t threads[w];
	for(i=0;i<w;i++)
	{
		pthread_create(&threads[i],NULL,prod,NULL);
	}	
	for(i=0;i<w;i++)
	{
		pthread_join(threads[i],NULL);
	}
//wypisywanie macierzy
	for(i=0;i<k;i++)
	{
		for(j=0;j<m;j++)
			printf("%d ",A[i][j]);
		printf("\n");	
	}
	printf("\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
			printf("%d ",B[i][j]);
		printf("\n");	
	}
	printf("\n");
	for(i=0;i<k;i++)
	{
		for(j=0;j<n;j++)
			printf("%d ",C[i][j]);
		printf("\n");	
	}
	printf("\n");
	return 0;
}
