/**
 * Thomas Herr
 * 200325519
 * COMP2006 Assignment 3/4
 */

#include <iostream>
#include <locale>
#include <time.h>

//OSX Specific Headers
#ifdef __APPLE__
    #include <sys/uio.h>
//Windows Specific Headers
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <io.h>
    #include <windows.h>
#endif

#include "Cards.h"
#include "Deck.h"
#include "Player.h"
#include "Cribbage.h"

#pragma execution_character_set( "utf-8" )

using namespace std;

int main() {

    //Set proper encoding output based on platform to display Unicode suit symbols
    #if defined(__linux__)
        locale::global(locale("en_US.UTF-8"));
        wcout.imbue(locale());
    #elif defined(__APPLE__)
        locale::global(locale("en_US.UTF-8"));
        wcout.imbue(locale());
    #elif defined(_WIN32)
        SetConsoleOutputCP(65001);
    #elif defined(_WIN64)
        SetConsoleOutputCP(65001);
    #endif

    srand(time(NULL));
    cribbage game = cribbage();

    game.run();


    /**
     * Allow the user to control the application with 4 options
     *  -Create a deck
     *  -Shuffle a deck
     *  -Cut the deck
     *  -Exit application
     */




    #if defined(__linux__)
        __pause();
    #elif defined(__APPLE__)
        system( "read -n 1 -s -p \"Press any key to continue...\"" );
    #elif defined(_WIN32)
        system("pause");
    #elif defined(_WIN64)
        system("pause");
    #endif

    return 0;
}