/*! \file memory_handling.c
    \brief Plik definiujacy funkcje zawarte w memory_handling.h
*/

#include "../lib/memory_handling.h"
#include "../lib/defines.h"

#include <stdlib.h>
#include <stdio.h>

void przydziel(Area* mapa, Player** gracz)
{
    przydziel_area(mapa, gracz);
    przydziel_player(gracz, mapa);
    return;
}

void przydziel_area(Area* mapa, Player** gracz)
{
    mapa->tab = malloc(sizeof(Tile*) * mapa->m);
    if(mapa->tab == NULL)
    {
        zwolnij(mapa, gracz);
        exit(3);
    }
    for(int i = 0; i < mapa->m; i++)
    {
        mapa->tab[i] = malloc(sizeof(Tile) * mapa->n);
        if(mapa->tab[i] == NULL)
        {
            zwolnij(mapa, gracz);
            exit(3);
        }
    }
    return;
}

void przydziel_player(Player** gracz, Area* mapa)
{
    *gracz = malloc(sizeof(Player*) * MAX_PLAYERS);
    if(*gracz == NULL)
    {
        zwolnij(mapa, gracz);
        exit(3);
    }
    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        (*gracz)[i].nazwa_gracza = malloc(sizeof(char*) * SIZE_PLAYER_NAME);
        if((*gracz)[i].nazwa_gracza == NULL)
        {
            zwolnij(mapa, gracz);
            exit(3);
        }
    }
    return;
}

void zwolnij(Area* mapa, Player** gracz)
{
 //   zwolnij_area(mapa);
 //   zwolnij_player(gracz);
    return;
}

void zwolnij_area(Area* mapa)
{
    for(int i = 0; i < mapa->m; i++)
    {
        free(mapa->tab[i]);
    }
    free(mapa->tab);
    return;
}

void zwolnij_player(Player** gracz)
{
    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        free((*gracz)[i].nazwa_gracza);
    }
    free(*gracz);
    return;
}
