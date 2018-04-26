/*! \file r_w_func.c
    \brief Plik definiujacy funkcje zawarte w r_w_func.h
*/

#include "../lib/r_w_func.h"
#include "../lib/defines.h"
#include "../lib/memory_handling.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void otworz_plik(int argc, char** argv, FILE** plik, int i_or_o, Area* mapa, Player** gracz)
{
    char* nazwa_pliku = argv[pozycja_pliku_w_argumentach(argc, i_or_o)];
    char* sposob_otwarcia = (i_or_o == 0) ? READ_SYMBOL : WRITE_SYMBOL;
    *plik = NULL;
    *plik = fopen(nazwa_pliku, sposob_otwarcia);
    if(*plik == NULL)
    {
        zwolnij(mapa, gracz);
        perror("Nie mozna otworzyc pliku");
        exit(2);
    }
    return;
}

void zamknij_plik(FILE** plik)
{
    fclose(*plik);
    return;
}

int pozycja_pliku_w_argumentach(int argc, int i_or_o)
{
    return argc - 2 + i_or_o;
}

void wczytaj_rozmiary_tablicy(Area* mapa, FILE** plik, Player** gracz)
{
    if(fscanf(*plik, "%d %d", &mapa->m, &mapa->n) != 2)
    {
        fprintf(stderr, "Blad wczytywania rozmiarow planszy\n");
        zwolnij(mapa, gracz);
        exit(2);
    }
    printf("%d %d\n", mapa->n, mapa->m);
    usun_puste(plik, mapa, gracz);
    return;
}

void wczytaj_dane_tablicy(Area* mapa, Player** gracz, FILE** plik)
{
    int ch;
    for(int i = 0; i < mapa->m; i++)
    {
        ch = fgetc(*plik);
        czy_poprawny_znak(ch, &isdigit, mapa, gracz);
        mapa->tab[i][0].ryby = ch - '0';
        ch = fgetc(*plik);
        czy_poprawny_znak(ch, &isdigit, mapa, gracz);
        mapa->tab[i][0].gracz = ch - '0';
        for(int j = 1; j < mapa->n; j++)
        {

            ch = fgetc(*plik);
            czy_poprawny_znak(ch, &isspace, mapa, gracz);
            ch = fgetc(*plik);
            czy_poprawny_znak(ch, &isdigit, mapa, gracz);
            mapa->tab[i][0].ryby = ch - '0';
            ch = fgetc(*plik);
            czy_poprawny_znak(ch, &isdigit, mapa, gracz);
            mapa->tab[i][0].gracz = ch - '0';
        }
        usun_puste(plik, mapa, gracz);
    }
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
          /*  if()
            {
                zrobiæ w³asnego stringa
            }*/
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
            usun_puste(plik, mapa, gracz);
        }
    }while(ch != EOF);
    return;
}

void usun_puste(FILE** plik, Area* mapa, Player** gracz)
{
    int ch = fgetc(*plik);
    if(ch != '\n')
    {
        do
        {
            if( ch != ' ')
            {
                fprintf(stderr, "Blad danych w tablicy\n");
                zwolnij(mapa, gracz);
                exit(2);
            }
            ch = fgetc(*plik);
        }while(ch != '\n');
    }
    return;
}

void czy_poprawny_znak(int ch, int (*znak) (int ch), Area* mapa, Player** gracz)
{
    if(znak(ch) == 0)
    {
        fprintf(stderr, "Blad danych planszy\n");
        zwolnij(mapa, gracz);
        exit(2);
    }
    return;
}
