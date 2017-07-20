
#ifndef COMP2006_ASSIGNMENT3_CRIBBAGE_H
#define COMP2006_ASSIGNMENT3_CRIBBAGE_H

using namespace std;

#include "Game.h"
#include <algorithm>
#include <iomanip>

class cribbage : public game {
    protected:
        deck cardDeck;
        int dealerIndex;
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
        const int STANDARD_DECK_SIZE = 52;
        cribbage() {
            cardDeck = deck();
            scoreToWin = 121;
            cout << "Welcome to Cribbage in C++. Press Q at any time to quit." << endl;
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

            showInitial();

            //Run the game until its status is changed to complete
            //while(currentStatus!=complete) {
                //Each round is broken up into three phases
                setup();
                play();
                count();
            //}
        }
        /**
         * Display a message and show players sitting in their assigned order
         */
        void showInitial() {
            cout << "Players please take your seats." << endl;
            render();
            displayStatus();
        }

        void displayStatus() {
            cout << "Status: ";
            switch(currentStatus) {
                case ready:
                    cout << "The match is ready to start" << endl;
                    break;
                case dealer_selected:
                    cout << "The dealer will now shuffle the deck and start the match" << endl;
                    break;
                default:
                    cout << "Unknown" << endl;
                    break;
            }
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
                    players.at(static_cast<unsigned int>(i)).cards.pickup(cutCard);
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

                dealerIndex = lowestPlayer;
                dealerExists = true;
                currentStatus = dealer_selected;
                cout << "The deck has been cut with the following results." << endl;
                cout << getPlayers().at((unsigned int) lowestPlayer).getName() << " will start as the dealer" << endl;
                render();
                clearHands();
                displayStatus();
            } else {
                nextDealer();
            }
        }
        /**
         * Check if the given player is currently the dealer
         * @param inputPlayer Player to check
         * @return boolean result if player is dealer
         */
        bool isDealer(const player &inputPlayer) {
            if(!dealerExists) {
                return false;
            }

            return (inputPlayer.getId()==players.at(static_cast<unsigned int>(dealerIndex)).getId());
        }
        /**
         * Set the next player as the dealer. This will rotate the dealer in a "clockwise" (ascending) direction
         */
        void nextDealer() {
            //Is the "next" player in ascending order the last player
            if((dealerIndex+1)==playerNum) {
                //If so reset the index
                dealerIndex = 0;
            } else {
                //If not dealer is the next player
                dealerIndex++;
            }

            cout << "New dealer is: " << getPlayers().at((unsigned int) dealerIndex).getName() << endl;
        }
        /**
         * Removes cards from players hands
         */
        void clearHands() {
            for(int i=0; i<playerNum; i++) {
                cardDeck.returnTo(players.at(static_cast<unsigned int>(i)).cards.discardAll());
            }

            if(cardDeck.validate(STANDARD_DECK_SIZE)) {
                cout << "Cards returned successfully" << endl;
            } else {
                cout << "Error after returning cards, deck size invalid" << endl;
            }
        }
        /**
         * Display a visual indication of player turn order, dealer status and cards in hand
         */
        void render() override {
            for(int i=0; i<playerNum; i++) {
                string displayName;
                displayName = players.at(static_cast<unsigned int>(i)).getName();
                if(isDealer(players.at(static_cast<unsigned int>(i)))) {
                    displayName.append(" (D)");
                }

                //Render Top and Bottom
                if(i==0||i==3) {
                    cout << '\t' << setw(20) << left << displayName << endl;
                    cout << '\t' << setw(20) << left << players.at(static_cast<unsigned int>(i)).cards.display() << endl << '\n';
                } else {
                    //Middle Row, check number of players
                    if(playerNum==4) {
                        cout << setw(15) << left << displayName;

                        displayName = players.at(2).getName();
                        if(isDealer(players.at(2))) {
                            displayName.append(" (D)");
                        }

                        cout << setw(25) << right << displayName << endl;
                        cout << setw(20) << left << players.at(static_cast<unsigned int>(i)).cards.display() << '\t';
                        cout << setw(20) << right << players.at(2).cards.display() << endl << '\n';

                        i++;
                    } else {
                        //No fourth player, third player goes in right position
                        cout << setw(20) << right << displayName << endl;
                        cout << setw(20) << right << players.at(static_cast<unsigned int>(i)).cards.display() << endl << '\n';
                    }

                }


            }
        }
        /**
         * Assign cards from deck to players hands, note the amount delt with change with the player number
         */
        void deal() {
            for(int j=0; j<playerNum; j++) {
                vector<card> drawnCards = cardDeck.draw(cardsDealtToPlayers);
                players.at(static_cast<unsigned int>(j)).cards.pickup(drawnCards);
            }

            render();
        }
        /**
         * Run pre game processes, select a dealer, shuffle the deck, deal the cards, form a crib for dealer
         */
        void setup() override {
            selectDealer();
            cardDeck.shuffle();
            showScore();
            deal();
            //Form Crib

        }
        /**
         * Process of pegging
         */
        void play() override {
            //Clear the terminal window


        }
        /**
         * Count points from hands and add up scores to total to check for winner
         */
        void count() {
            //Total scores
        }

};


#endif //COMP2006_ASSIGNMENT3_CRIBBAGE_H
