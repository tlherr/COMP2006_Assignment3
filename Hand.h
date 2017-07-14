using namespace std;

#include "Cards.h"
#include <vector>

#ifndef COMP2006_ASSIGNMENT3_HAND_H
#define COMP2006_ASSIGNMENT3_HAND_H

/**
 * Class that represents a collection of cards
 */
class hand {
    private:
        vector<card> cards;
    public:
        void pickup(card pickedUpCard) {
            cards.push_back(pickedUpCard);
        }

        void discard(card discardedCard) {
            for(int i = 0; i < cards.size(); i++) {
                if(cards.at((unsigned int) i).compare(discardedCard)) {
                    cards.erase(cards.begin()+i);
                }
            }
        }

        void discardAll() {
            cards.erase(cards.begin(), cards.end());
        }
};




#endif //COMP2006_ASSIGNMENT3_HAND_H
