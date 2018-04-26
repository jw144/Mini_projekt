/*! \file defines.h
    \brief Biblioteka ze strukturami i definami
*/

#ifndef DEFINES_H_
#define DEFINES_H_

/*!
    \brief Typedef struktury zawierajaca dane jednej komorki
*/
typedef struct tile
{
    //! Ilosc ryb w danej komorce
    char ryby;

    //! Numer gracza w danej komorce
    char gracz;
} Tile;

/*!
    \brief Typedef struktury zawierajaca plansze, na ktorej gramy
*/
typedef struct area
{
    //! Ilosc kolumn
    int n;

    //! Ilosc wierszy
    int m;

    //! Tablica z plansza
    Tile** tab;
} Area;


/*!
    \brief Typedef struktury zawierajaca parametry gracza
*/
typedef struct player
{
    //! Ilosc punktow
    int punkty;

    //! Nazwa gracza
    char* nazwa_gracza;

    //! Numer gracza
    char numer;
} Player;

/*! \def SIZE_PLAYER_NAME
    \brief Definiuje tymczasowa dlugosc nazwy gracza
*/
#define SIZE_PLAYER_NAME 20

#define MAX_PLAYERS 9

#define MAX_INPUT_ARGUMENTS 5

#define INPUT 0

#define READ_SYMBOL "r"

#define WRITE_SYMBOL "w"


#endif // DEFINES_H_
