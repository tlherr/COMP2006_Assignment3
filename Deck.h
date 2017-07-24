//
// Created by Thomas Herr on 2017-07-06.
//

#ifndef COMP2006_ASSIGNMENT3_DECK_H
#define COMP2006_ASSIGNMENT3_DECK_H

#include "Cards.h"
#include "Common.h"
#include <random>
#include <vector>

class deck {

    private:
        /**
         * Create an array to hold the 52 cards of a standard North American playing deck
         */
        vector<card> cards;

    public:
        deck() {
            int position_counter = 0;

            //Populate deck with cards
            for(int suit_counter = 1; suit_counter <=4; suit_counter++) {
                for(int card_counter = 2; card_counter<=ACE; card_counter++, position_counter++) {
                    card tmpCard  = card(card_counter, suit_counter);
                    cards.push_back(tmpCard);
                }
            }
        }

        string display() {
            string output = "{";
            for(int i = 0; i < cards.size()-1; i++) {
                output.append(cards.at((unsigned long) i).getDisplayValue());
                if(i!=cards.size()-1) {
                    output.append(",");
                }
            }
            output.append("}");
            return output;
        }
        /**
         * By default perform one 'pass' per card in the deck
         */
        void shuffle() {
            shuffle((int) cards.size()-1);
        }

        /**
         * Using the system time randomly seed the deck. You can do this by randomly selecting a card in the deck and
         * swapping it with a temp class.  Repeat this at least 52 times to “shuffle” each card
         * Display every card in the shuffled deck similar to the above ordered representation.
         * We will look to ensure no duplicates and that it is random.
         * Keep in mind the modulus operator can be used to help with this function and that you will need new include
         * files for randomisation (see slides)
         * Keep in mind that for both i and ii no cards should ever be duplicated in the running deck
         */
        void shuffle(int passes) {

            random_device rd;
            mt19937 seed(rd());
            uniform_int_distribution<> distr(0, (int) cards.size()-1);

            for(int i = 0; i <= passes; i++) {
                //Randomly select cards to swap
                int to = distr(seed);
                int from = distr(seed);

                swap(cards[to], cards[from]);
            }

        }
        /**
         * Get current number of cards in the deck
         * @return
         */
        int getSize() {
            return (int) cards.size();
        }

        /**
         * Check to see if we have the expected number of cards in the deck
         */
        bool validate(int expectedCards) {
            return cards.size()==expectedCards;
        }
        /**
         * Cut the deck and return a random card
         * @return
         */
        card cut() {
            shuffle();
            int selection = common::random(0, cards.size()-1);
            return getAt(selection);
        }
        /**
         * Remove a card from the specified index position
         * @param index
         * @return
         */
        card getAt(int index) {
            card drawnCard = cards.at(static_cast<unsigned int>(index));
            cards.erase(cards.begin()+index);
            return drawnCard;
        }
        /**
         * Returns the next card from the top of the deck and "removes it"
         * @return
         */
        card getNext() {
            return getAt(cards.size()-1);
        }
        /**
         * Return an array of cards from the deck
         * @param numCards
         * @return
         */
        vector<card> draw(int numCards) {
            if(numCards>cards.size()-1) {
                numCards=cards.size()-1;
            }

            vector<card> cardsDrawn(cards.begin(), cards.begin()+numCards);
            cards.erase(cards.begin(), cards.begin()+numCards);
            return cardsDrawn;
        }

        /**
         * Return cards back into the deck, adding to the "bottom" so if cards are drawn it is still randomized
         * @param crd
         */
        void returnTo(card crd) {
            cards.insert(cards.begin(), crd);
        }
        /**
         * Return a vector of cards back into the deck, adding to the "bottom" so if cards are drawn it is still randomized
         * @param crds
         */
        void returnTo(vector<card> crds) {
            cards.insert(cards.end(), crds.begin(), crds.end());
        }

};



#endif //COMP2006_ASSIGNMENT3_DECK_H
