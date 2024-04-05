#ifndef ENEMIES_H
#define ENEMIES_H

#include <string>
#include "rooms.h"

class Enemies {
friend class Room;
    public:
        Enemies(std::string enemyName, int HP, int atk);
        const std::string getEnemyName();
        const int getHP();
        const int getMaxHP();
        const int getAttack();
    private:
        std::string enemyName;
        int HP;
        int maxHP;
        int atk;
};

#endif
