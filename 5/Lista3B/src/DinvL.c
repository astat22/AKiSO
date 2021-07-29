/*-------------------------------------
Definicja funkcji sprawdzajacej, czy nazwa luku sie nie powtarza
Autor: Jacek Mucha
Data stworzenia pliku: 1 maja 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
---------------------------------------
zmienne wejscia:
        Lista2 ptr - lista lukow, nad ktora pracujemy
        char *Nom - identyfikator sprawdzanego luku

wartosc zwracana:
        int spr2 - 0, jesli nazwa sie powtarza
zmienne lokalne:
        
funkcje importowane:
        int eqStr - funkcja porownujaca stringi

obslugiwane wyjatki:
            -
--------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "DinvL.h"
//#ifndef DEQSTR_H
//   #define DEQSTR_H 
   #include "DeqStr.h"
//#endif
//#ifndef STRUCT_H
//   #define STRUCT_H
   #include "STRUCT.h"
//#endif

int invL(Lista2 ptr, char *Nom)
{
    int spr2=1;
    if(ptr!=NULL)
    {
        AdresL pom;
        while(ptr!=NULL)
        {
            pom=ptr->adresL;
            if(eqStr(Nom,pom->NazwaL)==1)
            {
                spr2=0;
                return spr2;
            }
            ptr=ptr->nastepny;
        }
    }
    return spr2;
}
