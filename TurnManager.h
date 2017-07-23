#ifndef COMP2006_ASSIGNMENT3_TURNMANAGER_H
#define COMP2006_ASSIGNMENT3_TURNMANAGER_H

class turnManager {
    private:
        int current;
        int totalPlayer;

    public:

    int getTotalPlayer() const {
        return totalPlayer;
    }

    void setTotalPlayer(int totalPlayer) {
        turnManager::totalPlayer = totalPlayer;
    }

    int getCurrent() const {
        return current;
    }

    void setCurrent(int current) {
        turnManager::current = current;
    }
    /**
     * Advance current to next player, if the next player is out of bounds (larger than current players playing game)
     * then reset back to the first player
     */
    void next() {
        if(current+1>=totalPlayer) {
            current = 0;
        } else {
            current++;
        }
    }

};

#endif //COMP2006_ASSIGNMENT3_TURNMANAGER_H
