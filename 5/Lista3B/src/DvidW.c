/*-------------------------------------
Definicja funkcji przegladajacej wezly
Autor: Jacek Mucha
Data stworzenia pliku: 29 kwietnia 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
-------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
//#ifndef STRUCT_H
//   #define STRUCT_H
   #include "STRUCT.h"
//#endif
//#ifndef DVIDL_H
//   #define DVIDL_H
   #include "DvidL.h"
//#endif
#include "DvidW.h"

void vidW(Lista1 ptr)
{
    if(ptr==NULL)
        printf("Nie ma zadnych wezlow\n");
    else
    {
        AdresW pom;
        printf("Istnieja nastepujace wezly: \n");
        while(ptr!=NULL)
        {
            pom=ptr->adresW;
            printf("\n%s \n", pom->NazwaW);
            printf("luki przychodzace: ");
            vidL(pom->Przychodzace,2);
            printf("luki wychodzace: ");
            vidL(pom->Wychodzace,2);
            ptr=ptr->kolejny;
        }
    }
}
