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


};

#endif //COMP2006_ASSIGNMENT3_COMMON_H
