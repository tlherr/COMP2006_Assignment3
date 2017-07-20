#ifndef COMP2006_ASSIGNMENT3_GAME_H
#define COMP2006_ASSIGNMENT3_GAME_H

using namespace std;

#include <iomanip>
#include "Player.h"
#include "Common.h"

/**
 * Abstract gane class
 */
class game {

    protected:
        int currentStatus;
        int playerNum;
        vector<player> players;
        int turn = 1;
        int scoreToWin;
        enum gameStatus {
            initializing = 1,
            setup = 2,
            running = 3,
            complete = 4
        };

    public:

        /**
         * Get the number of players and their respective names
         */
        void getSetupInfo() {
            currentStatus = initializing;
            for(;;) {
                printf("How many players are there (2, 3, or 4)? \n");

                cin >> playerNum;
                if(!cin.fail()) {
                    if(playerNum<2|playerNum>4) {
                        printf("Please enter a number between 2 and 4. \n");
                        cin.clear();
                        cin.ignore();
                    } else {
                        break;
                    }
                } else {
                    if(common::checkForExit(to_string(playerNum))) {
                        exit(0);
                    } else {
                        printf("Invalid Integer Entered. Please try again \n");
                        cin.clear();
                        cin.ignore();
                    }
                }
            }
            int tmpId = 0;
            /**
             * Get all the names
             */
            for(int i=0; i<playerNum; i++) {
                printf("Please enter Player %d's name: ", i+1);
                player tmpPlayer = player();
                tmpPlayer.setId(tmpId);
                tmpPlayer.getNameInput();
                addPlayer(tmpPlayer);
                tmpId+=rand();
            }
        }

        const vector<player> &getPlayers() const {
            return players;
        }

        void addPlayer(player toAdd) {
            players.push_back(toAdd);
        }
        /**
         * Iterate through players and display scores
         */
        void showScore() {
            cout << "Score:" << endl;
            for(auto const& player: players) {
                cout << setw(15) << left << player.getName() << ":" << right << player.getScore() << endl;
            }
        }

        /**
         * Return the player whos turn is next
         */
        player nextTurn() {
            player currentTurn = players.at((unsigned int) turn);
            if(turn==players.size()) {
                turn = 1;
            } else {
                turn++;
            }

            return currentTurn;
        }

        virtual void run() = 0;
        virtual void render() = 0;
};


#endif //COMP2006_ASSIGNMENT3_GAME_H
