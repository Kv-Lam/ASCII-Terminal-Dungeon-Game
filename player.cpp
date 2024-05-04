#include "player.h"
#include "rooms.h"
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
    } while(toupper(confirmation) != 'Y');
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

bool Player::combat(Rooms &room, Bag &inventory) {
    std::cout << name << " has encountered " << room.enemy->enemyName << '!' << std::endl;
    if(!room.enemy->enemyDialogue.empty()) std::cout << room.enemy->enemyName << ": " << room.enemy->getEnemyDialogue() << std::endl;
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
                    std::cout << "\n\033[4mPlease select your move\033[0m\nA) Attack\nI) Inventory\nR) Run\nE) Enemy Art\nPlease enter your letter choice: ";
                    std::cin >> choice;
                    choice = toupper(choice);
                    if(choice != 'A'|| choice != 'I' || choice != 'R' || choice != 'E') std::cout << "Invalid choice!" << std::endl;
                    else break;
                }
                switch(toupper(choice)) {
                    case 'A': //Attack.
                        std::cout << name << " attacked the " << room.enemy->getEnemyName() << " for " << getAttack() << " damage!" << std::endl;
                        room.enemy->HP -= getAttack();
                        std::cout << room.enemy->getEnemyName() << "'s HP: " << room.enemy->getHP();
                        if(room.enemy->getHP() <= 0) {
                            int itemReceivedIndex = rand() % 3;
                            std::cout << name << " has killed the " << room.enemy->getEnemyName() << " and received a/an " << itemNames[itemReceivedIndex] << "!";
                            room.deleteEnemy();
                            inventory.addItem(itemNames[itemReceivedIndex], 1);
                            return true;
                        }
                        break;
                    case 'I': //Inventory.
                        inventory.interactBag(this);
                        break;
                    case 'R': //Run.
                        if(rand() % 10 < 2) { //20% chance to fail running.
                            currentHP--;
                            std::cout << "You failed to run away and took 1 damage as a result!" << std::endl;
                        }
                        else {
                            std::cout << "You turned tail and successfully fled from the battle!" << std::endl;
                            return false;
                        }
                        break;
                    case 'E':
                        std::cout << room.enemy->getASCIIEnemyArt() << std::endl;
                        break;
                }
                break;
            case 1: //Enemy's turn.
                std::cout << room.enemy->getEnemyName() << " attacked " << name << " for " << room.enemy->getAttack() << "!";
                if((currentHP -= room.enemy->getAttack()) <= 0) { //TODO: Check if player died inside of decisions().
                    std::cout << name << " has been slain! Game over." << std::endl;
                    return false;
                }
                break;
        }
        
        turn++;
    }
    return false;
}

const void Player::decisions(Bag &inventory, Rooms *room) {
    char choice = ' ';
    size_t currentRoom = 0;
    do {
        std::cout << "\n\033[4mAvailable Options\033[0m\nM) Move\nL) Look\nB) Bag\nS) Stats\nQ) Quit\nPlease enter your letter choice: ";
        while(true) {
            std::cin >> choice;
            choice = std::toupper(choice);
            if(choice == 'M' || choice == 'L' || choice == 'B' || choice == 'S' || choice == 'Q') {
                std::cin.get();
                break;
            }
            std::cout << "Invalid choice. Please enter M, L, B, S, or Q: ";
        }
        switch(choice) {
            case 'M': //For movement and combat.
                while(true) {
                    if(currentHP <= 0) {
                        std::cout << name << " has died! Game over." << std::endl;
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
            case 'L': //For look.
                look(room[currentRoom]);
                break;
            case 'B': //Bag.
                inventory.interactBag(this);
                break;
            case 'S': //Stats.
                displayStats();
                break;
            case 'Q': //Quit game.
                std::cout << "Thank you for playing, " << name << '!' << std::endl;
                //NEED TO DELETE ALL ALLOCATED STUFF IN MAIN.
                return;
        }
    } while(choice != 'Q');
    return;
}