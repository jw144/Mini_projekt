/*! \file memory_handling.c
    \brief Plik definiujacy funkcje zawarte w memory_handling.h
*/

#include "../lib/memory_handling.h"
#include "../lib/defines.h"

#include <stdlib.h>

/*! \fn void przydziel(Area* mapa, Player* gracz)
    \brief Przydziela pamiec do tablic
    \param mapa Mapa z rybami
    \param gracz Parametry gracza
*/
void przydziel(Area* mapa, Player* gracz)
{
    przydziel_area(mapa);
    przydziel_player(gracz);
    return;
}

/*! \fn void przydziel_area(Area* mapa)
    \brief Przydziela pamiec do tablicy z rybami
    \param mapa Mapa z rybami
*/
void przydziel_area(Area* mapa)
{
    mapa->tab = malloc(sizeof(Tile*) * mapa->m);
    if(mapa->tab == NULL)
    {
        free(mapa->tab);
        exit(3);
    }
    for(int i = 0; i < mapa->m; i++)
    {
        mapa->tab[i] = malloc(sizeof(Tile) * mapa->n);
        if(mapa->tab[i] == NULL)
        {
            free(mapa->tab);
            exit(3);
        }
    }
    return;
}

/*! \fn void przydziel_player(Player* gracz)
    \brief Przydziela pamiec do tablicy z nazwa gracza
    \param gracz Parametry gracza
*/
void przydziel_player(Player* gracz)
{
    gracz->nazwa_gracza = malloc(sizeof(char) * SIZE_PLAYER_NAME);
    if(gracz->nazwa_gracza == NULL)
    {
        free(gracz->nazwa_gracza);
        exit(3);
    }
    return;
}

/*! \fn void zwolnij(Area* mapa, Player* gracz)
    \brief Zwalnia pamiec
    \param mapa Mapa z rybami
    \param gracz Parametry gracza
*/
void zwolnij(Area* mapa, Player* gracz)
{
    free(mapa->tab);
    free(gracz->nazwa_gracza);
    return;
}
