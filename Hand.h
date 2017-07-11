using namespace std;

#include "Cards.h"
#include <vector>

#ifndef COMP2006_ASSIGNMENT3_HAND_H
#define COMP2006_ASSIGNMENT3_HAND_H

/**
 * Class that represents a collection of cards the belong to a player
 */
class hand {
    private:
        vector cards<card>;
    public:
        void pickup(card pickedUpCard) {
            cards.push_back(pickedUpCard);
        }

        void discard(card discardedCard) {
            for(int i = 0; i < cards.size(); i++) {
                if(cards.at(i)==discardedCard) {
                    cards.erase(i);
                }
            }
        }

        void discardAll() {
            while(!cards.empty()) {
                cards.pop_back();
            }
        }
};




#endif //COMP2006_ASSIGNMENT3_HAND_H
