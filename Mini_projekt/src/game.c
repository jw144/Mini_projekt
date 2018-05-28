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

#define AUTO
void wybor_trybu(Area* mapa, Players* gracze, int argc, char** argv)
{
    #ifdef AUTO
    tryb_auto(mapa, gracze, argc, argv);
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
        if(gracze->num_of_players > 10)
        {
            program_error(mapa, gracze, BAD_INPUT, WRONG_DATA);
            return NULL;
        }
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
            mapa->tab[i][j].najlepsze_pole = 0;
            if(mapa->tab[i][j].gracz == 0 && mapa->tab[i][j].ryby == 1)
            {
                mapa->tab[i][j].najlepsze_pole = 1;
                possible_place++;
            }
            else if(mapa->tab[i][j].gracz == My->numer)
            {
                mapa->tab[i][j].najlepsze_pole = 3;
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
                for(int k = i; k >= 0; k--)
                {
                    if(mapa->tab[k][j].gracz == 0 && mapa->tab[k][j].ryby != 0)
                    {
                        return;
                    }
                }
                for(int k = j; k >= 0; k--)
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

void tryb_auto(Area* mapa, Players* gracze, int argc, char** argv)
{
    int phase = faza_gry(argv[1]);
    Parameters* My = czy_jest_gracz(mapa, gracze, phase);
    if(phase == 0)
    {
        auto_placement(mapa, gracze, argc, argv, My);
    }
    else
    {
        auto_movement(mapa, gracze, argc, argv, My);
    }
    return;
}

void auto_placement(Area* mapa, Players* gracze, int argc, char** argv, Parameters* My)
{
    czy_jest_miejsce(mapa, gracze, My, argv[2]);
    Par backup_place;
    backup_place.x = -1;
    backup_place.y = -1;
    int no_friendly_penguins = 0;
    for(int i = 0; i < mapa->m; i++)
    {
        for(int j = 0; j < mapa->n; j++)
        {
            if(mapa->tab[i][j].najlepsze_pole == 1)
            {
                backup_place.x = i;
                backup_place.y = j;
                no_friendly_penguins = 0;
                for(int k = 0; k < mapa->m; k++)
                {
                    if(mapa->tab[k][j].najlepsze_pole == 3)
                    {
                        no_friendly_penguins = 1;
                        break;
                    }
                }
                for(int k = 0; k < mapa->n; k++)
                {
                    if(mapa->tab[i][k].najlepsze_pole == 3)
                    {
                        no_friendly_penguins = 1;
                        break;
                    }
                }
                if(no_friendly_penguins == 0)
                {
                    mapa->tab[i][j].gracz = My->numer;
                    My->punkty +=  mapa->tab[i][j].ryby;
                    mapa->tab[i][j].ryby = 0;
                    return;
                }
            }
        }
    }
    mapa->tab[backup_place.x][backup_place.y].gracz = My->numer;
    My->punkty +=  mapa->tab[backup_place.x][backup_place.y].ryby;
    mapa->tab[backup_place.x][backup_place.y].ryby = 0;
    return;
}

void best_movement_place(Area* mapa, Players* gracze, Parameters* My, int a, int b, int x_poz, int y_poz)
{

    if(mapa->tab[a+1*x_poz][b+1*y_poz].gracz != My->numer)
    {
        if(mapa->tab[a+1*x_poz][b+1*y_poz].najlepsze_pole != 0)
        {
            mapa->tab[a+1*x_poz][b+1*y_poz].najlepsze_pole == 0;
        }
        enemy_penguins(mapa, gracze, My, a+1*x_poz, b+1*y_poz);
        mapa->tab[a+1*x_poz][b+1*y_poz].najlepsze_pole +=30;
        if(mapa->tab[a+1*x_poz][b+1*y_poz].ryby > 1)
        {
            mapa->tab[a+1*x_poz][b+1*y_poz].najlepsze_pole +=13;
        }
        if(mapa->tab[a+1*x_poz][b+1*y_poz].ryby > 2)
        {
            mapa->tab[a+1*x_poz][b+1*y_poz].najlepsze_pole +=14;
        }
    }
    else
    {
        return;
    }
    if(mapa->tab[a+2*x_poz][b+2*y_poz].gracz != My->numer)
    {
        if(mapa->tab[a+2*x_poz][b+2*y_poz].najlepsze_pole != 0)
        {
            mapa->tab[a+2*x_poz][b+2*y_poz].najlepsze_pole == 0;
        }
        enemy_penguins(mapa, gracze, My, a+2*x_poz, b+2*y_poz);
        mapa->tab[a+2*x_poz][b+2*y_poz].najlepsze_pole +=20;
        if(mapa->tab[a+2*x_poz][b+2*y_poz].ryby > 1)
        {
            mapa->tab[a+2*x_poz][b+2*y_poz].najlepsze_pole +=13;
        }
        if(mapa->tab[a+2*x_poz][b+2*y_poz].ryby > 2)
        {
            mapa->tab[a+2*x_poz][b+2*y_poz].najlepsze_pole +=14;
        }
    }
    else
    {
        return;
    }
    if(mapa->tab[a+3*x_poz][b+3*y_poz].gracz != My->numer)
    {
        if(mapa->tab[a+3*x_poz][b+3*y_poz].najlepsze_pole != 0)
        {
            mapa->tab[a+3*x_poz][b+3*y_poz].najlepsze_pole == 0;
        }
        enemy_penguins(mapa, gracze, My, a+3*x_poz, b+3*y_poz);
        mapa->tab[a+3*x_poz][b+3*y_poz].najlepsze_pole +=10;
        if(mapa->tab[a+3*x_poz][b+3*y_poz].ryby > 1)
        {
            mapa->tab[a+3*x_poz][b+3*y_poz].najlepsze_pole +=13;
        }
        if(mapa->tab[a+3*x_poz][b+3*y_poz].ryby > 2)
        {
            mapa->tab[a+3*x_poz][b+3*y_poz].najlepsze_pole +=14;
        }
    }
    else
    {
        return;
    }
    return;
}

void enemy_penguins(Area* mapa, Players* gracze, Parameters* My, int a, int b)
{

    
        if(mapa->tab[a][b].ryby < 2)

    {

        return;

    }

    
    for(int k = a; k >= 0; k--)
    {
        if(mapa->tab[k][b].gracz != 0)
        {
            if(mapa->tab[k][b].gracz != My->numer)
            {
                mapa->tab[a][b].najlepsze_pole += 5;
                return;
            }
        }
    }
    for(int k = b; k >= 0; k--)
    {
        if(mapa->tab[a][k].gracz != 0)
        {
            if(mapa->tab[a][k].gracz != My->numer)
            {
                mapa->tab[a][b].najlepsze_pole += 5;
                return;
            }
        }
    }
    for(int k = a; k < mapa->m; k++)
    {
        if(mapa->tab[k][b].gracz != 0)
        {
            if(mapa->tab[k][b].gracz != My->numer)
            {
                mapa->tab[a][b].najlepsze_pole += 5;
                return;
            }
        }
    }
    for(int k = b; k < mapa->n; k++)
    {
        if(mapa->tab[a][k].gracz != 0)
        {
            if(mapa->tab[a][k].gracz != My->numer)
            {
                mapa->tab[a][b].najlepsze_pole += 5;
                return;
            }
        }
    }
}

void auto_movement(Area* mapa, Players* gracze, int argc, char** argv, Parameters* My)
{
    czy_jest_ruch(mapa, gracze, My);
    Best_movement movement;
    movement.best = 0;
    movement.x = 0;
    movement.y = 0;
    int is_change = 0;
    for(int i = 0; i < mapa->m; i++)
    {
        for(int j = 0; j < mapa->n; j++)
        {
            if(mapa->tab[i][j].gracz == My->numer)
            {

                is_change = 0;
                for(int k = i; k >= 0; k--)
                {
                    if((mapa->tab[k][j].gracz != 0  || mapa->tab[k][j].ryby == 0) && k != i)
                    {
                        best_movement_place(mapa, gracze, My, k, j, 1, 0);
                        assign_best(mapa, k, j, &movement, 1, 0, &is_change, My);
                        if(is_change == 1)
                        {
                            movement.last_x = i;
                            movement.last_y = j;
                        }
                        break;
                    }
                    if(k == 0 && k != i)
                    {
                        best_movement_place(mapa, gracze, My, k - 1, j, 1, 0);
                        assign_best(mapa, k - 1, j, &movement, 1, 0, &is_change, My);
                        if(is_change == 1)
                        {
                            movement.last_x = i;
                            movement.last_y = j;
                        }
                        break;

                    }
                }
                for(int k = j; k >= 0; k--)
                {
                    if((mapa->tab[i][k].gracz != 0 || mapa->tab[i][k].ryby == 0) && k != j)
                    {
                        best_movement_place(mapa, gracze, My, i, k, 0, 1);
                        assign_best(mapa, i, k, &movement, 0, 1, &is_change, My);
                        if(is_change == 1)
                        {
                            movement.last_x = i;
                            movement.last_y = j;
                        }
                        break;
                    }
                    if(k == 0 && k != j)
                    {
                        best_movement_place(mapa, gracze, My, i, k - 1, 0, 1);
                        assign_best(mapa, i, k - 1, &movement, 0, 1, &is_change, My);
                        if(is_change == 1)
                        {
                            movement.last_x = i;
                            movement.last_y = j;
                        }
                        break;
                    }
                }
                for(int k = i; k < mapa->m; k++)
                {
                    if((mapa->tab[k][j].gracz != 0 || mapa->tab[k][j].ryby == 0) && k != i)
                    {
                        best_movement_place(mapa, gracze, My, k, j, -1, 0);
                        assign_best(mapa, k, j, &movement, -1, 0, &is_change, My);
                        if(is_change == 1)
                        {
                            movement.last_x = i;
                            movement.last_y = j;
                        }
                        break;
                    }
                    if(k == mapa->m - 1 && k != i)
                    {
                        best_movement_place(mapa, gracze, My, k + 1, j, -1, 0);
                        assign_best(mapa, k + 1, j, &movement, -1, 0, &is_change, My);
                        if(is_change == 1)
                        {
                            movement.last_x = i;
                            movement.last_y = j;
                        }
                        break;
                    }
                }
                for(int k = j; k < mapa->n; k++)
                {
                    if((mapa->tab[i][k].gracz != 0 || mapa->tab[i][k].ryby == 0) && k != j)
                    {
                        best_movement_place(mapa, gracze, My, i, k, 0, -1);
                        assign_best(mapa, i, k, &movement, 0, -1, &is_change, My);
                        if(is_change == 1)
                        {
                            movement.last_x = i;
                            movement.last_y = j;
                        }
                        break;
                    }
                    if(k == mapa->n - 1 && k != j)
                    {
                        best_movement_place(mapa, gracze, My, i, k + 1, 0, -1);
                        assign_best(mapa, i, k + 1, &movement, 0, -1, &is_change, My);
                        if(is_change == 1)
                        {
                            movement.last_x = i;
                            movement.last_y = j;
                        }
                        break;
                    }
                }
            }
        }
    }
    mapa->tab[movement.x][movement.y].gracz = My->numer;
    My->punkty += mapa->tab[movement.x][movement.y].ryby;
    mapa->tab[movement.x][movement.y].ryby = 0;
    mapa->tab[movement.last_x][movement.last_y].gracz = 0;
    return;
}

void assign_best(Area* mapa, int a, int b, Best_movement* movement, int x_poz, int y_poz, int* is_change, Parameters* My)
{
    if(mapa->tab[a+1*x_poz][b+1*y_poz].gracz != My->numer)
    {
        if(movement->best < mapa->tab[a+1*x_poz][b+1*y_poz].najlepsze_pole)
        {
            movement->best = mapa->tab[a+1*x_poz][b+1*y_poz].najlepsze_pole;
            movement->x = a+1*x_poz;
            movement->y = b+1*y_poz;
            *is_change = 1;
        }

    }
    else
    {
        return;
    }
    if(mapa->tab[a+2*x_poz][b+2*y_poz].gracz != My->numer)
    {
        if(movement->best < mapa->tab[a+2*x_poz][b+2*y_poz].najlepsze_pole)
        {
            movement->best = mapa->tab[a+2*x_poz][b+2*y_poz].najlepsze_pole;
            movement->x = a+2*x_poz;
            movement->y = b+2*y_poz;
            *is_change = 1;
        }
    }
    else
    {
        return;
    }
    if(mapa->tab[a+3*x_poz][b+3*y_poz].gracz != My->numer)
    {
        if(movement->best < mapa->tab[a+3*x_poz][b+3*y_poz].najlepsze_pole)
        {
            movement->best = mapa->tab[a+3*x_poz][b+3*y_poz].najlepsze_pole;
            movement->x = a+3*x_poz;
            movement->y = b+3*y_poz;
            *is_change = 1;
        }
    }
    else
    {
        return;
    }
    return;
}
