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
    przydziel_players(mapa, gracze);
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

void przydziel_players(Area* mapa, Players* gracze)
{
    gracze->parameters = malloc(sizeof(Parameters) * MAX_PLAYERS);
    if(gracze->parameters == NULL)
    {
        program_error(mapa, gracze, BAD_ALLOCATION, PROGRAM_ERROR);
        return;
    }
    return;
}

void zwolnij(Area* mapa, Players* gracze)
{
    zwolnij_area(mapa);
    zwolnij_players(gracze);
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

void zwolnij_players(Players* gracze)
{
    for(int i = 0; i < gracze->num_of_players; i++)
    {
        free(gracze->parameters[i].nazwa_gracza);
    }
    free(gracze->parameters);
    return;
}

void program_error(Area* mapa, Players* gracze, char* message, int error_number)
{
    zwolnij(mapa, gracze);
    fprintf(stderr, "%s\n", message);
    exit(error_number);
    return;
}

void przydziel_nazwa(Area* mapa, Players* gracze)
{
    gracze->parameters[gracze->num_of_players - 1].nazwa_gracza = malloc(sizeof(char) * SIZE_PLAYER_NAME);
    if(gracze->parameters[gracze->num_of_players - 1].nazwa_gracza == NULL)
    {
        program_error(mapa, gracze, BAD_ALLOCATION, PROGRAM_ERROR);
        return;
    }
    return;
}

void realloc_nazwa(Area* mapa, Players* gracze, int temp)
{
    char* temp_tab = gracze->parameters[gracze->num_of_players - 1].nazwa_gracza;
    temp_tab = realloc(gracze->parameters[gracze->num_of_players - 1].nazwa_gracza, sizeof(char) * SIZE_PLAYER_NAME * temp);
    if(temp_tab == NULL)
    {
        program_error(mapa, gracze, BAD_ALLOCATION, PROGRAM_ERROR);
        return;
    }
    else
    {
        gracze->parameters[gracze->num_of_players - 1].nazwa_gracza = temp_tab;
    }
    return;
}
