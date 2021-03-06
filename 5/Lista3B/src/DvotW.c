/*-------------------------------------
Definicja funkcji sprawdzajacej, czy istnieje luk miedzy zadanymi wezlami
Autor: Jacek Mucha
Data stworzenia pliku: 1 maja 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
---------------------------------------
zmienne wejscia:
        char *ID1 - identyfikator wezla pierwszego 
        char *ID2 - identyfikator wezla drugiego
        Lista1 ptrw  - lista wezlow, w ktorej bedziemy szukac zadanego wezla
        Lista2 ptr - lista lukow
        
wartosc zwracana:
        void
zmienne lokalne:
        
funkcje importowane:
        int eqStr
        int invW

obslugiwane wyjatki:
            -nie istnieje min. jeden z podanych wezlow
--------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "DvotW.h"
//#ifndef DEQSTR_H
//   #define DEQSTR_H "DeqStr.h"
   #include "DeqStr.h" //DEQSTR_H
//#endif
//#ifndef DINVW_H
//   #define DINVW_H
   #include "DinvW.h"
//#endif
//#ifndef STRUCT_H
//   #define STRUCT_H
   #include "STRUCT.h"
//#endif

void votW( char *ID1, char *ID2, Lista2 ptr, Lista1 ptrw)
{
    if(invW(ptrw,ID1)==0&&invW(ptrw,ID2)==0)
    {
        if(ptr!=NULL)
        {
            int br=1;
            AdresL adL;
            AdresW Pocz;
            AdresW Kon;
            adL=ptr->adresL;
            Pocz=adL->Od;
            Kon=adL->Do;
//szukanie luku
            if(eqStr(ID1,Pocz->NazwaW)&&eqStr(ID2,Kon->NazwaW))
            {
                printf("luk laczacy %s i %s: %s\n",ID1,ID2,adL->NazwaL);
                br=0;
            }
            while(ptr!=NULL&&br)
            {
                ptr=ptr->nastepny;
                if(ptr!=NULL)
                {
                    adL=ptr->adresL;
                    Pocz=adL->Od;
                    Kon=adL->Do;
                    if(eqStr(ID1,Pocz->NazwaW)&&eqStr(ID2,Kon->NazwaW))
                    {
                        printf("luk laczacy %s i %s: %s\n",ID1,ID2,adL->NazwaL);
                        br=0;
                    }
                }
                else
                    printf("taki luk nie istnieje\n");
            }//while ptr!=NULL && br
        }// if ptr!=NULL
        else
            printf("taki luk nie istnieje\n");
    }//jesli takie wierzcholki istnieja
    else
        printf("co najmniej jeden z podanych wezlow nie istnieje\n");
}
