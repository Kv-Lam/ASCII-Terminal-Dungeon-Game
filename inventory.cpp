#include "inventory.h"
#include <iostream>
#include <algorithm>

Inventory::Inventory(){}

bool Inventory::interactInventory(Player *player) { //TODO: FIX ACTUALLY USING THE ITEMS.
    const std::string itemNames[] = {"HEALTH POTION", "MAX HEALTH POTION", "ATTACK POTION"}; //Maybe move this to the private data members inside .h.
    std::string inventoryChoice;
    while(true) {
        std::cout << "\n\033[4m" << player->name << "'s inventory\033[0m" << std::endl;
        u_short itemNum = 0;
        for(auto it = inventory.begin(); it != inventory.end(); it++) {
            itemNum++;
            std::cout << itemNum << ": " << it->first << " (" << it->second << ')' << std::endl;
        }
        while(true) {
            std::cout << "\nPlease enter the item (full name) you want to use (enter back if you want to leave inventory): ";
            std::getline(std::cin, inventoryChoice, '\n');
            bool validItem = false;

            for(char &c : inventoryChoice) c = toupper(c);

            if(inventoryChoice == "BACK") return false;

            for(std::string s : itemNames) {
                if(inventoryChoice == s) {
                    validItem = true;
                    break;
                }
            }
            
            if(validItem) break;
            else std::cout << "Invalid item name." << std::endl;
        }

        if(inInventory(inventoryChoice)) {
            switch(inventoryChoice[0]) {
            case 'H': //Health potion
                player->currentHP = std::min(player->maxHP, player->currentHP + 3); //Can change how much potions give.
                removeItem(inventoryChoice, 1);
                break;
            case 'M': //Max health potion
                player->maxHP += 1;
                player->currentHP += 1;
                removeItem(inventoryChoice, 1);
                break;
            case 'A': //Attack potion
                player->atk += 1;
                removeItem(inventoryChoice, 1);
                break;
            }
            return true;
        }
        else std::cout << "You do not have any " << inventoryChoice << "s!" << std::endl;
    }
}

void Inventory::addItem(std::string itemName, int quantity) {
    if(!inventory.count(itemName)) inventory.insert({itemName, 0});
    inventory[itemName] += quantity;
    return;
}

void Inventory::removeItem(std::string itemName, int quantity) { //Fix this to delete the key if value == 0.
    inventory[itemName] -= quantity;
    if(!inInventory(itemName)) inventory.erase(itemName);
    return;
}

bool Inventory::inInventory(const std::string itemName) {
    if(inventory.find(itemName) == inventory.end()) return false;
    else return true;
}