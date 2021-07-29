/*-------------------------------------
Definicja funkcji kontrolujacej wykonywanie operacji w main
Autor: Jacek Mucha
Data stworzenia pliku: 1 maja 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
-------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "DdaInt.h"

int daInt(char c)
{
    int n;
    switch(c)
    {
    case 48:
        n=0;
        break;
    case 49:
        n=1;
        break;
    case 50:
        n=2;
        break;
    case 51:
        n=3;
        break;
    case 52:
        n=4;
        break;
    case 53:
        n=5;
        break;
    case 54:
        n=6;
        break;
    case 55:
        n=7;
        break;
    case 56:
        n=8;
        break;
    case 57:
        n=9;
        break;
    }
    return n;
}
