//**************************STRUKTURY*******************************************************
typedef struct Wezel* AdresW;
typedef struct ListaW* Lista1;
typedef struct Luk* AdresL;
typedef struct ListaL* Lista2;
typedef struct Nuptias* Hestia;
#ifndef STRUCT_H
   #define DSTRUCT_H
//Struktura wierzcholek. trzy pola: identyfikator, lista wychodzacych, lista przychodzacych
struct Wezel
{
    char NazwaW[8]; //Identyfikator
    int NUMER;     // kazdy wezel ma swoj przyporzadkowany numer. potrzebne do algorytmu Warshalla
    Lista2 Wychodzace; //Adresy lukow, ktore wychodza
    Lista2 Przychodzace; //Adresy lukow, ktore przychodza
};
//Druga struktura- luk
struct Luk
{
    char NazwaL[8];//Identyfikator luku
    AdresW Od; //adres wierzcholka, od ktorego luk wychodzi
    AdresW Do; //adres wezla, do ktorego luk dochodzi
};
//Lista przechowujaca adresy wezlow
struct ListaW
{
    AdresW adresW; //Wskazuje adres wezla
    struct ListaW *kolejny;//Wskazuje adres wskazania adresu kolejnego wezla- kolejna pozycja na liscie
};
//Lista przechowujaca adresy lukow
struct ListaL
{
    AdresL adresL; //Wskazuje adres luku
    struct ListaL *nastepny; //Wskazuje adres wskazania adresu kolejnego luku- kolejna pozycja na liscie
};
//Struktura pomocnicza przechowujaca liste lukow i liste wezlow
//potrzebna, bo funkcja usuwajaca wezel zwraca nawa liste wezlow i nowa liste lukow
struct Nuptias
{
    Lista1 mal;
    Lista2 fem;
};

#endif
