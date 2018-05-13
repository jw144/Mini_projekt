/*! \file inter_mode.c
    \brief Plik definiujacy funkcje zawarte w inter_mode.h
*/

#include "../lib/inter_mode.h"
#include "../lib/defines.h"
#include "../lib/game.h"
#include <curses.h>
#include <string.h>

void tryb_manual(Area* mapa, Players* gracze, int argc, char** argv)
{
    int phase = faza_gry(argv[1]);
    Parameters* My = czy_jest_gracz(mapa, gracze, phase);
    if(phase == 0)
    {
        czy_jest_miejsce(mapa, gracze, My, argv[2]);
    }
    else
    {
        czy_jest_ruch(mapa, gracze, My);
    }

    initscr();
    curs_set(0);

    Par highlight;  //Wspolrzednie podkreslenia
    highlight.x = 0;
    highlight.y = 0;

    Par size_area_win;  //Maksymalna wielkosc tablicy
    size_area_win.x = MAX_AREA_WIN_X > 1 + 2 * mapa->m ? 1 + 2 * mapa->m : MAX_AREA_WIN_X;
    size_area_win.y = MAX_AREA_WIN_Y > 1 + 3 * mapa->n ? 1 + 3 * mapa->n : MAX_AREA_WIN_Y;

    WINDOW* area_win = make_win(size_area_win.x, size_area_win.y, 0, 0);    //Tworzy okno z tablica z rybami
    keypad(area_win, TRUE); //Zezwala na korzystanie ze strzalek

    uzupelnij_tablice(mapa, &area_win, size_area_win.y);
    wypisz_tablice(mapa, &area_win, highlight); //Wypisanie tablicy przed zmianami
    wrefresh(area_win);

    int temp = 0;
    int ch;
    do
    {
        ch = wgetch(area_win);
        if(ch == KEY_RIGHT && highlight.y < mapa->n - 1)
        {
            highlight.y++;
        }
        else if(ch == KEY_LEFT && highlight.y > 0)
        {
            highlight.y--;
        }
        else if(ch == KEY_UP && highlight.x > 0)
        {
            highlight.x--;
        }
        else if(ch == KEY_DOWN && highlight.x < mapa->m - 1)
        {
            highlight.x++;
        }
        else if(ch == 10)
        {
            if(phase == 0)
            {
                temp = manual_placement(mapa, gracze, highlight, My);
                if(temp == 1)
                {
                    break;
                }
            }
            else
            {
                temp = manual_movement(mapa, gracze, highlight, My, temp);
                if(temp == 2)
                {
                    break;
                }
            }
        }
        wypisz_tablice(mapa, &area_win, highlight);
    }while(true);
    endwin();
    return;
}
void uzupelnij_tablice(Area* mapa, WINDOW** area_win, int area_win_y)
{
    for(int i = 0; i < mapa->m; i++)
    {
        for(int j = 1; j < mapa->n; j++)
        {
            mvwprintw(*area_win, 1 + 2 * i, 3 * j, "|");
        }
        for(int j = 1; j < area_win_y - 1; j++)
        {
            mvwprintw(*area_win, 2 + 2 * i, j, "-");
        }
    }
    return;
}

void wypisz_tablice(Area* mapa, WINDOW** area_win, Par highlight)
{
    Par temp;   //Sluzy do obliczania kiedy tablica musi zostac przesunieta
    temp.x = highlight.x > 9 ? highlight.x - 9 : 0;
    temp.y = highlight.y > 9 ? highlight.y - 9 : 0;

    Par size_area;  //Sluzy do okreslenia wielkosci tablicy, do ktorej wypisujemy znaki
    size_area.x = mapa->m > 10 ? 10 : mapa->m;
    size_area.y = mapa->n > 10 ? 10 : mapa->n;

    for(int i = 0; i < size_area.x; i++)
    {
        for(int j = 0; j < size_area.y; j++)
        {
            if(i + temp.x == highlight.x && j + temp.y == highlight.y)  //Podswietlenie obecnego wyboru
            {
                wattron(*area_win, A_REVERSE);
            }
            mvwprintw(*area_win, 1 + 2 * i, 1 + 3 * j, "%d%d", mapa->tab[i + temp.x][j + temp.y].ryby, mapa->tab[i + temp.x][j + temp.y].gracz);
            wattroff(*area_win, A_REVERSE);
        }
    }
    return;
}

WINDOW* make_win(int height, int width, int startx, int starty)
{
    WINDOW* win = newwin(height, width, startx, starty);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');   //Wartosci dla poszczegolnych krawedzi/wierzcholkow
    wrefresh(win);
    return win;
}

int faza_gry(char* phase)
{
    if(strcmp(phase, PHASE_PLACEMENT) == 0)
    {
        return 0;
    }
    return 1;
}
