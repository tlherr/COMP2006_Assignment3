
#ifndef COMP2006_ASSIGNMENT3_CRIBBAGE_H
#define COMP2006_ASSIGNMENT3_CRIBBAGE_H

using namespace std;

#include "Game.h"
#include "TurnManager.h"
#include "RndManager.h"
#include <algorithm>
#include <iomanip>

class cribbage : public game {
    protected:
        deck cardDeck;
        card cut;
        turnManager tManager;
        rndManager rManager;
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
            max_score_reached = 9
        };
        class crib {
            private:
                hand cards;
        };

    public:
        const int STANDARD_DECK_SIZE = 52;
        cribbage() {
            cardDeck = deck();
            tManager = turnManager();
            rManager = rndManager();
            scoreToWin = 121;
            cout << "Welcome to Cribbage in C++. Press Q at any time to quit." << endl;
        }
        /**
         * Main Game Loop
         */
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
            //Tell the turn manager how many players are playing the game
            tManager.setTotalPlayer(playerNum);
            showInitial();

            //Run the game until its status is changed to complete
            while(currentStatus!=complete) {
                //Each round is broken up into three phases
                setup();
                play();
                count();
            }
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
                case cards_played:
                    cout << "All cards held by the players have been played.  Post-game counting to commence." << endl;
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
                cout << getDealer()->getName() << " will start as the dealer" << endl;
                players.at(dealerIndex).isDealer = true;
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
        bool isDealer(player *inputPlayer) {
            if(!dealerExists) {
                return false;
            }

            return (inputPlayer->getId()==players.at(static_cast<unsigned int>(dealerIndex)).getId());
        }
        /**
         * Returns a pointer to current dealer
         * @return
         */
        player* getDealer() {
            return &players[dealerIndex];
        }
        /**
         * Return a refernce to the current player
         * @param index
         * @return player whose turn it is to play
         */
        player* getCurrentPlayer() {
            return &players.at(static_cast<unsigned int>(tManager.getCurrent()));
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
         * Return the total number of cards still in the hands of players, used durring pegging to continue until no cards
         * remain available for play
         * @return int total number of cards available to be played
         */
        int getAllPlayersCardCount() {
            int total = 0;
            for(int i=0; i<players.size(); i++) {
                total+=players.at((unsigned long) i).cards.getCount();
            }
            return total;
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
         * Print whitespace for padding
         * @param amount
         */
        string space(int amount) {
            string rtn;
            for(int i=0; i<amount; i++) {
                rtn.append(" ");
            }
            return rtn;
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
                rnd *cround = rManager.getCurrent();
                cout << "Count: " << cround->getCount() << endl;
            }

            //We know there is at least one player, render it first
            cout << space(20) << setw(15) << left << players.at(0).getName() << endl;
            cout << space(20) << setw(15) << left << "Last Played:" << players.at(0).getLastPlayed() << endl;
            cout << space(20) << setw(20) << left << players.at(0).cards.display() << endl << '\n';

            //Check if we have 2 or 4 players to format middle row
            if(playerNum==2||playerNum==3) {
                cout << space(40) << setw(15) << left << players.at(1).getName() << endl;
                cout << space(40) << setw(15) << left << "Last Played:" << players.at(1).getLastPlayed() << endl;
                cout << space(40) << setw(20) << left << players.at(1).cards.display() << endl << '\n';
            } else if(playerNum==4) {
                cout << setw(15) << left << players.at(3).getName() << space(20);
                cout << setw(15) << left << players.at(1).getName() << endl;

                cout << setw(15) << left << "Last Played:" << players.at(3).getLastPlayed() << space(20);
                cout << setw(15) << left << "Last Played:" << players.at(1).getLastPlayed() << endl;


                cout << setw(20) << left << players.at(3).cards.display() << space(20);
                cout << setw(20) << left << players.at(1).cards.display() << endl << '\n';
            }

            //if we have a third player render on the bottom row
            if(playerNum>=3) {
                cout << space(20) << setw(15) << left << players.at(2).getName() << endl;
                cout << space(20) << setw(15) << left << "Last Played:" << players.at(2).getLastPlayed() << endl;
                cout << space(20) << setw(20) << left << players.at(2).cards.display() << endl << '\n';
            }

            displayStatus();
        }
        /**
         * Assign cards from deck to players hands, note the amount delt with change with the player number
         */
        void deal() {
            for(int j=0; j<playerNum; j++) {
                vector<card> drawnCards = cardDeck.draw(cardsDealtToPlayers);
                players.at(static_cast<unsigned int>(j)).cards.pickup(drawnCards);
                players.at(static_cast<unsigned int>(j)).saveHand();
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
            tManager.setCurrent(dealerIndex);
            tManager.next();

            for(int i = 0; i<playerNum; i++) {
                for(int j=0; j<cardsDiscardedToCrib; j++) {
                    int selectedCard = selectCard("discard to Crib");
                    getDealer()->crib.pickup(getCurrentPlayer()->cards.discard(selectedCard));
                }

                render();
                tManager.next();
            }

            if(getDealer()->crib.getCount()==((playerNum*cardsDiscardedToCrib)+cardsDealtToCrib)) {
                cout << "Crib Count Verified. Expected " << getDealer()->crib.getCount() << " Got: "
                     << ((playerNum*cardsDiscardedToCrib)+cardsDealtToCrib) << endl;
            }
        }
        /**
         * Ask a specified player which card they would like to select, return the index position of the selected card
         * @param cards The Players Cards
         * @param reasonForSelection Text describing the reason for card selection (ie to crib/be played in round etc.)
         * @return int index of selected card in users hand
         */
        int selectCard(string reasonForSelection) {
            cout << getCurrentPlayer()->getName()
                 << ", what card would you like to select to " << reasonForSelection << "? (state position in hand to take)" << endl;

            int selectedCard;
            bool valid = false;

            while(!valid) {
                cin >> selectedCard;

                if(cin.good()) {
                    if(selectedCard>=1 && selectedCard<=getCurrentPlayer()->cards.getCount()) {
                        valid = true;
                    } else {
                        cout << "Invalid range, please select between 1 and " << cardsDealtToPlayers << endl;
                    }
                } else {
                    cout << "Invalid Input, please try again" << endl;
                }
            }
            //Turn back into zero indexed array
            return selectedCard-1;
        }
        /**
         * Cut the deck
         */
        void performCut() {
            cut = cardDeck.cut();

            tManager.setCurrent(dealerIndex);
            tManager.next();

            cout << getCurrentPlayer()->getName()
                 << " has cut the deck revealing the " << cut.getDisplayValue() << endl;
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
            //Stop when players are out of cards
            while(getAllPlayersCardCount()>0) {
                playRound();
            }
            currentStatus = cards_played;
            displayStatus();
        }
        /**
         * Peg until max score is reached
         */
        void playRound() {
            //Start a new round
            rManager.startNew();
            rnd *crnd = rManager.getCurrent();
            player *lastToPlayCards = nullptr;
            //Number of players who have passed, if it equals player num the round is over as everyone has passed
            int passes = 0;
            while(!crnd->isComplete()) {
                if(passes==playerNum) {
                    //Everyone has passed, end the round,
                    //@TODO: award points for being the last the play
                    crnd->end();
                    if(lastToPlayCards!= nullptr && crnd->getCount()!=31) {
                        cout << "Awarding points for last to play to: " << lastToPlayCards->getName() << endl;
                        lastToPlayCards->addScore(1);
                    }
                    showScore();
                    break;
                }

                player *current = getCurrentPlayer();
                render();
                if(crnd->canPlay(current->cards)) {
                    int cardSelected = selectCard("be played");
                    current->setLastPlayed(current->cards.getAt(cardSelected));
                    //Card can be played, play it
                    crnd->play(current, current->cards.discard(cardSelected));
                    lastToPlayCards = current;
                    tManager.next();
                } else {
                    passes++;
                    cout << "Determined player:"<< current->getName() <<" cannot play without going over limit, skipping turn" << endl;
                    tManager.next();
                }
            }
        }

        /**
         * Count points from hands and add up scores to total to check for winner
         */
        void count() {
            //Count from left of dealer around back to dealer
            tManager.setCurrent(dealerIndex);
            tManager.next();

            for(int i = 0; i<playerNum; i++) {
                //Count each players points, when we get to the dealer count hand+crib
                player *current = getCurrentPlayer();
                current->cardsToCount.count(cut);
                if(isDealer(current)) {

                }


                render();
                tManager.next();
            }



            //@TODO: MAKE SURE ALL CARDS ARE RETURNED TO DECK AFTER ROUND ENDS (CLEAR SAVED HAND)
            //Clear cut card
        }

};


#endif //COMP2006_ASSIGNMENT3_CRIBBAGE_H
