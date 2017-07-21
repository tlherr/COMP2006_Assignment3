using namespace std;

#include <string>
#include "Hand.h"
#include "Common.h"

#ifndef COMP2006_ASSIGNMENT3_PLAYER_H
#define COMP2006_ASSIGNMENT3_PLAYER_H

class player {
    private:
        string name;
        int score;
        int id;
    public:
        hand cards;
        hand crib;
        card lastPlayed;

        player() {
            id = 0;
            score = 0;
            cards = hand();
            crib = hand();
        }

        void getNameInput() {
            for(;;) {
                if(cin >> name) {
                    if(common::checkForExit(name)) {
                        exit(0);
                    }

                    if(cin.fail()) {
                        cout << "Invalid name entered, please try again." << endl;
                        cin.clear();
                        cin.ignore();
                    } else {
                        break;
                    }
                } else {
                    cout << "Invalid name entered, please try again." << endl;
                    cin.clear();
                    cin.ignore();
                }
            }
        }

        int getScore() const {
            return score;
        }

        void setScore(int score) {
            player::score = score;
        }

        const string &getName() const {
            return name;
        }

        int getId() const {
            return id;
        }

        void setId(int id) {
            player::id = id;
        }

        const card &getLastPlayed() const {
            return lastPlayed;
        }

        void setLastPlayed(const card &lastPlayed) {
            player::lastPlayed = lastPlayed;
        }
};



#endif //COMP2006_ASSIGNMENT3_PLAYER_H
