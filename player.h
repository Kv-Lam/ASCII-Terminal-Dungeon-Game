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
        const int getAttack(); //Returns atk.
        const int getCurrentHP(); //Returns currentHP.
        const int getMaxHP(); //Returns maxHP.
        const std::string getPlayerName(); //Returns name.
        const void decisions(Inventory &inventory, Rooms *room); //The actual game. Calls different functions based on the player's decision.
        void displayStats(); //Prints out the player's current stats.
        bool combat(Rooms &room, Inventory &inventory); //Combat system. Returns true if enemy is killed, false if not.
    private:
        int maxHP;
        int currentHP;
        int atk;
        std::string name;
};

#endif