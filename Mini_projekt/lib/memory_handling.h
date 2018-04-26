/*! \file memory_handling.h
    \brief Biblioteka zarzadzajaca pamiecia
*/

#ifndef MEMORY_HANDLING_H_
#define MEMORY_HANDLING_H_

#include "../lib/defines.h"

/*! \fn void przydziel(Area* mapa, Player* gracz)
    \brief Przydziela pamiec do tablic
    \param mapa Mapa z rybami
    \param gracz Parametry gracza
*/
void przydziel(Area* mapa, Player** gracz);


/*! \fn void przydziel_area(Area* mapa)
    \brief Przydziela pamiec do tablicy z rybami
    \param mapa Mapa z rybami
*/
void przydziel_area(Area* mapa, Player** gracz);

/*! \fn void przydziel_player(Player* gracz)
    \brief Przydziela pamiec do tablicy z nazwa gracza
    \param gracz Parametry gracza
*/
void przydziel_player(Player** gracz, Area* mapa);

/*! \fn void zwolnij(Area* mapa, Player* gracz)
    \brief Zwalnia pamiec
    \param mapa Mapa z rybami
    \param gracz Parametry gracza
*/
void zwolnij(Area* mapa, Player** gracz);

void zwolnij_area(Area* mapa);

void zwolnij_player(Player** gracz);

#endif // MEMORY_HANDLING_H_
