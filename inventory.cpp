#include "inventory.h"
#include <iostream>
#include <algorithm>

Inventory::Inventory(){}

bool Inventory::interactInventory(Player *player, const bool &isInCombat) { //TODO: FIX ACTUALLY USING THE ITEMS.
    const std::string itemNames[] = {"health potion", "max health potion", "attack potion"}; //Maybe move this to the private data members inside .h.
    short healthPotionHeal = 5;
    short maxHPPotionGive = 2;
    short attackPotionGive = 1;
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

        if(inInventory(inventoryChoice)) {
            switch(inventoryChoice[0]) {
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
    if(!inventory.count(itemName)) inventory.insert({itemName, 0});
    inventory[itemName] += quantity;
    return;
}

void Inventory::removeItem(std::string itemName, int quantity) { //Fix this to delete the key if value == 0.
    inventory[itemName] -= quantity;
    if(inventory[itemName] == 0) inventory.erase(itemName);
    return;
}

bool Inventory::inInventory(const std::string itemName) {
    if(inventory.find(itemName) == inventory.end()) return false;
    else return true;
}