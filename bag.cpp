#include "bag.h"
#include <iostream>
#include <algorithm>

Bag::Bag(){}

void Bag::interactBag(Player *player) {
    const std::string itemNames[] = {"health potion", "max health potion", "attack potion"}; //Maybe move this to the private data members inside .h.
    std::string bagChoice;
    while(true) {
        std::cout << "\n\033[4m" << player->name << "'s bag\033[0m" << std::endl;
        u_short itemNum = 0;
        for(auto it = bag.begin(); it != bag.end(); it++) {
            itemNum++;
            std::cout << itemNum << ": " << it->first << " (" << it->second << ')' << std::endl;
        }
        while(true) {
            std::cout << "Please enter the item (full name) you want to use (enter back if you want to leave inventory): ";
            std::getline(std::cin, bagChoice, '\n');
            bool validItem = false;

            for(char &c : bagChoice) c = tolower(c);

            if(bagChoice == "back") return;

            for(std::string s : itemNames) {
                if(bagChoice == s) {
                    validItem = true;
                    break;
                }
            }
            
            if(validItem) break;
            else std::cout << "Invalid item name." << std::endl;
        }

        if(inBag(bagChoice)) {
            switch(bagChoice[0]) {
            case 'p': //Health potion
                player->currentHP = std::min(player->maxHP, player->currentHP + 3); //Can change how much potions give.
                removeItem(bagChoice, 1);
                break;
            case 'm': //Max health potion
                player->maxHP += 1;
                player->currentHP += 1;
                removeItem(bagChoice, 1);
                break;
            case 'a': //Attack potion
                player->atk += 1;
                removeItem(bagChoice, 1);
                break;
            }
        }
        else std::cout << "You do not have any " << bagChoice << "s!" << std::endl;
    }
    return;
}

void Bag::addItem(std::string itemName, int quantity) {
    if(!bag.count(itemName)) bag.insert({itemName, 0});
    bag[itemName] += quantity;
    return;
}

void Bag::removeItem(std::string itemName, int quantity) {
    bag[itemName] -= quantity;
    if(!inBag(itemName)) bag.erase(itemName);
    return;
}

bool Bag::inBag(const std::string itemName) {
    return bag[itemName];
}