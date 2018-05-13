/*! \file inter_mode.h
    \brief Biblioteka z funkcjami interfejsu
*/

#ifndef INTER_MODE_H_
#define INTER_MODE_H_

#include "../lib/defines.h"
#include <curses.h>

/*! \fn void tryb_manual(Area* mapa, Players* gracze, int argc, char** argv)
    \brief Wyswietla tablice z rybami i pozwala na wykonanie ruchu
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param argc Zmienna z liczba wczytanych parametrow przy starcie programu
    \param argv Tablica z parametrami wczytanymi przy starcie programu
*/
void tryb_manual(Area* mapa, Players* gracze, int argc, char** argv);

/*! \fn void uzupelnij_tablice(Area* mapa, WINDOW** area_win, int area_win_y)
    \brief Uzupelnia tablice o brakujace znaki
    \param mapa Mapa z rybami
    \param area_win Okno z tablica z rybami
    \param area_win_y Maksymalna szerokosc okna
*/
void uzupelnij_tablice(Area* mapa, WINDOW** area_win, int area_win_y);

/*! \fn void wypisz_tablice(Area* mapa, WINDOW** area_win, Par highlight)
    \brief Wypisuje ryby na tablice
    \param mapa Mapa z rybami
    \param area_win Okno z tablica z rybami
    \param highlight Wspolrzedne podkreslenia
*/
void wypisz_tablice(Area* mapa, WINDOW** area_win, Par highlight);

/*! \fn WINDOW* make_win(int height, int width, int startx, int starty)
    \brief Tworzy nowe okno i ramke do niego
    \param height Wysokosc okna
    \param width Szerokosc okna
    \param startx Punkt startowy x okna
    \param starty Punkt startowy y okna
*/
WINDOW* make_win(int height, int width, int startx, int starty);

/*! \fn int faza_gry(char* phase)
    \brief Przypisuje numen fazy gry do zmiennej 0 - placement, 1 - movement
    \param phase lancuch z faza gry
*/
int faza_gry(char* phase);
#endif // INTER_MODE_H_
