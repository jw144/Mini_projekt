/*! \file main.c
    \brief Glowny plik
*/

#include "../lib/defines.h"
#include "../lib/r_w_func.h"
#include "../lib/memory_handling.h"
#include "../lib/game.h"
#include <stdio.h>


/*! \fn int main(int argc, char** argv)
    \brief Funkcja glowna
*/
int main(int argc, char** argv)
{
    Area mapa;      //Deklaracja mapy
    FILE* plik;     //Deklaracja zmiennej typu FILE na pliki wejscia/wyjscia
    Players gracze;  //Deklaracja tablicy graczy

    otworz_plik(&mapa, &gracze, &plik, INPUT, argc, argv);  //Otwiera plik wejsciowy
    wczytaj_rozmiary_tablicy(&mapa, &gracze, &plik);        //Wczytuje parametry tablicy
    przydziel(&mapa, &gracze);                              //Alokuje pamiec do tablic
    wczytaj_dane_tablicy(&mapa, &gracze, &plik);            //Wczytuje pozostale dane
    zamknij_plik(&plik);                                    //Zamyka plik wejsciowy

    wybor_trybu(&mapa, &gracze, argc, argv);                //Wybiera tryb gry i uruchamia ja

    otworz_plik(&mapa, &gracze, &plik, OUTPUT, argc, argv); //Otwiera plik wejsciowy
    zapisz_plik(&mapa, &gracze, &plik);                     //Zapisuje dane do pliku
    zamknij_plik(&plik);                                    //Zamyka plik wejsciowy
    zwolnij(&mapa, &gracze);                                //Zwalnia pamiec
    return 0;
}
