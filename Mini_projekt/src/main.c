/*! \file main.c
    \brief Glowny plik
*/

#include "../lib/defines.h"
#include "../lib/r_w_func.h"
#include "../lib/memory_handling.h"


/*! \fn int main(int argc, char** argv)
    \brief Funkcja glowna
*/
int main(int argc, char** argv)
{
    //Deklaracja mapy
    Area mapa;

    //Deklaracja parametrów gracza
    Player gracz;

    //Wczytuje parametry tablicy
    wczytaj_rozmiary_tablicy(&mapa);

    //Alokuje pamiec do tablic
    przydziel(&mapa, &gracz);

    //Wczytuje pozostale dane
    wczytaj_dane_tablicy(&mapa, &gracz);

    //Zwalnia pamiec
    zwolnij(&mapa, &gracz);
    return 0;
}
