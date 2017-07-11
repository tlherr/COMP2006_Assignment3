/**
 * Thomas Herr
 * 200325519
 * COMP2006 Assignment 3/4
 */

#include <iostream>
#include <locale>
#include <io.h>
#include <afxres.h>
#include "Cards.h"
#include "Deck.h"
#include "Player.h"
#include "Cribbage.h"

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
        SetConsoleOutputCP(CP_UTF8);
    #elif defined(_WIN64)
        SetConsoleOutputCP(CP_UTF8);
    #endif

    cribbage game = cribbage();

    /**
     * Elicit user input as to how many players are playing the game
     * (with valid options consisting of 2, 3, and 4 players only, with some error checking)
     */
    game.getSetupInfo();


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