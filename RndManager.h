//
// Created by Thomas Herr on 2017-07-24.
//

#ifndef COMP2006_ASSIGNMENT3_ROUNDMANAGER_H
#define COMP2006_ASSIGNMENT3_ROUNDMANAGER_H

#include "Rnd.h"

using namespace std;

/**
 * This class exists to store cards played during rounds of pegging
 */
class rndManager {
    private:
        vector<rnd> rounds;

    public:
        void startNew() {
            rnd newRound = rnd();
            rounds.push_back(newRound);
        }
        /**
         * Get the most recent round
         * @return
         */
        rnd* getCurrent() {
            return &rounds.at(rounds.size()-1);
        }
        /**
         * Go through all rounds and return a vector containing all cards played
         * @return
         */
//        vector<card> returnAll() {
//
//        }
};


#endif //COMP2006_ASSIGNMENT3_ROUNDMANAGER_H
