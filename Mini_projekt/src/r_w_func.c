/*! \file r_w_func.c
    \brief Plik definiujacy funkcje zawarte w r_w_func.h
*/

#include "../lib/r_w_func.h"
#include "../lib/defines.h"
#include "../lib/memory_handling.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void otworz_plik(Area* mapa, Players* gracze, FILE** plik, int i_or_o, int argc, char** argv)
{
    char* nazwa_pliku = argv[pozycja_pliku_w_argumentach(argc, i_or_o)];    //Nazwa pliku znajduje sie na 3 lub 4 parametrze
    char* sposob_otwarcia = (i_or_o == 0) ? READ_SYMBOL : WRITE_SYMBOL;     //Przypisuje "r" lub "w" w zaleznosci od tego czy wczytujemy czy zapisujemy
    *plik = NULL;
    *plik = fopen(nazwa_pliku, sposob_otwarcia);
    if(*plik == NULL)
    {
        program_error(mapa, gracze, BAD_LOADING, WRONG_DATA);
        return;
    }
    return;
}

void zamknij_plik(FILE** plik)
{
    fclose(*plik);
    return;
}

int pozycja_pliku_w_argumentach(int i_or_o, int argc)
{
    return argc - 2 + i_or_o;
}

void wczytaj_rozmiary_tablicy(Area* mapa, Players* gracze, FILE** plik)
{
    if(fscanf(*plik, "%d %d", &mapa->m, &mapa->n) != 2)
    {
        program_error(mapa, gracze, BAD_SIZES, WRONG_DATA);
        return;
    }
    if(mapa->m < 0 && mapa->n < 0)
    {
        program_error(mapa, gracze, BAD_SIZES, WRONG_DATA);
        return;
    }
    usun_puste(mapa, gracze, plik);
    return;
}


void wczytaj_dane_tablicy(Area* mapa, Players* gracze, FILE** plik)
{
    wczytaj_plansze(mapa, gracze, plik);
    wczytaj_graczy(mapa, gracze, plik);
    return;
}

void wczytaj_plansze(Area* mapa, Players* gracze, FILE** plik)
{
    int ch;
    for(int i = 0; i < mapa->m; i++)
    {
        wczytaj_plansze_ryba(mapa, gracze, plik, i, 0);
        wczytaj_plansze_gracz(mapa, gracze, plik, i, 0);

        for(int j = 1; j < mapa->n; j++)
        {

            ch = fgetc(*plik);
            czy_poprawny_znak(mapa, gracze, ch, &isspace);  //Usuwa spacje pomiedzy danymi i sprawdza czy to spacja

            wczytaj_plansze_ryba(mapa, gracze, plik, i, j);
            wczytaj_plansze_gracz(mapa, gracze, plik, i, j);
        }
        usun_puste(mapa, gracze, plik);
    }
    return;
}
void wczytaj_plansze_gracz(Area* mapa, Players* gracze, FILE** plik, int i, int j)
{
    int ch;
    ch = fgetc(*plik);
    czy_poprawny_znak(mapa, gracze, ch, &isdigit);
    mapa->tab[i][j].gracz = ch - '0';
    return;
}

void wczytaj_plansze_ryba(Area* mapa, Players* gracze, FILE** plik, int i, int j)
{
    int ch;
    ch = fgetc(*plik);
    czy_poprawny_znak(mapa, gracze, ch, &isdigit);
    mapa->tab[i][j].ryby = ch - '0';
    if(mapa->tab[i][j].ryby > MAX_NUM_OF_FISH)
    {
        program_error(mapa, gracze, BAD_INPUT, WRONG_DATA);
        return;
    }
    return;
}

void wczytaj_graczy(Area* mapa, Players* gracze, FILE** plik)
{
    int ch;
    int idx = 0;
    int temp = 1;
    gracze->num_of_players = -1;
    do
    {
        ch = fgetc(*plik);
        gracze->num_of_players++;
        if(gracze->num_of_players > 9) //Sprawdzenie ilosci graczy
        {
            program_error(mapa, gracze, BAD_INPUT, WRONG_DATA);
            return;
        }

        przydziel_nazwa(mapa, gracze);
        idx = 0;
        do
        {
            czy_poprawny_znak(mapa, gracze, ch, &isgraph);
            gracze->parameters[gracze->num_of_players].nazwa_gracza[idx] = ch;

            idx++;
            temp = 1;
            if(temp * SIZE_PLAYER_NAME - 2 < idx)
            {
                temp++;
              realloc_nazwa(mapa, gracze, temp);
            }
            ch = fgetc(*plik);
        }while(ch != ' ');
        gracze->parameters[gracze->num_of_players].nazwa_gracza[idx] = '\0';

        ch = fgetc(*plik);
        czy_poprawny_znak(mapa, gracze, ch, &isdigit);
        gracze->parameters[gracze->num_of_players].numer = ch - '0';

        ch = fgetc(*plik);
        czy_poprawny_znak(mapa, gracze, ch, &isspace);

        ch = fgetc(*plik);
        gracze->parameters[gracze->num_of_players].punkty = 0;
        do
        {
            czy_poprawny_znak(mapa, gracze, ch, &isdigit);
            gracze->parameters[gracze->num_of_players].punkty = gracze->parameters[gracze->num_of_players].punkty * 10 + ch - '0';
            ch = fgetc(*plik);
        }while(ch >= '0' && ch <= '9');

        if(ch != '\n' && ch != EOF)
        {
            usun_puste(mapa, gracze, plik);
        }
    }while(ch != EOF);
    return;
}

void usun_puste(Area* mapa, Players* gracze, FILE** plik)
{
    int ch = fgetc(*plik);
    if(ch != '\n')
    {
        do
        {
            if( ch != ' ')
            {
                program_error(mapa, gracze, BAD_INPUT, WRONG_DATA);
                return;
            }
            ch = fgetc(*plik);
        }while(ch != '\n');
    }
    return;
}

void czy_poprawny_znak(Area* mapa, Players* gracze, int ch, int (*znak) (int ch))
{
    if(znak(ch) == 0)
    {
        program_error(mapa, gracze, BAD_INPUT, WRONG_DATA);
        return;
    }
    return;
}

void zapisz_plik(Area* mapa, Players* gracze, FILE** plik)
{
    fprintf(*plik, "%d %d\n", mapa->m, mapa->n);
    for(int i = 0; i < mapa->m; i++)
    {
        fprintf(*plik, "%d%d", mapa->tab[i][0].ryby, mapa->tab[i][0].gracz);
        for(int j = 1; j < mapa->n; j++)
        {
            fprintf(*plik, " %d%d", mapa->tab[i][j].ryby, mapa->tab[i][j].gracz);
        }
        fprintf(*plik, "\n");
    }
    for(int i = 0; i <= gracze->num_of_players; i++)
    {
        fprintf(*plik, "%s %d %d\n", gracze->parameters[i].nazwa_gracza, gracze->parameters[i].numer, gracze->parameters[i].punkty);
    }
    return;
}
