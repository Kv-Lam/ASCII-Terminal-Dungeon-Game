#include "player.h"
#include "rooms.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <string>

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
    return "ERROR"; //To avoid warnings, but also for any problems with this function.
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
    return 0; //To avoid warnings.
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
                //Checks whether there is an exit there.
                if(-1 == getExit(room[currentRoom], exitChoice)) {
                    std::cout << "You can't go " << getDirectionName(exitChoice) << '!' << std::endl;
                    break;
                }
                
                //Following three lines of code is for a valid direction input.
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
    //Following three lines print enemy info.
    std::cout << '\n' << name << " has encountered " << room.enemy->enemyName << '!' << std::endl;
    if(!room.enemy->enemyDialogue.empty()) std::cout << room.enemy->enemyName << ": " << room.enemy->getEnemyDialogue() << std::endl;
    if(!room.enemy->ASCIIEnemyArt.empty()) std::cout << room.enemy->getASCIIEnemyArt() << std::endl;

    int turn = 0; //Turn counter.
    const std::string itemNames[] = {"health potion", "max health potion", "attack potion"}; //For item drops.
    srand(time(NULL)); //For randomizing which item is dropped from killing enemies.

    while(true) {
        char choice;

        switch(turn % 2) {
            case 0: //Player's turn.
                displayStats();
                room.enemy->displayEnemyStats();

                //Prompts user for turn choice, checks for valid choice, and executes commands based on letter choice.
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

                        //Checks whether the player killed the enemy.
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
                        if(rand() % 10 < 2) { //20% chance to fail running. If player fails, take 1 point of damage.
                            currentHP--;
                            std::cout << "\nYou failed to run away and took 1 damage as a result!" << std::endl;
                        }
                        else { //Successful run.
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
                if((currentHP = std::max(0, currentHP - room.enemy->getAttack())) <= 0) return false; //Updates player's HP after getting attacked and checks if player dies.
                break;
        }
        
        turn++;
    }
    return false;
}

const void Player::decisions(Inventory &inventory, Rooms *room) {
    size_t currentRoom = 0;
    char choice;
    do {
        //Checks if it's the final room after beating boss. All exits must == -1.
        if((room[currentRoom].north == -1) && (room[currentRoom].south == -1) && (room[currentRoom].east == -1) && (room[currentRoom].west == -1)) { 
            std::cout << room[currentRoom].name << '\n' << room[currentRoom].description << std::endl;
            if(!room[currentRoom].ASCIIRoomArt.empty()) std::cout << room[currentRoom].getASCIIRoomArt();
            return;
        }

        //Following code prints available commands, checks whether the command the player enters is valid, and executes the specified command.
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
            case 'm': //For movement. If there is an enemy in the room the player moves to, initiate combat.
                while(true) {
                    move(room, currentRoom);

                    if(room[currentRoom].enemy != NULL) { //There is an enemy.
                        if(this->combat(room[currentRoom], inventory)) break; //If player kills enemy, breaks out of while loop.
                        if(currentHP <= 0) { //If player died, end game.
                            std::cout << name << " has been slain! Game over." << std::endl;
                            return;
                        }
                    }
                    else break; //There's no enemy.
                }
                break;
            case 'l': //Look at room name, description, and art.
                look(room[currentRoom]);
                break;
            case 'i': //Inventory.
                (void) inventory.interactInventory(this, false); //Casts the bool to void, as the boolian isn't used.
                break;
            case 's': //Stats.
                displayStats();
                break;
            case 'q': //Quit game.
                std::cout << "Thank you for playing, " << name << '!' << std::endl;
                return;
        }
    } while(true);
    return;
}