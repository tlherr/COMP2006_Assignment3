#ifndef COMP2006_ASSIGNMENT3_GAME_H
#define COMP2006_ASSIGNMENT3_GAME_H

#include "Player.h"

class game {
    private:
        vector<player> players;
        int scoreToWin;

public:
    const vector<player> &getPlayers() const {
        return players;
    }

    void addPlayer(player toAdd) {
        players.push_back(toAdd);
    }

};


#endif //COMP2006_ASSIGNMENT3_GAME_H
