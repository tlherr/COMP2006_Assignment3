/**
 * Contains Deliverables for Card Game Requirements
 */

using namespace std;

#ifndef COMP2006_ASSIGNMENT3_CARDS_H
#define COMP2006_ASSIGNMENT3_CARDS_H

#include <iostream>
#include <stdio.h>

/*
 * Create the four suits (clubs, diamonds, hearts, and spades) as an enumerator
 */

enum suits {
    clubs = 1, diamonds, hearts, spades
};

suits getSuit(int suitNum) {
    switch(suitNum) {
        default:
            return clubs;
        case clubs:
            return clubs;
        case diamonds:
            return diamonds;
        case hearts:
            return hearts;
        case spades:
            return spades;
    }

}


/**
 * Create constants to represent the jack, queen, king, ace and assign them to 11-14 respectively
 */

const int JACK = 11;
const int QUEEN = 12;
const int KING = 13;
const int ACE = 14;

const string CLUB_UNICODE = "\u2663";
const string DIAMOND_UNICODE = "\u2666";
const string HEART_UNICODE = "\u2665";
const string SPADE_UNICODE = "\u2660";

/**
 *  Has member data of the card number and the suit
 *  Has member functions consisting of a constructor (empty for the time being), setting a card value with a suit and value, and display function
 */

class card {
    private:
    int value;
        suits suit;

    public:
        card(){}
        card(int value, suits suit) : value(value), suit(suit) {}
        card(int cardValue, int suitNum) {
            suit = getSuit(suitNum);
            value = cardValue;
        }

        void display() {
            cout << getDisplayValue() << endl;
        }

        /**
         * Display Function:
         * Display the suit of the card using the unicode text values.  This will vary from system to system but as an
         * example will include ♠, ♥, ♦, ♣. If your compiler allows for this you can copy and paste this into your code.
         * Display the numerical value of the card from 2 to 10 or J, Q, K, or A for jack, queen, kind, and ace
         * respectively (aligning with the enumerators)
         */
        string getDisplayValue() {
            string output;
            string card_value;

            if(value>=JACK && value<=ACE) {
                switch(value) {
                    case JACK:
                        card_value = 'J';
                        break;
                    case QUEEN:
                        card_value = 'Q';
                        break;
                    case KING:
                        card_value = 'K';
                        break;
                    case ACE:
                        card_value = 'A';
                        break;
                }
            } else {
                card_value = to_string(value);
            }


            string suit_value;

            switch(suit) {
                case spades:
                    suit_value = SPADE_UNICODE;
                    break;
                case hearts:
                    suit_value = HEART_UNICODE;
                    break;
                case diamonds:
                    suit_value = DIAMOND_UNICODE;
                    break;
                case clubs:
                    suit_value = CLUB_UNICODE;
                    break;
            }

            output.append(card_value).append(suit_value);
            return output;
        }

    /**
     * Compare a card to see if it matches
     * @param comparison card to be compared
     * @return bool Result of comparison (True if equal)
     */
    bool compare(card comparison) {
        return (this->value==comparison.value && this->suit==comparison.suit);
    }
    /**
     * Compare the suit of a card to a given card, return true if they match
     * @param comparison
     * @return
     */
    bool compareSuit(card comparison) {
        return (this->suit==comparison.suit);
    }
    /**
     * Compare the value of a card to a given card, return true if they match
     * @param comparison
     * @return
     */
    bool compareValue(card comparison) {
       cout << "Comparing value: " << this->value << " to " << comparison.value << endl;
       return (this->value==comparison.value);
    }
    /**
     * Return the difference in card value
     * @param comparison
     * @return int
     */
    int getDif(card comparison) {
        return this->value-comparison.value;
    }

    /**
     * Return the numeric value of a card
     * @return
     */
    int getValue() const {
        return value;
    }

    suits getSuitValue() const {
        return suit;
    }

    /**
     * Get the value of the card as used in counting
     * @return
     */
    int getCountValue() {
        switch(this->value) {
            default:
                return this->value;
            case JACK:
                return 10;
            case QUEEN:
                return 10;
            case KING:
                return 10;
            case ACE:
                return 1;
        }
    }
};





#endif //COMP2006_ASSIGNMENT3_CARDS_H