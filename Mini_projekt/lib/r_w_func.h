/*! \file r_w_func.h
    \brief Biblioteka wczytujaca dane
*/

#ifndef R_W_FUNC_H_
#define R_W_FUNC_H_

#include "../lib/defines.h"
#include <stdio.h>

/*! \fn void otworz_plik(Area* mapa, Players* gracz, FILE** plik, int i_or_o, int argc, char** argv)
    \brief Otwiera plik do wczytania/zapisu
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param plik Wskaznik na plik, do ktorego wczytujemy/zapisujemy
    \param i_or_o Zmienna do okreœlenia czy wczytujemy czy zapisujemy
    \param argc Zmienna z liczba wczytanych parametrow przy starcie programu
    \param argv Tablica z parametrami wczytanymi przy starcie programu
*/
void otworz_plik(Area* mapa, Players* gracze, FILE** plik, int i_or_o, int argc, char** argv);

/*! \fn void zamknij_plik(FILE** plik)
    \brief Zamyka plik
    \param plik Wskaznik na plik, do ktorego wczytujemy/zapisujemy
*/
void zamknij_plik(FILE** plik);

/*! \fn int pozycja_pliku_w_argumentach(int i_or_o, int argc)
    \brief Zwraca pozycje nazwy pliku wczytywanego/zapisywanego
    \param i_or_o Zmienna do okreœlenia czy wczytujemy czy zapisujemy
    \param argc Zmienna z liczba wczytanych parametrow przy starcie programu
*/
int pozycja_pliku_w_argumentach(int i_or_o, int argc);

/*! \fn void wczytaj_rozmiary_tablicy(Area* mapa, Players* gracze, FILE** plik)
    \brief Wczytuje ilosc kolumn i wierszy tablicy z rybami
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param plik Wskaznik na plik, do ktorego wczytujemy/zapisujemy
*/
void wczytaj_rozmiary_tablicy(Area* mapa, Players* gracze, FILE** plik);

/*! \fn void wczytaj_dane_tablicy(Area* mapa, Player* gracz, FILE** plik)
    \brief Wczytuje pozostale dane
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param plik Wskaznik na plik, do ktorego wczytujemy/zapisujemy
*/
void wczytaj_dane_tablicy(Area* mapa, Players* gracze, FILE** plik);

/*! \fn void wczytaj_plansze(Area* mapa, Players* gracze, FILE** plik)
    \brief Wczytuje plansze
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param plik Wskaznik na plik, do ktorego wczytujemy/zapisujemy
*/
void wczytaj_plansze(Area* mapa, Players* gracze, FILE** plik);

/*! \fn void usun_puste(Area* mapa, Players* gracze, FILE** plik)
    \brief Usuwa puste znaki w linii
    \param mapa Mapa z rybami
    \param gracze Tablica z graczami
    \param plik Wskaznik na plik, do ktorego wczytujemy/zapisujemy
*/
void usun_puste(Area* mapa, Players* gracze, FILE** plik);


void czy_poprawny_znak(Area* mapa, Players* gracze, int ch, int (*znak) (int ch));


void zapisz_plik(Area* mapa, Players* gracze, FILE** plik);

#endif // R_W_FUNC_H_
