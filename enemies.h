#ifndef ENEMIES_H
#define ENEMIES_H

#include <string>
#include "room.h"

class Enemies {
friend class Room;
    public:
        Enemies(std::string enemyName, int HP, int atk);
        std::string getEnemyName();
        int getHP();
        int getMaxHP();
        int getAttack();
    private:
        std::string enemyName;
        int HP;
        int maxHP;
        int atk;
};

#endif
