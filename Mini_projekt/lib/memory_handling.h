/*! \file memory_handling.h
    \brief Biblioteka zarzadzajaca pamiecia
*/

#ifndef MEMORY_HANDLING_H_
#define MEMORY_HANDLING_H_

#include "../lib/defines.h"

/*! \fn void przydziel(Area* mapa, Players* gracze)
    \brief Przydziela pamiec do tablic
    \param mapa Mapa z rybami
    \param gracze Parametry gracza
*/
void przydziel(Area* mapa, Players* gracze);

/*! \fn void przydziel_area(Area* mapa, Players* gracze)
    \brief Przydziela pamiec do tablicy z rybami
    \param mapa Mapa z rybami
    \param gracze Parametry gracza
*/
void przydziel_area(Area* mapa, Players* gracze);

/*! \fn void przydziel_player(Area* mapa, Players* gracze)
    \brief Przydziela pamiec do tablicy z nazwa gracza
    \param mapa Mapa z rybami
    \param gracze Parametry gracza
*/
void przydziel_player(Area* mapa, Players* gracze);

/*! \fn void zwolnij(Area* mapa, Player* gracz)
    \brief Zwalnia pamiec
    \param mapa Mapa z rybami
    \param gracze Parametry gracza
*/
void zwolnij(Area* mapa, Players* gracze);

/*! \fn void zwolnij_area(Area* mapa)
    \brief Zwalnia pamiec z tablicy z rybami
    \param mapa Mapa z rybami
*/
void zwolnij_area(Area* mapa);

/*! \fn void zwolnij_player(Players* gracze)
    \brief Zwalnia pamiec z tablicy z graczami
    \param gracze Parametry gracza
*/
void zwolnij_player(Players* gracze);

/*! \fn void program_error(Area* mapa, Players* gracze, char* message, int error_number)
    \brief Wypisuje blad i konczy program
    \param mapa Mapa z rybami
    \param gracze Parametry gracza
    \param message Opis bledu
    \param error_number Kod bledu
*/
void program_error(Area* mapa, Players* gracze, char* message, int error_number);

#endif // MEMORY_HANDLING_H_
