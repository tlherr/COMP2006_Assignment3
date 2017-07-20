//
// Created by Tom on 7/12/2017.
//

#ifndef COMP2006_ASSIGNMENT3_COMMON_H
#define COMP2006_ASSIGNMENT3_COMMON_H

#include <string>

class common {
    public:
        /**
        * Checks an input string for "q" or "Q" to indicate the user would like to quit
        * @param input
        * @return
        */
        static bool checkForExit(std::string input) {
            return (input=="q" || input=="Q");
        }

        static int random (int low, int high) {
            if (low > high) return high;
            return low + (std::rand() % (high - low + 1));
        }

        static void clearConsole() {
            #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
                        system("cls");
            #elif defined(__linux__)
                        std::cout << "\x1B[2J\x1B[H";
            #endif
        }

    static void pause() {
        #if defined(__linux__)
                __pause();
        #elif defined(__APPLE__)
                system( "read -n 1 -s -p \"Press any key to continue...\"" );
        #elif defined(_WIN32)
                system("pause");
        #elif defined(_WIN64)
                system("pause");
        #endif
    }

};

#endif //COMP2006_ASSIGNMENT3_COMMON_H
