/*-------------------------------------
Definicja funkcji szukajacej drogi miedzy zadanymi wezlami
Autor: Jacek Mucha
Data stworzenia pliku: 1 maja 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
---------------------------------------
zmienne wejscia:
        Lista1 ptrw - tu sa zadane wezly
        int rozmiar - informacja o rozmiarze macierzy
        Lista2 ptrl - na tej liscie bedziemy szukac sciezki
        char *ID1 - wezel poczatkowy- jego identyfikator
        char *ID2 - identyfiklator wezla koncowego

wartosc zwracana:
        void
zmienne lokalne:
        
funkcje importowane:
        int eqStr
        int invW

obslugiwane wyjatki:

--------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "DviaWW.h"
//#ifndef DEQSTR_H
//   #define DEQSTR_H 
   #include "DeqStr.h"
//#endif
#include "DinvW.h"
//#ifndef STRUCT_H
//   #define STRUCT_H
   #include "STRUCT.h"
//#endif

void viaWW(Lista1 ptrw, int rozmiar, Lista2 ptrl, char *ID1, char *ID2)
{
    if(ptrw!=NULL)//wyjatek 1- brak wezlow
    {
        if(ptrl!=NULL)//wyjatek 2- brak lukow
        {
            if(invW(ptrw,ID1)==0)//wyjatek 3-brak poczatkowego wezla
            {
                if(invW(ptrw,ID2)==0)//wyjatek 4- brak koncowego wezla
                {
                    if(!eqStr(ID1,ID2))
                    {
//tworzenie macierzy polaczen wezlow
                        int M[rozmiar][rozmiar];
                        int M2[rozmiar][rozmiar];
                        int it1,it2;
//zerowanie macierzy
                        for(it1=0; it1<rozmiar; it1++)
                            for(it2=0; it2<rozmiar; it2++)
                            {
                                M[it1][it2]=0;
                                M2[it1][it2]=0;
                            }
//czytanie polaczen
                        AdresL adL;
                        AdresW WOd, WDo;
                        while(ptrl!=NULL)
                        {
                            adL=ptrl->adresL;
                            WOd=adL->Od;
                            WDo=adL->Do;
                            M[WOd->NUMER][WDo->NUMER]=WDo->NUMER;
                            M2[WOd->NUMER][WDo->NUMER]++;
                            ptrl=ptrl->nastepny;
                        }// while(ptrl!=NULL)
//Roy-Warshall
                        int it3;
                        //szukanie numerow wezlow
                        int Pocz;
                        int Kon;
                        int br=1;//zmienna logiczna dla petli while
                        AdresW WPocz;
                        AdresW WKon;
                        Lista1 ptrwP;
                        ptrwP=ptrw;
                        if(ptrwP!=NULL)
                        {
                            WPocz=ptrwP->adresW;
                            if(eqStr(ID1,WPocz->NazwaW))
                            {
                                br=0;
                                Pocz=WPocz->NUMER;
                            }
                            while(br&&ptrwP!=NULL)
                            {
                                ptrwP=ptrwP->kolejny;
                                if(ptrwP!=NULL)
                                {
                                    WPocz=ptrwP->adresW;
                                    if(eqStr(ID1,WPocz->NazwaW))
                                    {
                                        br=0;
                                        Pocz=WPocz->NUMER;
                                        //printf("%s %d \n",WPocz->NazwaW,Pocz);
                                    }//if(eqStr(Id,naszW->NazwaW)
                                }//if(ptrw!=NULL)
                            }//while(br)
                        }//if(ptrwP!=NULL)
                        ptrwP=ptrw;
                        if(ptrwP!=NULL)
                        {
                            br=1;
                            WKon=ptrwP->adresW;
                            if(eqStr(ID2,WKon->NazwaW))
                            {
                                br=0;
                                Kon=WKon->NUMER;
                            }
                            while(br)
                            {
                                ptrwP=ptrwP->kolejny;
                                if(ptrwP!=NULL)
                                {
                                    WKon=ptrwP->adresW;
                                    if(eqStr(ID2,WKon->NazwaW))
                                    {
                                        br=0;
                                        Kon=WKon->NUMER;
                                        //printf("%s %d \n",WKon->NazwaW,Kon);
                                    }//if(eqStr(Id,naszW->NazwaW)
                                }//if(ptrw!=NULL)
                            }//while(br)
                        }//if(ptrwP!=NULL)
//procedura route
                        for(it1=0; it1<rozmiar; it1++)
                            for(it2=0; it2<rozmiar; it2++)
                                if(M[it2][it1]!=0)//wiemy jak dojsc z it2 do it1
                                    for(it3=0; it3<rozmiar; it3++)
                                        if((M[it2][it3]==0)&&(M[it1][it3]!=0))
                                            M[it2][it3]=M[it2][it1];
                        printf("\n");
//procedura scribere
                        int br3;
                        br3=Pocz;
                        if(M[Pocz][Kon]==0)
                            printf("droga nie istnieje\n");
                        else
                        {
                            AdresW adWP;
                            printf("%s->",ID1);
                            while(br3!=Kon)
                            {
                                br3=M[br3][Kon];
                                ptrwP=ptrw;
                                adWP=ptrwP->adresW;
                                while(adWP->NUMER!=br3)
                                {
                                    ptrwP=ptrwP->kolejny;
                                    adWP=ptrwP->adresW;
                                }
                                printf("%s",adWP->NazwaW);
                                if(br3!=Kon)
                                    printf("->");
                            }
                        }
                        printf("\n");
                    }//ID1!=ID2
                    else
                        printf("wezel poczatkowy musi byc rozny od koncowego\n");
                }//if(!invW(ptrw,ID2)
                else
                    printf("taki koncowy wezel nie istnieje");
            }//if(!invW(ptrw, ID1)
            else
                printf("taki poczatkowy wezel nie istnieje\n");
        }//if(ptrl!=NULL)
        else
            printf("nie ma zadnych lukow\n");
    }//if(ptrl!=NULL)
    else
        printf("nie ma zadnych wezlow\n");
}
