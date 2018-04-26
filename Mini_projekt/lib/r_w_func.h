/*! \file r_w_func.h
    \brief Biblioteka wczytujaca dane
*/

#ifndef R_W_FUNC_H_
#define R_W_FUNC_H_

#include "../lib/defines.h"
#include <stdio.h>

void otworz_plik(int argc, char** argv, FILE** plik, int i_or_o, Area* mapa, Player** gracz);

void zamknij_plik(FILE** plik);

int pozycja_pliku_w_argumentach(int argc, int i_or_o);

/*! \fn void wczytaj_rozmiary_tablicy(Area* mapa)
    \brief Wczytuje ilosc kolumn u wierszy tablicy z rybami
    \param mapa Mapa z rybami
*/
void wczytaj_rozmiary_tablicy(Area* mapa, FILE** plik, Player** gracz);

/*! \fn void wczytaj_dane_tablicy(Area* mapa, Player* gracz)
    \brief Wczytuje pozostale dane
    \param mapa Mapa z rybami
    \param gracz Parametry gracza
*/
void wczytaj_dane_tablicy(Area* mapa, Player** gracz, FILE** plik);

void usun_puste(FILE** plik, Area* mapa, Player** gracz);

void czy_poprawny_znak(int ch, int (*znak) (int ch), Area* mapa, Player** gracz);

#endif // R_W_FUNC_H_
