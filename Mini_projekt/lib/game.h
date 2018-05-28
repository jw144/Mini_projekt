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

/*! \fn void tryb_auto(Area* mapa, Players* gracze, int argc, char** argv)
    \brief Wykonuje ruchy automatycznie
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param argc Zmienna z liczba wczytanych parametrow przy starcie programu
    \param argv Tablica z parametrami wczytanymi przy starcie programu
*/
void tryb_auto(Area* mapa, Players* gracze, int argc, char** argv);

/*! \fn void auto_placement(Area* mapa, Players* gracze, int argc, char** argv, Parameters* My)
    \brief Automatycznie umieszcza pingwina
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param argc Zmienna z liczba wczytanych parametrow przy starcie programu
    \param argv Tablica z parametrami wczytanymi przy starcie programu
    \param My Nasze parametry
*/
void auto_placement(Area* mapa, Players* gracze, int argc, char** argv, Parameters* My);

/*! \fn void best_movement_place(Area* mapa, Players* gracze, Parameters* My, int a, int b, int x_poz, int y_poz)
    \brief Przypisuje wagi do poszczegolnych komorek, na ktore mozemy sie poruszyc
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param My Nasze parametry
    \param a Kolumny
    \param b Wiersze
    \param x_poz Kierunek poziomy
    \param y_poz Kierunek pionowy
*/
void best_movement_place(Area* mapa, Players* gracze, Parameters* My, int a, int b, int x_poz, int y_poz);

/*! \fn void enemy_penguins(Area* mapa, Players* gracze, Parameters* My, int a, int b)
    \brief Dodaje do wag komorek dodatkowe punkty za fakt, ze inni moga tam stanac
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param My Nasze parametry
    \param a Kolumny
    \param b Wiersze
*/
void enemy_penguins(Area* mapa, Players* gracze, Parameters* My, int a, int b);

/*! \fn void auto_movement(Area* mapa, Players* gracze, int argc, char** argv, Parameters* My)
    \brief Automatycznie przesuwa pingwina
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param argc Zmienna z liczba wczytanych parametrow przy starcie programu
    \param argv Tablica z parametrami wczytanymi przy starcie programu
    \param My Nasze parametry
*/
void auto_movement(Area* mapa, Players* gracze, int argc, char** argv, Parameters* My);

/*! \fn void assign_best(Area* mapa, int a, int b, Best_movement* movement, int x_poz, int y_poz, int* is_change, Parameters* My)
    \brief Znajduje najlepsze pole do ruchu
    \param mapa Mapa z rybami
    \param a Kolumny
    \param b Wiersze
    \param movement Struktura z najlepszym wynikiem
    \param x_poz Kierunek poziomy
    \param y_poz Kierunek pionowy
    \param My Nasze parametry
*/
void assign_best(Area* mapa, int a, int b, Best_movement* movement, int x_poz, int y_poz, int* is_change, Parameters* My);

#endif // GAME_H_
