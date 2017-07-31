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
        /**
         * Warning: this method returns a copy of a card, it does not remove a card from the hand when called like discard
         * @return card Card Object
         */
        card getAt(int index) {
            return cards.at(static_cast<unsigned int>(index));
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
            return (int) cards.size();
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

        /**
         * Scores the hand based on the current cards
         * @return
         */
        int count(card cutCard) {
            int rtrnPoints = 0;
            int duplicates = 0;
            //Flush. Four cards of the same suit in hand 4 (excluding the crib, and the starter)
            //Four cards in hand or crib of the same 5 suit as the starter

            int clubsFound = 0;
            int diamondsFound = 0;
            int spadesFound = 0;
            int heartsFound = 0;

            for(int i=0; i<cards.size(); i++) {
                //Take the cut card and check it with the current card for combinations of 15
                if(cards.at(i).getCountValue()+cutCard.getCountValue()==15) {
                    //Award 2 points
                    rtrnPoints+=2;
                }

                if(cards.at(i).getValue()==cutCard.getValue()) {
                    //Duplicate with cut card
                    rtrnPoints+=2;
                }

                switch(cards.at(i).getSuitValue()) {
                    case clubs:
                        clubsFound++;
                        break;
                    case diamonds:
                        diamondsFound++;
                        break;
                    case spades:
                        spadesFound++;
                        break;
                    case hearts:
                        heartsFound++;
                        break;
                }


                vector<int> diffs;
                //Check the current card against all others to look for duplicates, this will find each duplicate
                //twice so divide the number found by 2
                for(int j=cards.size()-1; j>0; j--) {
                    if(cards.at(i).getValue()==cards.at(j).getValue()) {
                        duplicates++;
                    }
                    diffs.push_back(cards.at(j).getDif(cards.at(j-1)));
                }

                //Loop through the diffs array and check for runs
                int positiveRunCounter = 0;
                int negativeRunCounter = 0;

                //Count up difs, if we get a sequence of +-1 award points
                for(int j=0; j<diffs.size(); j++) {
                    //We are only counting the first 5 diffs, anything older should already be counted
                    if(j<5) {
                        if(diffs[j]==1) {
                            positiveRunCounter++;
                        } else if(diffs[j]==-1)
                            negativeRunCounter++;
                    } else {
                        if(positiveRunCounter<3) {
                            positiveRunCounter=0;
                        }
                        if(negativeRunCounter<3) {
                            negativeRunCounter=0;
                        }
                    }
                }

                if(positiveRunCounter==3) {
                    rtrnPoints+=3;
                } else if(positiveRunCounter==4) {
                    rtrnPoints+=4;
                } else if(positiveRunCounter==5) {
                    rtrnPoints+=5;
                }

                if(negativeRunCounter==3) {
                    rtrnPoints+=3;
                } else if(negativeRunCounter==4) {
                    rtrnPoints+=4;
                } else if(negativeRunCounter==5) {
                    rtrnPoints+=5;
                }
            }

            if(heartsFound==4||diamondsFound==4||clubsFound==4||spadesFound==4) {
                rtrnPoints+=4;
            }

            rtrnPoints+=(duplicates/2);
            return rtrnPoints;
        }
};




#endif //COMP2006_ASSIGNMENT3_HAND_H
