/*! \file r_w_func.h
    \brief Biblioteka wczytujaca dane
*/

#ifndef R_W_FUNC_H_
#define R_W_FUNC_H_

#include "../lib/defines.h"

/*! \fn void wczytaj_rozmiary_tablicy(Area* mapa)
    \brief Wczytuje ilosc kolumn u wierszy tablicy z rybami
    \param mapa Mapa z rybami
*/
void wczytaj_rozmiary_tablicy(Area* mapa);

/*! \fn void wczytaj_dane_tablicy(Area* mapa, Player* gracz)
    \brief Wczytuje pozostale dane
    \param mapa Mapa z rybami
    \param gracz Parametry gracza
*/
void wczytaj_dane_tablicy(Area* mapa, Player* gracz);

#endif // R_W_FUNC_H_
