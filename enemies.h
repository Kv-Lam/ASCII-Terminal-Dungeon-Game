#ifndef ENEMIES_H
#define ENEMIES_H

#include <string>
#include "rooms.h"

class Enemies {
friend class Room;
    public:
        Enemies(std::string enemyName, std::string enemyDialogue, int HP, int atk);
        const int getHP();
        const int getMaxHP();
        const int getAttack();
        const std::string getEnemyName();
        const std::string getEnemyDialogue();
    private:
        int HP;
        int maxHP;
        int atk;
        std::string enemyName;
        std::string enemyDialogue;
};

#endif
