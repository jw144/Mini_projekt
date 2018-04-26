/*! \file memory_handling.c
    \brief Plik definiujacy funkcje zawarte w memory_handling.h
*/

#include "../lib/memory_handling.h"
#include "../lib/defines.h"

#include <stdlib.h>
#include <stdio.h>

void przydziel(Area* mapa, Players* gracze)
{
    przydziel_area(mapa, gracze);
    przydziel_player(mapa, gracze);
    return;
}

void przydziel_area(Area* mapa, Players* gracze)
{
    mapa->tab = malloc(sizeof(Tile*) * mapa->m);
    if(mapa->tab == NULL)
    {
        program_error(mapa, gracze, BAD_ALLOCATION, PROGRAM_ERROR);
        return;
    }
    for(int i = 0; i < mapa->m; i++)
    {
        mapa->tab[i] = malloc(sizeof(Tile) * mapa->n);
        if(mapa->tab[i] == NULL)
        {
            program_error(mapa, gracze, BAD_ALLOCATION, PROGRAM_ERROR);
            return;
        }
    }
    return;
}

void przydziel_player(Area* mapa, Players* gracze)
{
    gracze->parameters = malloc(sizeof(Players) * MAX_PLAYERS);
    if(gracze->parameters == NULL)
    {
        program_error(mapa, gracze, BAD_ALLOCATION, PROGRAM_ERROR);
        return;
    }
    return;
}

void zwolnij(Area* mapa, Players* gracz)
{
    zwolnij_area(mapa);
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

void zwolnij_player(Players* gracz)
{
    for(int i = 0; i < MAX_PLAYERS; i++)
    {
 //       free((*gracz)[i].nazwa_gracza);
    }
 //   free(*gracz);
    return;
}

void program_error(Area* mapa, Players* gracze, char* message, int error_number)
{
    zwolnij(mapa, gracze);
    fprintf(stderr, "%s\n", message);
    exit(error_number);
    return;
}
