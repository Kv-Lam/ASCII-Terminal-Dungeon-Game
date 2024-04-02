#include "bag.h"
#include <iostream>
#include <algorithm>

Bag::Bag(){}

void Bag::interactBag(Player *player) {
    const std::string itemNames[3] = {"health potion", "max health potion", "attack potion"};
    std::cout << "\n\033[4m" << player->name << "'s bag\033[0m" << std::endl;
    std::string bagChoice;
    while(true) {
        for(auto it = bag.begin(); it != bag.end(); it++) {
            std::cout << it->first << " (" << it->second << ')' << std::endl;
        }
        while(true) {
            std::cout << "Please enter the item (full name) you want to use (enter back if you want to leave inventory): ";
            std::cin >> bagChoice;
            for(char &c : bagChoice) c = tolower((char) c);
            if(bagChoice == "back") return;
            for(std::string s : itemNames) if(bagChoice == s) break;
            std::cout << "Invalid item name." << std::endl;
        }
        switch(bagChoice[0]) {
            case 'p': //Potion
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

        //Print statement printing out what's in your bag along with item information.

    }
    return;
}

void Bag::addItem(std::string itemName, int quantity) {
    bag[itemName] += quantity;
    return;
}

void Bag::removeItem(std::string itemName, int quantity) {
    bag[itemName] -= quantity;
    //Gotta make a thing to remove the item from inventory entirely if it's == 0.
    return;
}