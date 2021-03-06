/*-------------------------------------
Definicja funkcji wypisujacej sasiedztwo zadanego wezla
Autor: Jacek Mucha
Data stworzenia pliku: 1 maja 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
---------------------------------------
zmienne wejscia:
        char *ID - identyfikator wezla
        Lista1 ptrw  - lista wezlow, w ktorej bedziemy szukac zadanego wezla

wartosc zwracana:
        void
zmienne lokalne:
        
funkcje importowane:
        int eqStr
        int invW

obslugiwane wyjatki:
            -brak wezlow przychodzacych
            -brak wezlow wychodzacych
            -podany wezel nie istnieje
--------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "DconsW.h"
//#ifndef DEQSTR_H
  // #define DEQSTR_H 	//same include
   #include "DeqStr.h"
//#endif
//#ifndef DINVW_H
  // #define DINVW_H
   #include "DinvW.h"
//#endif
//#ifndef STRUCT_H
// #define STRUCT_H
   #include "STRUCT.h"
//#endif

void consW(char *ID, Lista1 ptrw)
{
//czy taki wezel istnieje?
    if(invW(ptrw,ID)==0)
    {
//wyszukaj wezel
        int br=1;//zmienna logiczna dla petli while
        AdresW naszW;
        naszW=ptrw->adresW;
        if(eqStr(ID,naszW->NazwaW))
        {
            br=0;
        }
//sprawdzilismy, ze taki wezel istnieje, wiec w while wystarczy jeden warunek
        while(br)
        {
            ptrw=ptrw->kolejny;
            if(ptrw!=NULL)
            {
                naszW=ptrw->adresW;
                if(eqStr(ID,naszW->NazwaW))
                {
                    br=0;
                }//if(eqStr(Id,naszW->NazwaW)
            }//if(ptrw!=NULL)
        }//while(br)
//wypisywanie wezlow przychodzacych
        Lista2 ptrl;
        AdresW sasiad;
        AdresW sasiadPom;
        AdresL viaSasiad;
        AdresL viaSasiadPom;
        Lista2 ptrlPom;
        Lista2 ptrlPom2;
        ptrl=naszW->Przychodzace;
        if(ptrl==NULL)
            printf("brak wezlow przychodzacych\n");
        else
        {
            printf("wezly przychodzace:\n");
            int br2=1;
            ptrlPom2=ptrl;
            ptrlPom=ptrl;
            while(ptrl!=NULL)
            {
                viaSasiad=ptrl->adresL;
                sasiad=viaSasiad->Od;
                //sprawdzenie, czy dany wezel juz wystapil
                while(ptrlPom!=ptrl)
                {
                    viaSasiadPom=ptrlPom->adresL;
                    sasiadPom=viaSasiadPom->Od;
                    if(eqStr(sasiad->NazwaW,sasiadPom->NazwaW))
                    {
                        br2=0;
                    }
                    ptrlPom=ptrlPom->nastepny;
                }//while(ptrlPom!=ptrl)
                ptrl=ptrl->nastepny;
                if(br2)
                {
                    printf("%s", sasiad->NazwaW);
                    if(ptrl!=NULL)
                        printf(", ");
                }
                br2=1;
                ptrlPom=ptrlPom2;
            }//while(ptrl!=NULL)
            printf("\n");
        }// if(ptrl!=NULL)
//wypisywanie wezlow wychodzacych
        ptrl=naszW->Wychodzace;
        if(ptrl==NULL)
            printf("brak wezlow wychodzacych\n");
        else
        {
            printf("wezly wychodzace:\n");
            int br2=1;
            ptrlPom2=ptrl;
            ptrlPom=ptrl;
            while(ptrl!=NULL)
            {
                viaSasiad=ptrl->adresL;
                sasiad=viaSasiad->Do;
                //sprawdzenie, czy dany wezel juz wystapil
                while(ptrlPom!=ptrl)
                {
                    viaSasiadPom=ptrlPom->adresL;
                    sasiadPom=viaSasiadPom->Do;
                    if(eqStr(sasiad->NazwaW,sasiadPom->NazwaW))
                    {
                        br2=0;
                    }
                    ptrlPom=ptrlPom->nastepny;
                }//while(ptrlPom!=ptrl)
                ptrl=ptrl->nastepny;
                if(br2)
                {
                    printf("%s", sasiad->NazwaW);
                    if(ptrl!=NULL)
                        printf(", ");
                }
                br2=1;
                ptrlPom=ptrlPom2;
            }//while(ptrl!=NULL)
            printf("\n");
        }// if(ptrl!=NULL)
    }//if(invW(ptrw,ID)==0)
    else
        printf("podany wezel nie istnieje\n");
}
