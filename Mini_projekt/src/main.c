/*! \file main.c
    \brief Glowny plik
*/

#include "../lib/defines.h"
#include "../lib/r_w_func.h"
#include "../lib/memory_handling.h"
#include <stdio.h>


/*! \fn int main(int argc, char** argv)
    \brief Funkcja glowna
*/
int main(int argc, char** argv)
{
    Area mapa;      //Deklaracja mapy
    FILE* plik;     //Deklaracja zmiennej typu FILE na pliki wejscia/wyjscia
    Player* gracz;  //Deklaracja parametrów gracza

    otworz_plik(argc, argv, &plik, INPUT, &mapa, &gracz);       //Otwiera plik wejsciowy
    wczytaj_rozmiary_tablicy(&mapa, &plik, &gracz);             //Wczytuje parametry tablicy
    przydziel(&mapa, &gracz);                                   //Alokuje pamiec do tablic

    wczytaj_dane_tablicy(&mapa, &gracz, &plik);                        //Wczytuje pozostale dane
    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        printf("%d %d %d\n", gracz[i].numer, gracz[i].punkty, gracz[i].nazwa_gracza[i]);
    }
    zamknij_plik(&plik);

    //Zwalnia pamiec
    printf("coo.avi\n");
    zwolnij(&mapa, &gracz);
    return 0;
}
