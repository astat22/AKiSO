/*-------------------------------------
Definicja funkcji usuwajacej wezly
Autor: Jacek Mucha
Data stworzenia pliku: 29 kwietnia 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
-------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "DdelL.h"
#include "DeqStr.h"
#include "STRUCT.h"
#include "DdelW.h"

Hestia delW(char *NazwaWe, Lista1 ptr, Lista2 ptrL)
{
    Lista1 preWekt;
    Lista1 actWekt;
    Lista1 postWekt;
    Lista2 ptrLiW;
    AdresW adW;
    AdresL adL;
    preWekt=NULL;
    actWekt=ptr;
    if(ptr!=NULL)
        adW=ptr->adresW;
    Hestia votum;
    votum=malloc(sizeof(struct Nuptias));
    char NazwaLuku[7];
//Szukanie wezla na liscie
    while((actWekt!=NULL)&&(!eqStr(adW->NazwaW,NazwaWe)))
    {
        preWekt=actWekt;
        actWekt=actWekt->kolejny;
        if(actWekt!=NULL)
            adW=actWekt->adresW;
    }
    if(actWekt!=NULL)
    {
//Usuwanie lukow z wezla
        int i4=0;
        ptrLiW=adW->Przychodzace;
        if(ptrLiW!=NULL)
        {
            adL=ptrLiW->adresL;
            //przepisanie nazwy luku
            for(i4=0; i4<7&&adL->NazwaL[i4]!='\0'; i4++)
            {
                NazwaLuku[i4]=adL->NazwaL[i4];
                NazwaLuku[i4+1]='\0';
            }
            while(ptrLiW!=NULL)
            {
                ptrL=delL(NazwaLuku,ptrL,2);
                ptrLiW=adW->Przychodzace;
                if(ptrLiW!=NULL)
                {
                    adL=ptrLiW->adresL;
                    for(i4=0; i4<7&&adL->NazwaL[i4]!='\0'; i4++)
                    {
                        NazwaLuku[i4]=adL->NazwaL[i4];
                        NazwaLuku[i4+1]='\0';
                    }
                }
            }
        }
        ptrLiW=adW->Wychodzace;
        if(ptrLiW!=NULL)
        {
            adL=ptrLiW->adresL;
            //przepisanie nazwy luku
            for(i4=0; i4<7&&adL->NazwaL[i4]!='\0'; i4++)
            {
                NazwaLuku[i4]=adL->NazwaL[i4];
                NazwaLuku[i4+1]='\0';
            }
            while(ptrLiW!=NULL)
            {
                ptrL=delL(NazwaLuku,ptrL,2);
                ptrLiW=adW->Wychodzace;
                if(ptrLiW!=NULL)
                {
                    adL=ptrLiW->adresL;
                    for(i4=0; i4<7&&adL->NazwaL[i4]!='\0'; i4++)
                    {
                        NazwaLuku[i4]=adL->NazwaL[i4];
                        NazwaLuku[i4+1]='\0';
                    }
                }
            }
        }
//Usuwanie wezla z lsty wezlow
        postWekt=actWekt->kolejny;
        if(preWekt==NULL)
        {
            ptr=postWekt;
        }
        else
        {
            preWekt->kolejny=postWekt;
        }
        free(actWekt);
    }
    else
        printf("\nNie ma takiego wezla!\n");
    votum->fem=ptrL;
    votum->mal=ptr;
    return votum;
}
