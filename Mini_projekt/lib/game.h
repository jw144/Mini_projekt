/*! \file game.h
    \brief Biblioteka z funkcjami gry
*/

#ifndef GAME_H_
#define GAME_H_

#include "../lib/defines.h"

/*! \fn void wybor_trybu(Area* mapa, Players* gracze, int argc, char** argv)
    \brief Wybiera tryb w kompilacji warunkowej pomiedzy auto a manual
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param argc Zmienna z liczba wczytanych parametrow przy starcie programu
    \param argv Tablica z parametrami wczytanymi przy starcie programu
*/
void wybor_trybu(Area* mapa, Players* gracze, int argc, char** argv);

/*! \fn int manual_placement(Area* mapa, Players* gracze, Par highlight, Parameters* My)
    \brief Umieszcza pingwina na planszy
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param highlight Aktualna wybierana pozycja
    \param My Nasze parametry
*/
int manual_placement(Area* mapa, Players* gracze, Par highlight, Parameters* My);

/*! \fn int manual_movement(Area* mapa, Players* gracze, Par highlight, Parameters* My, int temp)
    \brief Przesuwa pingwina
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param highlight Aktualna wybierana pozycja
    \param My Nasze parametry
    \param temp Faza przesuwania
*/
int manual_movement(Area* mapa, Players* gracze, Par highlight, Parameters* My, int temp);

/*! \fn int min_el(int a, int b);
    \brief Znajduje minimum
    \param a Pierwsza wartosc
    \param b Druga wartosc
*/
int min_el(int a, int b);

/*! \fn int max_el(int a, int b);
    \brief Znajduje maksimum
    \param a Pierwsza wartosc
    \param b Druga wartosc
*/
int max_el(int a, int b);

/*! \fn Parameters* czy_jest_gracz(Area* mapa, Players* gracze, int phase)
    \brief Sprawdza czy gracz jest zapisany w pliku, jeœli nie ma, dla phase = 0 dodaje go, a dla phase = 1 wywala blad
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param phase Faza gry
*/
Parameters* czy_jest_gracz(Area* mapa, Players* gracze, int phase);

/*! \fn void czy_jest_miejsce(Area* mapa, Players* gracze, Parameters* My, char* penguins)
    \brief Sprawdza czy jest miejsce na pingwina
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param My Nasze parametry
    \param penguins Lancuch z iloscia pingwinow
*/
void czy_jest_miejsce(Area* mapa, Players* gracze, Parameters* My, char* penguins);

/*! \fn void czy_jest_ruch(Area* mapa, Players* gracze, Parameters* My)
    \brief Sprawdza czy mozna sie ruszyc pingwinami
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param My Nasze parametry
*/
void czy_jest_ruch(Area* mapa, Players* gracze, Parameters* My);
#endif // GAME_H_
