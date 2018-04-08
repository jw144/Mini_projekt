/*! \file r_w_func.c
    \brief Plik definiujacy funkcje zawarte w r_w_func.h
*/

#include "../lib/r_w_func.h"
#include "../lib/defines.h"

//na potrzeby printf
#include <stdio.h>

/*! \fn void wczytaj_rozmiary_tablicy(Area* mapa)
    \brief Wczytuje ilosc kolumn u wierszy tablicy z rybami
    \param mapa Mapa z rybami
*/
void wczytaj_rozmiary_tablicy(Area* mapa)
{
    //Uzyte tymczasowo, na razie jeszcze nie zrobione
    scanf("%d %d", &mapa->n, &mapa->m);
    return;
}

/*! \fn void wczytaj_dane_tablicy(Area* mapa, Player* gracz)
    \brief Wczytuje pozostale dane
    \param mapa Mapa z rybami
    \param gracz Parametry gracza
*/
void wczytaj_dane_tablicy(Area* mapa, Player* gracz)
{
    //Obecnie puste
    return;
}
