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

        void display() {
            printf("Displaying Deck \n");
            for(int i = 0; i < (int) cards.size(); i++) {
                cards.at((unsigned long) i).display();
            }
        }
        /**
         * By default perform one 'pass' per card in the deck
         */
        void shuffle() {
            shuffle((int) cards.size());
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
         * Cut the deck and return a random card
         * @return
         */
        card cut() {
            int selection = common::random(0, cards.size());
            cout << "Cutting deck, using card at position:" << selection << " with value: ";
            cards.at(selection).display();
            shuffle();
            return cards.at(selection);
        }

        void deal(int cardNum) {

        }



};



#endif //COMP2006_ASSIGNMENT3_DECK_H
