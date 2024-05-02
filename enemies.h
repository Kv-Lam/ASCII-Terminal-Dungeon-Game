#ifndef ENEMIES_H
#define ENEMIES_H

#include <string>
#include "rooms.h"

class Enemies {
friend class Room;
friend class Player;
    public:
        Enemies(std::string enemyName, std::string enemyDialogue, std::string ASCIIEnemyArt, int HP, int atk);
        const void displayEnemyStats();
        const int getHP();
        const int getMaxHP();
        const int getAttack();
        const std::string getEnemyName();
        const std::string getEnemyDialogue();
        const std::string getASCIIEnemyArt();
    private:
        int HP;
        int maxHP;
        int atk;
        std::string enemyName;
        std::string enemyDialogue;
        std::string ASCIIEnemyArt;
};

#endif
