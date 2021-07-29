/*-------------------------------------
Definicja funkcji sprawdzajacej identycznosc dwoch stringow
Autor: Jacek Mucha
Data stworzenia pliku: 1 maja 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
-------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DeqStr.h"

int eqStr(char *radix, char *arbor)
{
    int eq=1,i2=0;
    if(strlen(radix)!=strlen(arbor))
    {
        eq=0;
        return eq;
    }
    for(i2=0; i2<7&&eq&&(arbor[i2]!='\0')&&(radix[i2]!='\0'); i2++)
    {
        if(arbor[i2]!=radix[i2])
        {
            eq=0;
        }
    }
    return eq;
}
