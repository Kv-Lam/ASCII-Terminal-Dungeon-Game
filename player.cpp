#include "player.h"
#include <iostream>
#include <cctype>

Player::Player() {
    char confirmation = ' ';
    while(toupper(confirmation) != 'Y') {
        std::cout << "Please enter your character's name: ";
        std::cin >> this->name;
        std::cout << "Are you sure you want " << this->name << " to be your name (y or n)? ";
        std::cin >> confirmation;
    }
    atk = 5; //Starting atk = 5;
    maxHP = currentHP = 10; //Starting HP = 10
}

const int Player::getAttack() {
    return atk;
}

const int Player::getCurrentHP() {
    return currentHP;
}

const int Player::getMaxHP() {
    return maxHP;
}

const std::string Player::getPlayerName() {
    return name;
}

const void Player::decisions() {
    char choice = ' ';
    while(choice != 'Q') {
        std::cout << "\n\033[4mAvailable Options\033[0m\nM) Move\nI) Inventory\nS) Stats\nQ) Quit\nPlease enter your letter choice: ";
        while(true) {
            std::cin >> choice;
            choice = std::toupper(choice);
            if(choice == 'M' || choice == 'I' || choice == 'S' || choice == 'Q') break;
            std::cout << "Invalid choice. Please enter M, I, S, or Q: ";
        }
        switch(choice) {
            case 'M':
                break;
            case 'I':
                break;
            case 'S':
                std::cout << "\n\033[4m" << name << "'s stats\033[0m" << std::endl; //Underlined playerName's stats.
                std::cout << "HP: " << currentHP << '/' << maxHP << std::endl;
                std::cout << "ATK: " << atk << std::endl;
                break;
            case 'Q':
                std::cout << "Thank you for playing, " << name << '!' << std::endl;
                return;
        }
    }
        return;
}