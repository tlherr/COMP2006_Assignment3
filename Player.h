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
        hand cardsToCount;
        hand crib;
        card lastPlayed;
        bool isDealer;

        player() {
            id = 0;
            name = "";
            score = 0;
            cards = hand();
            cardsToCount = hand();
            crib = hand();
            lastPlayed = card(-1, hearts);
            isDealer = false;
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

        void addScore(int toAdd) {
            cout << name << " has got " << toAdd << " points" << endl;
            player::score+=toAdd;
        }
        /**
         * Saves a copy of the players hand to be used for counting, should be cleared after counting or else duplicate
         * cards will be returned to the deck
         */
        void saveHand() {
            cardsToCount = cards;
        }


        string getName() const {
            if(isDealer) {
                name + "(D)";
            }

            return name;
        }

        int getId() const {
            return id;
        }

        void setId(int id) {
            player::id = id;
        }

        string getLastPlayed() {
            if(lastPlayed.getValue()==-1) {
                //Uninitialized, return a dash as no cards have been played
                return "-";
            } else {
                return lastPlayed.getDisplayValue();
            }
        }

        void setLastPlayed(const card &lastPlayed) {
            player::lastPlayed = lastPlayed;
        }
};



#endif //COMP2006_ASSIGNMENT3_PLAYER_H
