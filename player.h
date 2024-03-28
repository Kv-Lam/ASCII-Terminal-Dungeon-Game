#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>
#include <string>

class Player {
    public:
        Player(); //Prompts for user name (asks for confirmation) and sets base atk & hp to 5 and 10 respectively.
        const int getAttack();
        const int getCurrentHP();
        const int getMaxHP();
        const std::string getPlayerName();
        const void decisions();
        //void interactInventory();
    private:
        int maxHP;
        int currentHP;
        int atk;
        std::string name;
        std::unordered_map<std::string, int> inventory; //Item name is mapped to quantity.
};

#endif