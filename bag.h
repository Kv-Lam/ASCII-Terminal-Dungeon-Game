#ifndef BAG_H
#define BAG_H

#include <string>
#include <unordered_map>
#include "player.h"

class Player; //Forward declaring player class to allow for compiling.

class Bag {
    public:
        Bag();
        void interactBag(Player *player);
    private:
        void addItem(const std::string itemName, int quantity);
        void removeItem(const std::string itemName, int quantity);
        bool inBag(const std::string itemName);
        std::unordered_map<std::string, int> bag; //Item name is mapped to quantity.
};

#endif