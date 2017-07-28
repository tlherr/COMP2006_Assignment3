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
    /**
     * Constructor
     */
    rnd() {
        count = 0;
        cardsPlayed = hand();
        complete = false;
    }

    /**
     * Return a count of how many cards have been played in this round
     * @return int count number of cards played in the round
     */
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
     * End round
     */
    void end() {
        complete = true;
        cout << "Round has ended" << endl;
    }

    /**
     * Checks the score to determine if a user can play a card
     * @return boolean true if user can play specified card without going over limit, false if cannot
     */
    bool canPlay(hand toCheck) {
        bool canPlay = true;
        //Check based on the given cards if a player can play one of them without going over the limit
        for (int i = 0; i < toCheck.getCount(); i++) {
            if ((toCheck.getAt(i).getValue() + count) > ROUND_MAX_COUNT) {
                canPlay = false;
            }
        }

        return canPlay;
    }

    /**
     * Play a card, will automatically assign points if points necessary
     * @param cardPlayer
     * @param cardPlayed
     * @return
     */
    void play(player *cardPlayer, card cardPlayed) {
        cardsPlayed.pickup(cardPlayed);
        count += cardPlayed.getValue();
        int pointsEarned = checkScore();
        cardPlayer->addScore(pointsEarned);
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
        int rtrnScore = 0;

        //If 1 or fewer cards have been played there are no possible points to be scored
        if (cardsPlayed.getCount() <= 1) {
            return rtrnScore;
        }

        //Check for a count of 15
        if (count == 15) {
            rtrnScore += 2;
        }

        //Based on current card and working backwards start checking for "pairs"
        if (cardsPlayed.getCount() >= 2) {
            //At least two cards have been played, check them for matches
            int mostRecentCardIndex = cardsPlayed.getCount() - 1;

            //Check for repeat values indicating pairs etc
            if (cardsPlayed.getAt(mostRecentCardIndex).compareValue(cardsPlayed.getAt(mostRecentCardIndex - 1))) {
                //Last two cards have a matching value, check for a triplet before awarding points
                if (cardsPlayed.getCount() >= 3) {
                    if (cardsPlayed.getAt(mostRecentCardIndex - 1).compareValue(
                            cardsPlayed.getAt(mostRecentCardIndex - 2))) {
                        //Last three cards played have a matching value, check for four before awarding points
                        if (cardsPlayed.getCount() >= 4) {
                            if (cardsPlayed.getAt(mostRecentCardIndex - 2).compareValue(
                                    cardsPlayed.getAt(mostRecentCardIndex - 3))) {
                                //Last four cards played have a matching value, this is max points possible for same value
                                cout << "Double Pair Detected" << endl;
                                rtrnScore += 12;
                            } else {
                                cout << "Tripplet Detected" << endl;
                                rtrnScore += 6;
                            }
                        }
                    } else {
                        cout << "Double Detected" << endl;
                        rtrnScore += 2;
                    }
                }

            }

            //Check for sequences
        }

        return rtrnScore;
    }


};
#endif //COMP2006_ASSIGNMENT3_ROUND_H
