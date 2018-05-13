/*! \file game.c
    \brief Plik definiujacy funkcje zawarte w game.h
*/

#include "../lib/game.h"
#include "../lib/defines.h"
#include "../lib/inter_mode.h"
#include "../lib/memory_handling.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void wybor_trybu(Area* mapa, Players* gracze, int argc, char** argv)
{
    #ifdef AUTO
    //Do zrobienia na kolejny raport
    #else
    tryb_manual(mapa, gracze, argc, argv);  //Tryb reczny gry
    #endif // AUTO
    return;
}

int manual_placement(Area* mapa, Players* gracze, Par highlight, Parameters* My)
{
    if(mapa->tab[highlight.x][highlight.y].gracz == 0 && mapa->tab[highlight.x][highlight.y].ryby == 1)
    {
        mapa->tab[highlight.x][highlight.y].gracz = My->numer;
        My->punkty +=  mapa->tab[highlight.x][highlight.y].ryby;
        mapa->tab[highlight.x][highlight.y].ryby = 0;
        return 1;
    }
    return 0;
}

int manual_movement(Area* mapa, Players* gracze, Par highlight, Parameters* My, int temp)
{
    static Par pingwin; //Uzywam statica, bo juz nie chce mi sie kombinowac, moze w przyszlosci zmienie
    if(temp == 0 && mapa->tab[highlight.x][highlight.y].gracz == My->numer) //Wybiera pingwina
    {
        pingwin.x = highlight.x;
        pingwin.y = highlight.y;
        return temp + 1;
    }
    if(temp == 1)   //Sprawdza czy mozna sie przemiescic w wybrane miejsce
    {
        if(pingwin.x != highlight.x && pingwin.y != highlight.y)
        {
            return 0;
        }
        if(pingwin.x != highlight.x)
        {
            for(int i = min_el(highlight.y, pingwin.y) + 1; i < max_el(highlight.y, pingwin.y) - 1; i++)
            {
                if(mapa->tab[highlight.x][i].ryby == 0 || mapa->tab[highlight.x][i].gracz != 0)
                {
                    return 0;
                }
            }
            mapa->tab[highlight.x][highlight.y].gracz = My->numer;
            My->punkty += mapa->tab[highlight.x][highlight.y].ryby;
            mapa->tab[highlight.x][highlight.y].ryby = 0;
            mapa->tab[pingwin.x][pingwin.y].gracz = 0;
            return 2;
        }
        if(pingwin.y != highlight.y)
        {
            for(int i = min_el(highlight.x, pingwin.x) + 1; i < max_el(highlight.x, pingwin.x) - 1; i++)
            {
                if(mapa->tab[i][highlight.y].ryby == 0 || mapa->tab[i][highlight.y].gracz != 0)
                {
                    return 0;
                }
            }
            mapa->tab[highlight.x][highlight.y].gracz = My->numer;
            My->punkty += mapa->tab[highlight.x][highlight.y].ryby;
            mapa->tab[highlight.x][highlight.y].ryby = 0;
            mapa->tab[pingwin.x][pingwin.y].gracz = 0;
            return 2;
        }
        return 1;
    }
    return 0;
}
int min_el(int a, int b)
{
    if(a > b)
    {
        return b;
    }
    return a;
}

int max_el(int a, int b)
{
    if(a > b)
    {
        return a;
    }
    return b;
}

Parameters* czy_jest_gracz(Area* mapa, Players* gracze, int phase)
{
    Parameters* My = NULL;
    for(int i = 0; i < gracze->num_of_players; i++)
    {
        if(strcmp(gracze->parameters[i].nazwa_gracza, OUR_NAME) == 0)
        {
            My = &gracze->parameters[i];
        }
    }
    if(My == NULL && phase == 1)
    {
        program_error(mapa, gracze, BAD_INPUT, WRONG_DATA);
        return NULL;
    }
    if(My == NULL)
    {
        gracze->num_of_players++;
        Parameters* temp = realloc(gracze->parameters, (gracze->num_of_players) * sizeof(Parameters));
        if(temp == NULL)
        {
            program_error(mapa, gracze, BAD_ALLOCATION, PROGRAM_ERROR);
            return NULL;
        }
        gracze->parameters = temp;
        gracze->parameters[gracze->num_of_players - 1].punkty = 0;
        gracze->parameters[gracze->num_of_players - 1].numer = gracze->num_of_players;
        gracze->parameters[gracze->num_of_players - 1].nazwa_gracza = malloc(strlen(OUR_NAME));
        strcpy(gracze->parameters[gracze->num_of_players - 1].nazwa_gracza, OUR_NAME);
    }
    My = &gracze->parameters[gracze->num_of_players - 1];
    return My;
}

void czy_jest_miejsce(Area* mapa, Players* gracze, Parameters* My, char* penguins)
{
    int player_penguins = 0;
    int possible_place = 0;
    for(int i = 0; i < mapa->m; i++)
    {
        for(int j = 0; j < mapa->n; j++)
        {
            if(mapa->tab[i][j].gracz == 0)
            {
                possible_place++;
            }
            else if(mapa->tab[i][j].gracz == My->numer)
            {
                player_penguins++;
            }
        }
    }
    if(possible_place == 0)
    {
        zwolnij(mapa, gracze);
        exit(NO_MOVES);
        return;
    }
    if(player_penguins == penguins[9] - '0')
    {
        zwolnij(mapa, gracze);
        exit(NO_MOVES);
        return;
    }
    return;
}

void czy_jest_ruch(Area* mapa, Players* gracze, Parameters* My)
{
    int possible_place = 0;
    for(int i = 0; i < mapa->m; i++)
    {
        for(int j = 0; j < mapa->n; j++)
        {
            if(mapa->tab[i][j].gracz == My->numer) //Nie mam sily, w przyszlosci to skompresuje
            {
                for(int k = i; k > 0; k--)
                {
                    if(mapa->tab[k][j].gracz == 0 && mapa->tab[k][j].ryby != 0)
                    {
                        return;
                    }
                }
                for(int k = j; k > 0; k--)
                {
                    if(mapa->tab[i][k].gracz == 0 && mapa->tab[i][k].ryby != 0)
                    {
                        return;
                    }
                }
                for(int k = i; k < mapa->m; k++)
                {
                    if(mapa->tab[k][j].gracz == 0 && mapa->tab[k][j].ryby != 0)
                    {
                        return;
                    }
                }
                for(int k = j; k < mapa->n; k++)
                {
                    if(mapa->tab[i][k].gracz == 0 && mapa->tab[i][k].ryby != 0)
                    {
                        return;
                    }
                }
            }
        }
    }
    if(possible_place == 0)
    {
        zwolnij(mapa, gracze);
        exit(NO_MOVES);
        return;
    }
    return;
}
