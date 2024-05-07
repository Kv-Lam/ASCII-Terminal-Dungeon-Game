#ifndef ENEMIES_H
#define ENEMIES_H

#include <string>
#include "rooms.h"

class Enemies {
friend class Room;
friend class Player;
    public:
        Enemies(std::string enemyName, std::string enemyDialogue, std::string ASCIIEnemyArt, int HP, int atk);
        const void displayEnemyStats(); //Helper function to print enemy stats when combat starts.
        const int getHP(); //Returns HP.
        const int getMaxHP(); //Returns maxHP.
        const int getAttack(); //Returns atk.
        const std::string getEnemyName(); //Returns enemyName for printing to terminal.
        const std::string getEnemyDialogue(); //Returns enemyDialogue for printing to terminal.
        const std::string getASCIIEnemyArt(); //Returns ASCIIEnemyArt for printing to terminal.
    private:
        int HP;
        int maxHP;
        int atk;
        std::string enemyName;
        std::string enemyDialogue;
        std::string ASCIIEnemyArt;
};

#endif
