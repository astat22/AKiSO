/*-------------------------------------
Definicja funkcji sprawdzajacej poprawnosc zapisu identyfikatora
Autor: Jacek Mucha
Data stworzenia pliku: 1 maja 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
-------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "Dqualitas.h"


int qualitas(char *obrussa)
{
    int i3=0,spr3=1;
    for(i3=0; i3<7&&spr3&&obrussa[i3]!='\0'; i3++)
    {
        if(!((obrussa[i3]>47&&obrussa[i3]<58)||(obrussa[i3]>64&&obrussa[i3]<91)||(obrussa[i3]>96&&obrussa[i3]<123)||obrussa[i3]=='\0'))
        {
            spr3=0;
            printf("\nNiepoprawna nazwa. Identyfikator musi skladac sie wylacznie z liter i cyfr.\n");
            return spr3;
        }
    }
    return spr3;
}
