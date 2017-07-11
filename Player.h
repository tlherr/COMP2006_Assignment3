using namespace std;

#include <string>
#include "Hand.h"

#ifndef COMP2006_ASSIGNMENT3_PLAYER_H
#define COMP2006_ASSIGNMENT3_PLAYER_H

class player {
    private:
        string name;
        int score;
    public:
        COMP2006_ASSIGNMENT3_HAND_H::hand cards;
        player(const string &name) : name(name) {}

    int getScore() const {
        return score;
    }

    void setScore(int score) {
        player::score = score;
    }
};



#endif //COMP2006_ASSIGNMENT3_PLAYER_H
