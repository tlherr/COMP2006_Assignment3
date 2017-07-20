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
        COMP2006_ASSIGNMENT3_HAND_H::hand cards;

    player() {
        score=0;
    }

    void getNameInput() {
        for(;;) {
            if(cin >> name) {
                if(common::checkForExit(name)) {
                    exit(0);
                }

                if(cin.fail()) {
                    printf("Invalid name entered, please try again. \n");
                    cin.clear();
                    cin.ignore();
                } else {
                    break;
                }
            } else {
                printf("Invalid name entered, please try again. \n");
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
};



#endif //COMP2006_ASSIGNMENT3_PLAYER_H
