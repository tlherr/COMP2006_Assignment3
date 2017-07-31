/**
 * Thomas Herr
 * 200325519
 * COMP2006 Assignment 3/4
 * OS: OSX/Windows
 * IDE: CLion
 * CMake 3.7.1
 * Apple LLVM version 7.3.0 (clang-703.0.31)
 * Target: x86_64-apple-darwin15.6.0
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

#include "Common.h"
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

    common::pause();

    return 0;
}