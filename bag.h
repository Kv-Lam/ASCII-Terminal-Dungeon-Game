#ifndef BAG_H
#define BAG_H

#include <string>
#include <unordered_map>
#include "player.h"

class Bag {
    friend class Player;
    public:
        Bag();
    private:
        void interactBag(Player *player);
        void addItem(const std::string itemName, int quantity);
        void removeItem(const std::string itemName, int quantity);
        std::unordered_map<std::string, int> bag; //Item name is mapped to quantity.
};

#endif