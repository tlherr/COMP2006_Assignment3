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
        int scoreToWin;
        enum gameStatus {
            initializing = 1,
            settingup = 2,
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
                cout << "How many players are there (2, 3, or 4)?" << endl;
                cin >> playerNum;
                if(!cin.fail()) {
                    if(playerNum<2||playerNum>4) {
                        cout << "Please enter a number between 2 and 4." << endl;
                        cin.clear();
                        cin.ignore();
                    } else {
                        break;
                    }
                } else {
                    if(common::checkForExit(to_string(playerNum))) {
                        exit(0);
                    } else {
                        cout << "Invalid Integer Entered. Please try again" << endl;
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
                cout << "Please enter Player" << i+1 <<"'s name: ";
                player tmpPlayer = player();
                tmpPlayer.setId(tmpId);
                tmpPlayer.getNameInput();
                addPlayer(tmpPlayer);
                tmpId+=rand()+1;
            }
        }
        /**
         *
         * @return
         */
        const vector<player> &getPlayers() const {
            return players;
        }
        /**
         * Add a player to the game
         * @param toAdd
         */
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
         * Any extension of the game class must have a setup method
         */
        virtual void setup() = 0;
        /**
         * Any extension of the game class must have a play method
         */
        virtual void play() = 0;
        /**
         * Any extension of the game class must have a run method
         */
        virtual void run() = 0;
        /**
         * Any extension of the game class must have a render method
         */
        virtual void render() = 0;
};


#endif //COMP2006_ASSIGNMENT3_GAME_H
