   #include <stdlib.h>
   #include <stdio.h>
   #include <string.h>
   #include "../headers/STRUCT.h"
   #include "../headers/DaddL.h"
   #include "DaddW.h"
   #include "DconsW.h"
   #include "DdaInt.h"
   #include "DdelW.h"
   #include "DdelL.h"
   #include "DeqStr.h"
   #include "DinvL.h"
   #include "DinvW.h"
   #include "DpurLiW.h"
   #include "Dqualitas.h"
   #include "DviaWW.h"
   #include "DvidL.h"
   #include "DvidW.h"
   #include "DvotW.h"


int main(void)
{
//deklaracja listy wezlow i listy lukow
    Lista1 ptrW;
    Lista2 ptrL;
    Hestia tau;
    ptrW=NULL;
    ptrL=NULL;
    int numerW=1;
    char wezel1[7];
    char wezel2[7];
    char luk[7];
    char poleceniePom;
    int polecenie=11;//zmienna kontrolna petli glownej proramu
    printf("Wpisz polecenie:\n 0- wyjscie z programu\n 1- dodaj nowy wezel\n 2- przegladaj wezly\n 3- usun wezel\n 4- dodaj nowy luk\n 5- przegladaj luki\n 6- usun luk\n 7- szukaj drogi od ID1 do ID2\n 8- czy istnieje luk od ID1 do ID2?\n 9- wypisz sasiedztwo zadanego wezla\n");
    while(polecenie!=0)
    {
        poleceniePom=getchar();
        polecenie=daInt(poleceniePom);
        if(polecenie==1)
        {
            scanf(" %s ", wezel1);
            if(strlen(wezel1)>7)
            {
                printf("niewlasciwa nazwa\n");
            }
            else //strlen(wezel1)<7
                if(qualitas(wezel1))
                {
                    ptrW=addW(ptrW,wezel1, numerW);
                    numerW++;
                }
        }//if(polecenie==1)
        if(polecenie==2)
        {
            vidW(ptrW);
        }
        if(polecenie==3)
        {
            scanf(" %s",wezel1);
            if(strlen(wezel1)>7)
            {
                printf("niewlasciwa nazwa\n");
            }
            else if(qualitas(wezel1))
            {
                tau=delW(wezel1,ptrW,ptrL);
                ptrW=tau->mal;
                ptrL=tau->fem;
            }
        }//if(polecenie==3)
        if(polecenie==4)
        {
            scanf(" %s od %s do %s",luk,wezel1,wezel2);
            if(strlen(wezel1)>7||strlen(wezel2)>7||strlen(luk)>7)
            {
                printf("niewlasciwa nazwa\n");
            }
            else
                ptrL=addL(luk,wezel1,wezel2,ptrW,ptrL);
        }//if(polecenie==4)
        if(polecenie==5)
        {
            vidL(ptrL,1);
        }
        if(polecenie==6)
        {
            scanf(" %s",luk);
            if(strlen(luk)>7)
            {
                printf("niewlasciwa nazwa");
            }
            else
                ptrL=delL(luk, ptrL,1);
        }//if(polecenie==6)
        if(polecenie==7)
        {
            scanf(" od %s do %s",wezel1,wezel2);
            if(strlen(wezel1)>7||strlen(wezel2)>7)
            {
                printf("niewlasciwa nazwa\n");
            }
            else
                viaWW(ptrW, numerW+1, ptrL, wezel1, wezel2);
        }
        if(polecenie==8)
        {
            scanf(" od %s do %s",wezel1,wezel2);
            if(strlen(wezel1)>7||strlen(wezel2)>7)
            {
                printf("niewlasciwa nazwa\n");
            }
            else
                votW(wezel1,wezel2,ptrL,ptrW);
        }//if(polecenie==8)
        if(polecenie==9)
        {
            scanf(" %s",wezel1);
            if(strlen(wezel1)>7)
            {
                printf("niewlasciwa nazwa\n");
            }
            else
            {
                consW(wezel1,ptrW);
            }
        }
    }//    while(polecenie!=0)
}
