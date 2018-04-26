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
    usun_puste(mapa, gracze, plik);
    return;
}


void wczytaj_dane_tablicy(Area* mapa, Players* gracze, FILE** plik)
{
    wczytaj_plansze(mapa, gracze, plik);
 /*   int ch;
    int idx = 0;
    int wiersz = -1;
    do
    {
        ch = fgetc(*plik);
        wiersz++;
        idx = 0;
        do
        {
            czy_poprawny_znak(ch, &isgraph, mapa, gracz);
            (*gracz)[wiersz].nazwa_gracza[idx] = ch;
            idx++;
            if()
            {
                zrobiæ w³asnego stringa
            }
            ch = fgetc(*plik);
        }while(ch != ' ');
        ch = fgetc(*plik);
        czy_poprawny_znak(ch, &isdigit, mapa, gracz);
        (*gracz)[wiersz].numer = ch - '0';
        ch = fgetc(*plik);
        czy_poprawny_znak(ch, &isspace, mapa, gracz);
        ch = fgetc(*plik);
        (*gracz)[wiersz].punkty = 0;
        do
        {
            czy_poprawny_znak(ch, &isdigit, mapa, gracz);
            (*gracz)[wiersz].punkty = (*gracz)[wiersz].punkty * 10 + ch - '0';
            ch = fgetc(*plik);
        }while(ch >= '0' && ch <= '9');
        if(ch != '\n' && ch != EOF)
        {
            usun_puste(mapa, gracze, plik);
        }
    }while(ch != EOF);*/
    return;
}

void wczytaj_plansze(Area* mapa, Players* gracze, FILE** plik)
{
    int ch;
    for(int i = 0; i < mapa->m; i++)
    {
        ch = fgetc(*plik);
        czy_poprawny_znak(mapa, gracze, ch, &isdigit);
        mapa->tab[i][0].ryby = ch - '0';

        ch = fgetc(*plik);
        czy_poprawny_znak(mapa, gracze, ch, &isdigit);
        mapa->tab[i][0].gracz = ch - '0';

        for(int j = 1; j < mapa->n; j++)
        {

            ch = fgetc(*plik);
            czy_poprawny_znak(mapa, gracze, ch, &isspace);  //Usuwa spacje pomiedzy danymi i sprawdza czy to spacja

            ch = fgetc(*plik);
            czy_poprawny_znak(mapa, gracze, ch, &isdigit);
            mapa->tab[i][j].ryby = ch - '0';

            ch = fgetc(*plik);
            czy_poprawny_znak(mapa, gracze, ch, &isdigit);
            mapa->tab[i][j].gracz = ch - '0';
        }
        usun_puste(mapa, gracze, plik);
    }
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
        fprintf(stderr, "Blad danych planszy\n");
        zwolnij(mapa, gracze);
        exit(2);
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
    return;
}
