/*-------------------------------------
Definicja funkcji dodajacej wezly
Autor: Jacek Mucha
Data stworzenia pliku: 29 kwietnia 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
---------------------------------------
zmienne wejscia:
        Lista1 ptr - aktualna lista wezlow, do ktorej chcemy dodac nowy element
        char *NazwaWe - identyfikator wezla, jaki chcemy dodac
        int numer - numer porzadkowy wezla. jest potrzebny w funkcji viaWW

wartosc zwracana:
        Lista1 nowyWLi - nowy pierwszy element listy wezlow
        Lista1 ptr - jesli wyskoczy jakis wyjatek

zmienne lokalne:
        
funkcje importowane:
        int invW - funkcja sprawdzajaca wyjatek istnienia w liscie wezla o zadanej nazwie

obslugiwane wyjatki:
            -wystapil juz wezel o tej nazwie
            -przekroczenie pamieci (dla struktury Wezel)
            -przekroczenie pamieci (dla struktury ListaW)
--------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "DaddW.h"
#ifndef DINVW_H
   #define DINVW_H
   #include "DinvW.h"
#endif
#ifndef STRUCT_H
   #define STRUCT_H
   #include "STRUCT.h"
#endif

Lista1 addW(Lista1 ptr, char *NazwaWe, int numer)
{
    if(invW(ptr,NazwaWe))
    {
        Lista1 nowyWLi;
        AdresW nowyW;
        nowyW=malloc(sizeof(struct Wezel));
        if(nowyW==NULL)
        {
            printf("\nZa malo pamieci\n");
            return ptr;
        }
        nowyWLi=malloc(sizeof(struct ListaW));
        if(nowyWLi==NULL)
        {
            printf("\nZa malo pamieci\n");
            return ptr;
        }
//przepisanie NazwaWe do nowego wektora
        int i=0;
        for(i=0; i<7&&NazwaWe[i]!='\0'; i++)
        {
            nowyW->NazwaW[i]=NazwaWe[i];
            nowyW->NazwaW[i+1]='\0';
        }
        nowyW->NUMER=numer;
//Lista lukow przychodzacych i wychodzacych musi byc pusta
        nowyW->Wychodzace=NULL;
        nowyW->Przychodzace=NULL;
        nowyWLi->adresW=nowyW;
        nowyWLi->kolejny=ptr;
        return nowyWLi;
    }
    else
    {
        printf("\n Taki wezel juz istnieje!\n");
        return ptr;
    }
}
