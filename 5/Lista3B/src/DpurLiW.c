/*-------------------------------------
Definicja funkcji usuwajacej informacje o luku z wezla
Autor: Jacek Mucha
Data stworzenia pliku: 30 kwietnia 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
---------------------------------------
zmienne wejscia:
        AdresW adresW - wskazanie na wezel, z ktorego mamy usunac informacje o luku
        Lista2 listaL - lista lukow, na ktorej znajduje sie zadany luk
        int k - zmienna kontrolna odpowiedzialna za wskazanie, czy luk jest "wychodzacy", czy "przychodzacy"

wartosc zwracana:
        void

zmienne lokalne:
        
funkcje importowane:
        nic

obslugiwane wyjatki:
            -zadany luk nie istnieje
--------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "DpurLiW.h"
//#ifndef STRUCT_H
//   #define STRUCT_H
   #include "STRUCT.h"
//#endif

void purLiW(AdresW adresW, Lista2 listaL,int k)
{
    Lista2 actL;
    Lista2 preL;
    Lista2 postL;
    AdresL adreswWekt;
    preL=NULL;
    if(k==1)
        actL=adresW->Przychodzace;
    else
        actL=adresW->Wychodzace;
    if(actL!=NULL)
        adreswWekt=actL->adresL;
    while((adreswWekt!=listaL->adresL)&&(actL!=NULL))
    {
        preL=actL;
        actL=actL->nastepny;
        if(actL!=NULL)
            adreswWekt=actL->adresL;
    }
    if(actL==NULL)
        printf("nie znalazlem luku\n");
    if(actL!=NULL)
    {
        postL=actL->nastepny;
        if(preL==NULL)
        {
            if(k==1)
                adresW->Przychodzace=postL;
            else
                adresW->Wychodzace=postL;
        }
        else
            preL->nastepny=postL;
        free(actL);
    }
}
