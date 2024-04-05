#ifndef ENEMIES_H
#define ENEMIES_H

#include <string>
#include "rooms.h"

class Enemies {
friend class Room;
    public:
        Enemies(std::string enemyName, int HP, int atk);
        const int getHP();
        const int getMaxHP();
        const int getAttack();
        const std::string getEnemyName();
    private:
        int HP;
        int maxHP;
        int atk;
        std::string enemyName;
};

#endif
