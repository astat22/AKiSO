/*-------------------------------------
Definicja funkcji usuwajacej luki
Autor: Jacek Mucha
Data stworzenia pliku: 30 kwietnia 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
---------------------------------------
zmienne wejscia:
        char *NazwaLu - identyfikator luku
        Lista2 ptr - lista lukow, z ktorej mamy usunac luk
        int M - zmienna kontrolna. czy wyswietlac dodatkowe informacje?

wartosc zwracana:
        Lista2 ptr - nowa lista lukow

zmienne lokalne:
        
funkcje importowane:
        int eqStr

obslugiwane wyjatki:
            -zadany luk nie istnieje
            -nie istnieje zaden luk
--------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "DdelL.h"
//#ifndef DEQSTR_H
//   #define DEQSTR_H 
   #include "DeqStr.h"
//#endif
//#ifndef STRUCT_H
//   #define STRUCT_H
   #include "STRUCT.h"
//#endif

Lista2 delL(char *NazwaLu, Lista2 ptr, int M)
{
    if(ptr!=NULL)
    {
        Lista2 pre;//poprzedni element listy
        Lista2 post;//nast\EApny element listy
        Lista2 hic;//aktualny element listy
        AdresL is;
        AdresW Od1;
        AdresW Do1;
        pre=NULL;
        hic=ptr;
        is=hic->adresL;
//Znajdz luk w Lista2
        while((hic!=NULL)&&(!eqStr(is->NazwaL,NazwaLu)))
        {
            pre=hic;
            hic=hic->nastepny;
            if(hic!=NULL)
                is=hic->adresL;
        }
        if(hic==NULL&&M==1)
            printf("\nNie ma takiego luku!\n");
        if(hic!=NULL)
        {
//Usuwanie informacji o luku w wezle, od ktorego luk wychodzi:
            Od1=is->Od;
            purLiW(Od1,hic,2);
//Usuwanie informacji o luku w wezle, do ktorego luk przyychodzi:
            Do1=is->Do;
            purLiW(Do1,hic,1);
//Usuwanie luku z Listy2 (listy lukow)
            post=hic->nastepny;
            if(pre==NULL)
            {
                ptr=post;
            }
            else
            {
                pre->nastepny=post;
            }
            free(hic);
        }
    }
    else
        printf("\nNie ma zadnych lukow, wiec nic nie moge usunac");
    return ptr;
}
