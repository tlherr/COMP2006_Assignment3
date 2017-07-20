
#ifndef COMP2006_ASSIGNMENT3_CRIBBAGE_H
#define COMP2006_ASSIGNMENT3_CRIBBAGE_H

using namespace std;

#include "Game.h"
#include <algorithm>
#include <iomanip>

class cribbage : public game {
    protected:
        deck cardDeck;
        player dealer;
        bool dealerExists = false;
        int cardsDealtToPlayers;
        int cardsDealtToCrib;
        int cardsDiscardedToCrib;
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
        class crib {
            private:
                COMP2006_ASSIGNMENT3_HAND_H::hand cards;
        };

    public:
        cribbage() {
            cardDeck = deck();
            scoreToWin = 121;
            printf("Welcome to Cribbage in C++. Press Q at any time to quit. \n");
        }

        void run() override {
            //Setup the players
            getSetupInfo();

            //Set the params needed to run the game based on the number of players
            switch(playerNum) {
                case 2:
                    cardsDealtToPlayers = 6;
                    cardsDealtToCrib = 0;
                    cardsDiscardedToCrib = 2;
                    break;
                case 3:
                    cardsDealtToPlayers = 5;
                    cardsDealtToCrib = 1;
                    cardsDiscardedToCrib = 1;
                    break;
                case 4:
                    cardsDealtToPlayers = 5;
                    cardsDealtToCrib = 0;
                    cardsDiscardedToCrib = 1;
                    break;
            }

            //Run the game until its status is changed to complete
            //while(currentStatus!=complete) {
                //Each round is broken up into three phases
                setup();
                play();
                count();
            //}
        }

        /**
         * Decide dealer (based on rotation or cutting deck if no dealer exists)
         * Each user is to cut the deck (pull a random card, without replacement) after which the user that pulls
         * the lowest card is designated the dealer.  If there is a tie for the lowest shuffle and repeat the cutting
         * process.
         */
        void selectDealer() {
            if(!dealerExists) {
                //Cut the deck once for each player
                int cutCards [playerNum];
                int lowestPlayer = -1;
                int lowestCard = 0;

                for(int i=0; i<playerNum; i++) {
                    card cutCard = cardDeck.cut();
                    cutCards[i] = cutCard.getValue();

                    if(lowestPlayer==-1) {
                        lowestPlayer = i;
                        lowestCard = cutCard.getValue();
                    } else {
                        //Check if the current card is lower then the lowest
                        if(cutCard.getValue()<lowestCard) {
                            lowestCard = cutCard.getValue();
                            lowestPlayer = i;
                        } else if(cutCard.getValue()==lowestCard) {
                            //Two players have cut a card of the same value, restart this process
                            cout << "Players cut cards of equal value, recutting " << endl;
                            selectDealer();
                        }
                    }
                }

                dealer = getPlayers().at((unsigned int) lowestPlayer);
                cout << dealer.getName() << " selected as the dealer " << endl;
                dealerExists = true;
            } else {
                nextDealer();
            }
        }

        bool isDealer(const player &inputPlayer) {
            for(int i=0; i<playerNum; i++) {
                if(dealer.getId()==inputPlayer.getId()) {
                    return true;
                }
            };

            return false;
        }

        /**
         * Set the next player as the dealer. This will rotate the dealer in a clockwise direction
         */
        void nextDealer() {
            //Get the "index" of the current dealer
            int currentDealerIndex = 0;
            for(int i=0; i<playerNum; i++) {
                if(isDealer(players.at(static_cast<unsigned int>(i)))) {
                    currentDealerIndex=i;
                }
            }

            if((currentDealerIndex+1)==playerNum) {
                currentDealerIndex = 0;
                dealer = players.at((unsigned int) (currentDealerIndex));
            } else {
                dealer = players.at((unsigned int) (currentDealerIndex + 1));
            }

            cout << "New dealer is: " << dealer.getName() << endl;
        }

        /**
         * Draw the game board and show player cards
         */
        void render() override {
            bool skipLast = false;
            for(int i=0; i<playerNum; i++) {
                if(skipLast) {
                    break;
                }

                string displayName;
                displayName = players.at(static_cast<unsigned int>(i)).getName();
                if(isDealer(players.at(static_cast<unsigned int>(i)))) {
                    displayName.append(" (D)");
                }

                if(i==1) {
                    //Check if there is a fourth player, if so render that on the left side
                    if(playerNum==4) {
                        skipLast = true;

                        cout << displayName;

                        displayName = players.at(3).getName();
                        if(isDealer(players.at(3))) {
                            displayName+" (D)";
                        }

                        cout << setw(30) << displayName << endl;

                        cout << setw(15) << players.at(static_cast<unsigned int>(i)).cards.display() << endl;
                        cout << setw(15) << players.at(3).cards.display() << endl;
                    } else {
                        cout << setw(30) << displayName << endl;
                        cout << setw(30) << players.at(static_cast<unsigned int>(i)).cards.display() << endl;
                    }
                } else {
                    cout << setw(15) << displayName << endl;
                    cout << setw(15) << players.at(static_cast<unsigned int>(i)).cards.display() << endl;
                }

            }
        }

        void deal() {

        }

        void setup() {
            selectDealer();
            cardDeck.shuffle();
            //Deal
            //Form Crib
        }

        void play() {
            render();
            //Cut
            //Play round
        }

        void count() {
            //Total scores
        }

};


#endif //COMP2006_ASSIGNMENT3_CRIBBAGE_H
