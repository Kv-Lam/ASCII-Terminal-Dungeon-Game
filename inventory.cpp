#include "inventory.h"
#include <iostream>
#include <algorithm>

Inventory::Inventory(){}

bool Inventory::interactInventory(Player *player, const bool &isInCombat) {
    //Following variables are for the amount of respective stats the item will give to the player.
    short healthPotionHeal = 5;
    short maxHPPotionGive = 2;
    short attackPotionGive = 1;

    const std::string itemNames[] = {"health potion", "max health potion", "attack potion"}; //Items implemented. Used to check if user enters a valid item.
    std::string inventoryChoice;
    
    while(true) {
        //Following six lines are for printing the items inside of player's inventory.
        std::cout << "\n\033[4m" << player->name << "'s inventory\033[0m" << std::endl;
        u_short itemNum = 0;
        for(auto it = inventory.begin(); it != inventory.end(); it++) {
            itemNum++;
            std::cout << itemNum << ": " << it->first << " (" << it->second << ')' << std::endl;
        }

        //Following while loop asks for what item user wishes to use and checks whether it is an actual item that is in itemNames[]. If player enters "back", leaves inventory.
        while(true) {
            std::cout << "\nPlease enter the item (full name) you want to use (enter back if you want to leave inventory): ";
            std::getline(std::cin, inventoryChoice, '\n');
            bool validItem = false;

            for(char &c : inventoryChoice) c = tolower(c);

            if(inventoryChoice == "back") return false;

            for(std::string s : itemNames) {
                if(inventoryChoice == s) {
                    validItem = true;
                    break;
                }
            }
            
            if(validItem) break;
            else std::cout << "Invalid item name." << std::endl;
        }

        /* Checks if the player has the item. If they do, remove one (amount can be changed if wanting to add a way for users to use
        multiple of one item) of the item from their inventory. For this, additional checks must be added to removeItem and addItem. */

        if(inInventory(inventoryChoice)) {
            switch(inventoryChoice[0]) { //Goes off of the first letter in the item name, but can be changed to enums for more items with same starting letter.
            case 'h': //Health potion
                player->currentHP = std::min(player->maxHP, player->currentHP + healthPotionHeal); //Can change how much potions give.
                removeItem(inventoryChoice, 1);
                std::cout << '\n' << player->name << " healed " << healthPotionHeal <<" HP!" << std::endl; 
                break;
            case 'm': //Max health potion
                player->maxHP += maxHPPotionGive;
                player->currentHP += maxHPPotionGive;
                removeItem(inventoryChoice, 1);
                std::cout << '\n' << player->name << "'s max health increased by " << maxHPPotionGive << "!" << std::endl;
                break;
            case 'a': //Attack potion
                player->atk += attackPotionGive;
                removeItem(inventoryChoice, 1);
                std::cout << '\n' << player->name << "'s attack increased by " << attackPotionGive << "!" << std::endl;
                break;
            }
            if(isInCombat) return true;
        }
        else std::cout << "You do not have any " << inventoryChoice << "s!" << std::endl;
    }
}

void Inventory::addItem(std::string itemName, int quantity) {
    if(!inventory.count(itemName)) inventory.insert({itemName, 0}); //Adds the key and value into the hash table if it doesn't exist or previously got deleted by removeItem().
    inventory[itemName] += quantity;
    return;
}

void Inventory::removeItem(std::string itemName, int quantity) {
    inventory[itemName] -= quantity;
    if(inventory[itemName] == 0) inventory.erase(itemName); //Deletes key from data structure (unordered map) if player no longer has any of the item. 
    return;
}

bool Inventory::inInventory(const std::string itemName) {
    if(inventory.find(itemName) == inventory.end()) return false;
    else return true;
}