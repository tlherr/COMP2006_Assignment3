
#ifndef COMP2006_ASSIGNMENT3_CRIBBAGE_H
#define COMP2006_ASSIGNMENT3_CRIBBAGE_H

using namespace std;

#include "Game.h"
class cribbage : public game {
    protected:
        deck cardDeck;
        enum matchStatus {
            ready = 1,
            dealer_selected = 2,
            crib_created = 3,
            pegging_begin = 4,
            cards_played = 5,
            counting = 6,
            hand_complete = 7,
            max_score_reached = 8
        };

    public:
        cribbage() {
            cardDeck = deck();
            scoreToWin = 121;
            printf("Welcome to Cribbage in C++. Press Q at any time to quit. \n");
        }

        void setup() {
            //Decide dealer (based on rotation or cutting deck if no dealer exists)
            //Shuffle
            //Deal
            //Form Crib
        }

        void play() {
            //Cut
            //Play round
        }

        void count() {
            //Total scores
        }



};


#endif //COMP2006_ASSIGNMENT3_CRIBBAGE_H
