#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>
#include <string>
#include "inventory.h"

class Inventory;
class Rooms;

class Player {
    friend class Inventory;
    public:
        Player(); //Prompts for user name (asks for confirmation) and sets base atk & hp to 5 and 10 respectively.
        const int getAttack();
        const int getCurrentHP();
        const int getMaxHP();
        const std::string getPlayerName();
        const void decisions(Inventory &inventory, Rooms *room);
        void displayStats();
        bool combat(Rooms &room, Inventory &inventory);
    private:
        int maxHP;
        int currentHP;
        int atk;
        std::string name;
};

#endif