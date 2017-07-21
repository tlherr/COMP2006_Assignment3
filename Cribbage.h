
#ifndef COMP2006_ASSIGNMENT3_CRIBBAGE_H
#define COMP2006_ASSIGNMENT3_CRIBBAGE_H

using namespace std;

#include "Game.h"
#include <algorithm>
#include <iomanip>

class cribbage : public game {
    protected:
        deck cardDeck;
        card cut;
        int dealerIndex;
        bool dealerExists = false;

        int cardsDealtToPlayers;
        int cardsDealtToCrib;
        int cardsDiscardedToCrib;

        enum matchStatus {
            ready = 1,
            dealer_selected = 2,
            creating_crib = 3,
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
        const int ROUND_MAX_COUNT = 31;
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
        /**
         * Output human readable status messages to inform the player of the game state
         */
        void displayStatus() {
            common::setColour(common::COLOUR_YELLOW);

            cout << "Status: ";
            switch(currentStatus) {
                case ready:
                    cout << "The match is ready to start" << endl;
                    break;
                case dealer_selected:
                    cout << "The dealer will now shuffle the deck and start the match" << endl;
                    break;
                case creating_crib:
                    cout << "Creating the crib for the round" << endl;
                    break;
                case pegging_begin:
                    cout << "The round pegging can now commence" << endl;
                    break;
                default:
                    cout << "Unknown" << endl;
                    break;
            }

            common::setColour(common::COLOUR_WHITE);
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
                            common::setColour(common::COLOUR_RED);
                            cout << "Players cut cards of equal value, recutting " << endl;
                            common::setColour(common::COLOUR_WHITE);
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
         * Returns a pointer to current dealer
         * @return
         */
        player* getDealer() {
            return &players[dealerIndex];
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
            //Depending on status show Deck, Cut, Crib and Count
            cout << "Deck (" << cardDeck.getSize() << ") :" << cardDeck.display() << endl;
            if(currentStatus>=pegging_begin) {
                cout << "Cut: " << cut.getDisplayValue() << endl;
            }

            if(currentStatus>=creating_crib && dealerExists) {
                cout << "Crib: " << getDealer()->crib.display() << endl;
            }

            if(currentStatus>=pegging_begin) {
                cout << "Count: " << endl;
            }

            //We know there is at least one player, render it first
            cout << '\t' << setw(20) << left << displayName(players.at(0)) << endl;
            cout << '\t' << setw(20) << left << players.at(0).cards.display() << endl << '\n';

            //Check if we have 2 or 4 players to format middle row
            if(playerNum==2) {
                cout << '\t' << setw(15) << right << displayName(players.at(1)) << endl;
                cout << '\t' << setw(25) << right << players.at(1).cards.display() << endl << '\n';
            } else if(playerNum==4) {
                cout << setw(15) << left << displayName(players.at(3));
                cout << setw(15) << right << displayName(players.at(1)) << endl;

                cout << setw(20) << left << players.at(3).cards.display() << '\t';
                cout << setw(20) << right << players.at(1).cards.display() << endl << '\n';
            }

            //if we have a third player render on the bottom row
            if(playerNum>=3) {
                cout << '\t' << setw(20) << left << displayName(players.at(2)) << endl;
                cout << '\t' << setw(20) << left << players.at(2).cards.display() << endl << '\n';
            }

            displayStatus();
        }
        /**
         * If the player is the dealer append the symbol to their name
         * @param plyr
         * @return string modified string
         */
        string displayName(const player &plyr) {
            string output;
            output.append(plyr.getName());

            if(isDealer(plyr)) {
                output.append(" (D)");
            }
            return output;
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
         * Ask users for input to discard a card into crib
         */
        void buildCrib() {
            currentStatus = creating_crib;
            //Check if we need to deal any cards into crib (based on playerNum)
            if(cardsDealtToCrib==1) {
                getDealer()->crib.pickup(cardDeck.getNext());
            }

            //Start with the player to the left (ascending index)
            int currentPlayer = dealerIndex+1;
            for(int i = 0; i<playerNum; i++) {

                if(currentPlayer>=playerNum) {
                    currentPlayer=0;
                }

                for(int j=0; j<cardsDiscardedToCrib; j++) {
                    int cardToCribIndex;
                    bool valid = false;
                    cout << players.at(static_cast<unsigned int>(currentPlayer)).getName() << ", what card would you like to discard to the Crib? (state position in hand to take)" << endl;
                    //Ask the player which card they would like to discard into crib

                    while(!valid) {
                        cin >> cardToCribIndex;

                        if(cin.good()) {
                            if(cardToCribIndex>=1 && cardToCribIndex<= cardsDealtToPlayers) {
                                valid = true;
                                //Remove the card from the hand and add to crib
                                getDealer()->crib.pickup(players.at(
                                        static_cast<unsigned int>(currentPlayer)).cards.discard(cardToCribIndex - 1));
                            } else {
                                cout << "Invalid range, please select between 1 and " << cardsDealtToPlayers << endl;
                            }
                        } else {
                            cout << "Invalid Input, please try again" << endl;
                        }
                    }
                }

                render();
                currentPlayer++;
            }

            if(getDealer()->crib.getCount()==((playerNum*cardsDiscardedToCrib)+cardsDealtToCrib)) {
                cout << "Crib Count Verified. Expected " << getDealer()->crib.getCount() << " Got: " << ((playerNum*cardsDiscardedToCrib)+cardsDealtToCrib) << endl;
            }
        }
        /**
         * Cut the deck
         */
        void performCut() {
            cut = cardDeck.cut();

            int playerToCut;
            //Get the person to the left of the dealer
            if(dealerIndex+1>=playerNum) {
                playerToCut=0;
            } else {
                playerToCut=dealerIndex+1;
            }

            cout << players.at(static_cast<unsigned int>(playerToCut)).getName() << " has cut the deck revealing the " << cut.getDisplayValue() << endl;
            currentStatus = pegging_begin;
            displayStatus();
        }
        /**
         * Run pre game processes, select a dealer, shuffle the deck, deal the cards, form a crib for dealer
         */
        void setup() override {
            selectDealer();
            cardDeck.shuffle();
            showScore();
            deal();
            buildCrib();
            performCut();
        }
        /**
         * Process of pegging
         */
        void play() override {

            //Determine how many cards are in players hands to be played

            //Loop Rounds until players have no cards left


        }
        /**
         * Peg until max score is reached
         */
        void playRound() {
            int roundCount;

            //Start on the dealers left for the first round, then just keep rotating clockwise

        }

        /**
         * Count points from hands and add up scores to total to check for winner
         */
        void count() {
            //Total scores

            //@TODO: MAKE SURE ALL CARDS ARE RETURNED TO DECK AFTER ROUND ENDS
        }

};


#endif //COMP2006_ASSIGNMENT3_CRIBBAGE_H
