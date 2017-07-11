#ifndef COMP2006_ASSIGNMENT3_GAME_H
#define COMP2006_ASSIGNMENT3_GAME_H

using namespace std;

#include "Player.h"

class game {
    private:
        int playerNum;
        vector<player> players;
        int scoreToWin;

public:
    /**
     * Get the number of players and their respective names
     */
    void getSetupInfo() {
        for(;;) {
            printf("How many players are there (2, 3, or 4)? \n");

            if(cin >> playerNum) {
                if(playerNum<2|playerNum>4) {
                    printf("Please enter a number between 2 and 4. \n");
                    cin.clear();
                    cin.ignore();
                } else {
                    break;
                }
            } else {
                printf("Invalid Integer Entered. Please try again \n");
                cin.clear();
                cin.ignore();
            }
        }
        /**
         * Get all the names
         */
        for(int i=1; i<=playerNum; i++) {
            printf("Please enter Player %d's name: ", i);
            player tmpPlayer = player();
            tmpPlayer.getNameInput();
            addPlayer(tmpPlayer);
        }
    }

    const vector<player> &getPlayers() const {
        return players;
    }

    void addPlayer(player toAdd) {
        players.push_back(toAdd);
    }

};


#endif //COMP2006_ASSIGNMENT3_GAME_H
