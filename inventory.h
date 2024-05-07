#ifndef BAG_H
#define BAG_H

#include <string>
#include <unordered_map>
#include "player.h"

class Player; //Forward declaring player class to allow for compiling.

class Inventory {
    friend class Player;
    public:
        Inventory(); //Constructor that does nothing.
        bool interactInventory(Player *player, const bool &isInCombat); //Allows the user to use the items inside their inventory. Returns true if item is used. False if not. If isInCombat is true, only a single item can be used before the function returns. If false, allows usage of multiple items. 
    private:
        void addItem(const std::string itemName, int quantity); //Adds quantity itemName into inventory. Inserts key with a value of 0 if item does not exist in inventory yet.
        void removeItem(const std::string itemName, int quantity); //Removes quantity itemName from inventory. Erases key from unordered map if quantity == 0 after removal.
        bool inInventory(const std::string itemName); //Finds itemName inside of inventory hash table. If found, return true. If not found, return false.
        std::unordered_map<std::string, int> inventory; //Item name is mapped to quantity. So, key = itemName and value = quantity.
};

#endif