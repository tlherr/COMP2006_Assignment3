//
// Created by Thomas Herr on 2017-07-24.
//

#ifndef COMP2006_ASSIGNMENT3_ROUND_H
#define COMP2006_ASSIGNMENT3_ROUND_H

#include "Hand.h"
#include "Player.h"

using namespace std;

/**
 * Rounds contain cards and the mechanisms to award and score points
 */
class rnd {
    private:
        const int ROUND_MAX_COUNT = 31;
        int count;
        bool complete;
        hand cardsPlayed;

    public:
        rnd(){
            count = 0;
            cardsPlayed = hand();
            complete = false;
        }

        int getCount() const {
            return count;
        }

        /**
         * Checks to see if the match is complete
         * @return
         */
        bool isComplete() {
            return complete;
        }
        /**
         * Checks the score to determine if a user can play a card
         * @return boolean true if user can play specified card without going over limit, false if cannot
         */
        bool canPlay(card toBePlayed) {
            return ((toBePlayed.getValue()+count)<ROUND_MAX_COUNT);
        }
        /**
         * Play a card, will automatically assign points if points necessary
         * @param cardPlayer
         * @param cardPlayed
         * @return
         */
        void play(player& cardPlayer, card cardPlayed) {
            cardsPlayed.pickup(cardPlayed);
            count+=cardPlayed.getValue();
            int pointsEarned = checkScore();
            cardPlayer.addScore(pointsEarned);
        }

       /**
        * Possible scoring points for pegging
        * Fifteen: For adding a card that makes the total 15 Peg 2
        * Pair: For adding a card of the same rank as the card just played Peg 2
        * Triplet: For adding the third card of the same rank. Peg 6
        * Four: (also called "Double Pair" or "Double Pair Royal")
        * For adding the fourth card of the same rank Peg 12
        * For a sequence of three Peg 3
        * For a sequence of four. Peg 4
        * For a sequence of five. Peg 5
        */
        int checkScore() {
            return 0;
       }



};


#endif //COMP2006_ASSIGNMENT3_ROUND_H
