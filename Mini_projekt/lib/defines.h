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
typedef struct parameters
{
    //! Ilosc punktow
    int punkty;

    //! Nazwa gracza
    char* nazwa_gracza;

    //! Numer gracza
    char numer;
} Parameters;

/*!
    \brief Typedef struktury zawierajaca tablice graczy
*/
typedef struct players
{
    //!Ilosc graczy
    int num_of_players;

    //!Parametry gracza
    Parameters* parameters;
}Players;

/*! \def SIZE_PLAYER_NAME
    \brief Definiuje tymczasowa dlugosc nazwy gracza
*/
#define SIZE_PLAYER_NAME 20

/*! \def MAX_PLAYERS
    \brief Definiuje maksymalna ilosc graczy
*/
#define MAX_PLAYERS 9

/*! \def MAX_INPUT_ARGUMENTS
    \brief Definiuje maksymalna ilosc argumentow wejsciowych
*/
#define MAX_INPUT_ARGUMENTS 5

/*! \def MAX_NUM_OF_FISH
    \brief Definiuje maksymalna ilosc ryb
*/
#define MAX_NUM_OF_FISH 3

/*! \def INPUT
    \brief Definiuje liczbe dla pliku wejsciowego
*/
#define INPUT 0

/*! \def OUTPUT
    \brief Definiuje liczbe dla pliku wyjsciowego
*/
#define OUTPUT 1

/*! \def READ_SYMBOL
    \brief Definiuje symbol wczytania
*/
#define READ_SYMBOL "r"

/*! \def WRITE_SYMBOL
    \brief Definiuje symbol wypisywania
*/
#define WRITE_SYMBOL "w"

/*! \def WRONG_DATA
    \brief Definiuje kod bledu dla zlych danych
*/
#define WRONG_DATA 2

/*! \def PROGRAM_ERROR
    \brief Definiuje kod bledu dla bledu programu
*/
#define PROGRAM_ERROR 3

/*! \def BAD_LOADING
    \brief Definiuje wiadomosc w przypadku bledu otwarcia pliku
*/
#define BAD_LOADING "Nie mozna otworzyc pliku"

/*! \def BAD_SIZES
    \brief Definiuje wiadomosc w przypadku blednych rozmiarow planszy
*/
#define BAD_SIZES "Blad wczytywania rozmiarow planszy"

/*! \def BAD_INPUT
    \brief Definiuje wiadomosc w przypadku blednych danych
*/
#define BAD_INPUT "Blad danych"

/*! \def BAD_ALLOCATION
    \brief Definiuje wiadomosc w przypadku nie zaalokowania pamieci
*/
#define BAD_ALLOCATION "Nie mozna zaalokowac pamieci"

#endif // DEFINES_H_
