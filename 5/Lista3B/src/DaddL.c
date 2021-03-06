/*-------------------------------------
Definicja funkcji dodajacej luki
Autor: Jacek Mucha
Data stworzenia pliku: 30 kwietnia 2012
Projekt GRAF
---------------------------------------
zmiany w module:
       -
---------------------------------------
zmienne wejscia:
        char *NazwaLu - identyfikator luku
        char *Wp - identyfikator wezla poczatkowego
        char *Wk - identyfikator wezla koncowego
        Lista1 ptr1 - lista wezlow, ktorej zadany luk dotyczy
        Lista2 ptr2 - lista lukow, na ktorej luk zostanie umieszczony

wartosc zwracana:
        Lista2 nowyLLi - jesli wszystko poszlo dobrze
        Lista2 ptr2 - jesli wystapil blad

zmienne lokalne:
        
funkcje importowane:
        int eqStr - funkcja porownujaca dwa stringi
        int invL - funkcja sprawdzajaca, czy nazwa luku nie powtarza sie

obslugiwane wyjatki:
            -wystapil juz luk o tej nazwie
            -brak wezlow
            -brak wezla poczatkowego lub koncowego
            -przekroczenie pamieci (ListaL)
            -przekroczenie pamieci (Luk)
--------------------------------------*/
//#ifndef STDLIB_H
  // #define STDLIB_H <stdlib.h>
   #include <stdlib.h>
   //#include STDLIB_H
//#endif
//#ifndef STDIO_H
  // #define STDIO_H <stdio.h>
  // #include STDIO_H
#include <stdio.h>
//#endif
//#include <stdio.h>
//#ifndef DEQSTR_H
//   #define DEQSTR_H "DeqStr.h"
//   #include DEQSTR_H
//#endif
#include "DeqStr.h"
//#ifndef DINVL_H
  //  #define DINVL_H
    #include "DinvL.h"
//#endif
#include "DaddL.h"
//#ifndef STRUCT_H
  // #define STRUCT_H
   #include "STRUCT.h"
//#endif

Lista2 addL(char *NazwaLu, char *Wp, char *Wk, Lista1 ptr1, Lista2 ptr2)                         
{
    if(invL(ptr2,NazwaLu))
    {
//Warunek brzegowy 1: czy sa jakiekolwiek wezly?
        if(ptr1==NULL)
        {
            printf("\nNie ma zadnych wezlow\n");
            return ptr2;
        }
        else
        {
            Lista2 nowyLLi;
            AdresL nowyL;
            Lista1 ptr1pom,ptr1pom2;
            ptr1pom=ptr1;
//Szukanie wezla Wp
            AdresW pomWp;
            pomWp=ptr1->adresW;
            while((!eqStr(pomWp->NazwaW,Wp))&&ptr1!=NULL)
            {
                ptr1pom2=ptr1;
                ptr1=ptr1->kolejny;
                if(ptr1!=NULL)
                {
                    pomWp=ptr1->adresW;
                }
            }
//Warunek brzegowy 2: czy istnieje wezel poczatkowy?
            if(ptr1==NULL)
            {
                printf("\nNie ma takiego poczatkowego wezla. Koncowego juz nie sprawdzam.\n");
                return ptr2;
            }
            else
            {
//Szukanie wezla Wk
                AdresW pomWk;
                pomWk=ptr1pom->adresW;
                while(!eqStr(pomWk->NazwaW,Wk)&&ptr1!=NULL)
                {
                    ptr1pom2=ptr1pom;
                    if(ptr1pom2==NULL)
                        printf(" ");
                    ptr1pom=ptr1pom->kolejny;
                    if(ptr1pom!=NULL)
                    {
                        pomWk=ptr1pom->adresW;
                    }
                }
//Warunek brzegowy 3: czy istnieje wezel koncowy?
                if(ptr1pom==NULL)
                {
                    printf("\nNie ma takiego koncowego wezla\n");
                }
                else
                {
//Dodawanie luku do Lista2
                    int i5=0;
                    nowyLLi=malloc(sizeof(struct ListaL));
                    if(nowyLLi==NULL)
                    {
                        printf("\nZa malo pamieci\n");
                        return ptr2;
                    }
                    nowyL=malloc(sizeof(struct Luk));
                    if(nowyL==NULL)
                    {
                        printf("\nZa malo pamieci\n");
                        return ptr2;
                    }
                    //przepisanie nazwy luku
                    for(i5=0; i5<7&&NazwaLu[i5]!='\0'; i5++)
                    {
                        nowyL->NazwaL[i5]=NazwaLu[i5];
                        nowyL->NazwaL[i5+1]='\0';
                    }
                    nowyL->Od=pomWp;
                    nowyL->Do=pomWk;
                    nowyLLi->adresL=nowyL;
                    nowyLLi->nastepny=ptr2;
//Dodawanie informacji o luku do Wp
                    Lista2 Ab;
                    Lista2 Abadalter;
                    Abadalter=pomWp->Wychodzace;
                    Ab=malloc(sizeof(struct Luk));
                    Ab->adresL=nowyL;
                    Ab->nastepny=Abadalter;
                    pomWp->Wychodzace=Ab;
//Dodawanie informacji o luku do Wk
                    Lista2 Ad;
                    Lista2 Adadalter;
                    Adadalter=pomWk->Przychodzace;
                    Ad=malloc(sizeof(struct Luk));
                    Ad->adresL=nowyL;
                    Ad->nastepny=Adadalter;
                    pomWk->Przychodzace=Ad;
//Zwracany jest adres do pierwszego elementu w nowej liscie lukow
                    return nowyLLi;
                }
            }
        }
    }
    else
    {
//Jesli luk o zadanej nazwie juz istnieje, to zwracana jest lista wejsciowa
        printf("\nLuk o zadanej nazwie aktualnie istnieje\n");
        return ptr2;
    }
    return ptr2;
}
