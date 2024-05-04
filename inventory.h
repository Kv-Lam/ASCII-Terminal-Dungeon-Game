#ifndef BAG_H
#define BAG_H

#include <string>
#include <unordered_map>
#include "player.h"

class Player; //Forward declaring player class to allow for compiling.

class Inventory {
    friend class Player;
    public:
        Inventory();
        void interactInventory(Player *player);
    private:
        void addItem(const std::string itemName, int quantity);
        void removeItem(const std::string itemName, int quantity);
        bool inInventory(const std::string itemName);
        std::unordered_map<std::string, int> inventory; //Item name is mapped to quantity.
};

#endif