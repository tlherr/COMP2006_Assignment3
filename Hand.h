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
        void pickup(vector<card> pickedUpCards) {
            cards.insert(cards.end(), pickedUpCards.begin(), pickedUpCards.end());
        }

        void pickup(card pickedUpCard) {
            cards.push_back(pickedUpCard);
        }

        card discard(int index) {
            card returningToDeck;
            returningToDeck = cards.at(static_cast<unsigned int>(index));
            cards.erase(cards.begin()+index);
            return returningToDeck;
        }

        card discard(card discardedCard) {
            card returningToDeck;
            for(int i = 0; i < cards.size(); i++) {
                if(cards.at((unsigned int) i).compare(discardedCard)) {
                    returningToDeck = cards.at((unsigned int) i);
                    cards.erase(cards.begin()+i);
                }
            }

            return returningToDeck;
        }

        int getCount() {
            return cards.size();
        }

        vector<card> discardAll() {
            vector<card> returningToDeck = cards;
            cards.erase(cards.begin(), cards.end());
            return returningToDeck;
        }
        /**
         * Return back rendered cards
         */
        string display() {
            if(cards.empty()) {
                return "Empty";
            }

            string displayString = "[";
            for (auto &card : cards) {
                displayString.append(card.getDisplayValue());
            }
            displayString.append("]");

            return displayString;
        }
};




#endif //COMP2006_ASSIGNMENT3_HAND_H
