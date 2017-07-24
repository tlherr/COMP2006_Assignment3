//
// Created by Thomas Herr on 2017-07-24.
//

#ifndef COMP2006_ASSIGNMENT3_ROUNDMANAGER_H
#define COMP2006_ASSIGNMENT3_ROUNDMANAGER_H

#include "Round.h"

/**
 * This class exists to store cards played during rounds of pegging
 */
class roundManager {
    private:
        vector<round> rounds;

    public:
        round& startNew() {
            round newRound = round();
            rounds.push_back(newRound);
            return newRound;
        }
        /**
         * Go through all rounds and return a vector containing all cards played
         * @return
         */
        vector<card> returnAll() {

        }
};


#endif //COMP2006_ASSIGNMENT3_ROUNDMANAGER_H
