#ifndef ROOMS_H
#define ROOMS_H

#include <string>
#include "enemies.h"

class Enemies; //Forward declaration for compiling.

class Rooms {
    friend class Inventory;
    friend class Player;
    friend Rooms *loadRooms(const std::string dungeonFilename);
    public:
        //Following four variables will hold which rooms the direction leads to.
        Rooms(); //Sets all cardinal directions to -1, enemy to NULL, and ASCIIRoomArt to "".
        ~Rooms(); //Deletes enemy.
        //Following four exit directions will be set to the room index the exit leads to.
        int north;
        int south;
        int east;
        int west; 
        std::string name;
        std::string description;
        std::string ASCIIRoomArt;
        const std::string getASCIIRoomArt(); //Returns ASCIIRooomArt to prevent any accidental changes after first read.
    private:
        void createEnemy(std::string enemyName, std::string enemyDialogue, std::string ASCIIEnemyArt, int HP, int atk); //Ran if there is an enemy inside file for the rooms.
        void deleteEnemy(); //Ran when enemy's health == 0.
        Enemies *enemy; //Will either point to NULL or a created enemy.
};

#endif