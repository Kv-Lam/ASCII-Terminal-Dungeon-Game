#include "player.h"
#include "rooms.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cctype>

//Following two functions are helpers.
std::string getDirectionName(const char direction) {
    switch(direction) {
        case 'n':
            return "north";
        case 's': 
            return "south";
        case 'e':
            return "east";
        case 'w':
            return "west";
    }
    return "ERROR";
}

int getExit(const Rooms &room, const char direction) {
    switch(direction)
    {
        case 'n':
            return room.north;
        case 's':
            return room.south;
        case 'e':
            return room.east;
        case 'w':
            return room.west;
    }
    return 0; //Returns 0 to avoid warnings.
}

Player::Player() {
    char confirmation;
    do {
        std::cout << "Please enter your character's name: ";
        getline(std::cin, name, '\n');
        std::cout << "Are you sure you want " << name << " to be your name (y or n)? ";
        std::cin >> confirmation;
        std::cin.get(); //Gets rid of newline at the end of confirmation.
    } while(tolower(confirmation) != 'y');
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

void look(const Rooms &room) {
    std::cout << '\n' << room.name << '\n' << room.description << '\n';
    std::cout << '\n' << room.ASCIIRoomArt << std::endl;
    std::cout << "\nExits:";
    if(-1 < room.north) std::cout << " n";
    if(-1 < room.south) std::cout << " s";
    if(-1 < room.east) std::cout << " e";
    if(-1 < room.west) std::cout << " w";
    std::cout << std::endl;
    return;
}

void move(const Rooms *room, size_t &currentRoom) {
    char exitChoice;
    while(true) {
        std::cout << "Which exit would you like to take? ";
        std::cin >> exitChoice;
        switch(exitChoice) {
            case 'n': case 's' : case 'e' : case 'w':
                if(-1 == getExit(room[currentRoom], exitChoice)) {
                    std::cout << "You can't go " << getDirectionName(exitChoice) << '!' << std::endl;
                    break;
                }
                //Following code is for a valid direction input.
                std::cout << "\nYou moved " << getDirectionName(exitChoice) << '.' << std::endl;
                currentRoom = getExit(room[currentRoom], exitChoice); 
                return;
            default:
                std::cout << "Invalid exit!" << std::endl;
                break;
        }
    }
}

void Player::displayStats() {
    std::cout << "\n\033[4m" << name << "'s stats\033[0m" << std::endl; //Underlined playerName's stats.
    std::cout << "HP: " << currentHP << '/' << maxHP << std::endl;
    std::cout << "ATK: " << atk << std::endl;
    return;
}

bool Player::combat(Rooms &room, Inventory &inventory) {
    std::cout << name << " has encountered " << room.enemy->enemyName << '!' << std::endl;
    if(!room.enemy->enemyDialogue.empty()) std::cout << room.enemy->enemyName << ": " << room.enemy->getEnemyDialogue() << std::endl;
    if(!room.enemy->ASCIIEnemyArt.empty()) std::cout << room.enemy->getASCIIEnemyArt() << std::endl;
    char choice;
    int turn = 0;
    const std::string itemNames[] = {"health potion", "max health potion", "attack potion"};
    srand(time(NULL));
    while(true) {
        switch(turn % 2) {
            case 0: //Player's turn.
                displayStats();
                room.enemy->displayEnemyStats();
                while(true) {
                    std::cout << "\n\033[4mPlease select your move\033[0m\nA) Attack\nI) Inventory\nR) Run\nPlease enter your letter choice: ";
                    std::cin >> choice;
                    choice = tolower(choice);
                    if(choice != 'a' && choice != 'i' && choice != 'r') std::cout << "Invalid choice!" << std::endl;
                    else {
                        std::cin.get(); //Gets rid of the '\n' at the end of the choice.
                        break;
                    }
                }
                switch(choice) {
                    case 'a': //Attack.
                        std::cout << '\n' << name << " attacked the " << room.enemy->getEnemyName() << " for " << getAttack() << " damage!" << std::endl;
                        room.enemy->HP = std::max(0, room.enemy->HP - getAttack());
                        if(room.enemy->getHP() <= 0) {
                            int itemReceivedIndex = rand() % 3;
                            std::cout << name << " has killed the " << room.enemy->getEnemyName() << " and received a/an " << itemNames[itemReceivedIndex] << "!" << std::endl;
                            room.deleteEnemy();
                            inventory.addItem(itemNames[itemReceivedIndex], 1);
                            return true;
                        }
                        break;
                    case 'i': //Inventory.
                        if(!inventory.interactInventory(this, true)) turn--; //If player did not use anything, then makes it player's turn again.
                        break;
                    case 'r': //Run.
                        if(rand() % 10 < 2) { //20% chance to fail running.
                            currentHP--;
                            std::cout << "\nYou failed to run away and took 1 damage as a result!" << std::endl;
                        }
                        else {
                            std::cout << "\nYou turned tail and successfully fled from the battle!" << std::endl;
                            std::cout << "\nExits:";
                            if(-1 < room.north) std::cout << " n";
                            if(-1 < room.south) std::cout << " s";
                            if(-1 < room.east) std::cout << " e";
                            if(-1 < room.west) std::cout << " w";
                            std::cout << std::endl;
                            return false;
                        }
                        break;
                }
                break;
            case 1: //Enemy's turn.
                std::cout << room.enemy->getEnemyName() << " attacked " << name << " for " << room.enemy->getAttack() << "!" << std::endl;
                if((currentHP = std::max(0, currentHP - room.enemy->getAttack())) <= 0) { //TODO: Check if player died inside of decisions().
                    return false;
                }
                break;
        }
        
        turn++;
    }
    return false;
}

const void Player::decisions(Inventory &inventory, Rooms *room) {
    char choice;
    size_t currentRoom = 0;
    do {
        std::cout << "\n\033[4mAvailable Options\033[0m\nM) Move\nL) Look\nI) Inventory\nS) Stats\nQ) Quit\nPlease enter your letter choice: ";
        while(true) {
            std::cin >> choice;
            choice = std::tolower(choice);
            if(choice == 'm' || choice == 'l' || choice == 'i' || choice == 's' || choice == 'q') {
                std::cin.get();
                break;
            }
            std::cout << "Invalid choice. Please enter M, L, I, S, or Q: ";
        }
        switch(choice) {
            case 'm': //For movement and combat.
                while(true) {
                    if(currentHP <= 0) {
                        std::cout << name << " has been slain! Game over." << std::endl;
                        return;
                    }
                    move(room, currentRoom);
                    if(room[currentRoom].enemy != NULL) { //There is an enemy.
                        //if enemy is not killed (combat returns true if killed) force player to move. 1 hp if you fail running. srand(time) % 10. If < 4, fail running.
                        //If enemy is not killed, force player to move. Boss room (vector size - 2) should not allow running.

                        //Player killed enemy. If player ran, will force player to keep moving until they go to a room without a monster
                        //or a room where they've already killed the monster. If they died, will end the game from first if-statement.
                        if(this->combat(room[currentRoom], inventory)) break;
                    }
                    else break; //There's no enemy.
                }
                break;
            case 'l': //For look.
                look(room[currentRoom]);
                break;
            case 'i': //Inventory.
                (void) inventory.interactInventory(this, false);
                break;
            case 's': //Stats.
                displayStats();
                break;
            case 'q': //Quit game.
                std::cout << "Thank you for playing, " << name << '!' << std::endl;
                //NEED TO DELETE ALL ALLOCATED STUFF IN MAIN.
                return;
        }
    } while(choice != 'Q');
    return;
}