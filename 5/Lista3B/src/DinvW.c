/*-------------------------------------
Definicja funkcji sprawdzajacej, czy nazwa wezla nie powtorzyla sie
Autor: Jacek Mucha
Data stworzenia pliku: 29 kwietnia 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
-------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
//#ifndef DEQSTR_H
//   #define DEQSTR_H 
   #include "DeqStr.h"
//#endif
//#ifndef STRUCT_H
//   #define STRUCT_H
#include "STRUCT.h"
//#endif
#include "DinvW.h"

int invW(Lista1 ptr, char *NazwaWe)
{
    int spr1=1;
    if(ptr!=NULL)
    {
        AdresW pom;
        while(ptr!=NULL)
        {
            pom=ptr->adresW;
            if(eqStr(NazwaWe,pom->NazwaW)==1)
            {
                spr1=0;
                return spr1;
            }
            ptr=ptr->kolejny;
        }
    }
    return spr1;
}
