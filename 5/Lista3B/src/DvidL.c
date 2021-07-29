/*-------------------------------------
Definicja funkcji przegladajacej luki
Autor: Jacek Mucha
Data stworzenia pliku: 1 maja 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
---------------------------------------
zmienne wejscia:
        Lista2 ptr - lista lukow, z ktorej bedziemy odczytywac luki
        int U - zmienna kontrolna, czy wyswietlac dodatkowe informacje

wartosc zwracana:
        void

zmienne lokalne:
        
funkcje importowane:
        nic

obslugiwane wyjatki:
            -nie istnieja zadne luki
--------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "DvidL.h"
//#ifndef STRUCT_H
//   #define STRUCT_H
   #include "STRUCT.h"
//#endif

void vidL(Lista2 ptr, int U)
{
    if(ptr==NULL)
        printf("\nNie ma zadnych lukow\n");
    else
    {
        if(U==1)
            printf("\nIstnieja nastepujace luki: \n");
        AdresL pom;
        AdresW pomOd;
        AdresW pomDo;
        while(ptr!=NULL)
        {
            pom=ptr->adresL;
            pomOd=pom->Od;
            pomDo=pom->Do;
            printf("%s od %s do %s\n", pom->NazwaL, pomOd->NazwaW, pomDo->NazwaW);
            ptr=ptr->nastepny;
        }
    }
}
