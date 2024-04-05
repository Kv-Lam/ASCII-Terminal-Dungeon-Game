#ifndef ROOMS_H
#define ROOMS_H

#include <string>
#include <vector>

#include "enemies.h"

class Enemies; //Forward declaration for compiling.

class Rooms {
    public:
        //Following four variables will hold which rooms the direction leads to.
        Rooms();
        ~Rooms();
        int north;
        int south;
        int east;
        int west; 
        std::string name;
        std::string description;
        std::string ASCIIRoomsArt;
        std::string ASCIIEnemyArt;
        void printRoomsASCII();
        void printEnemyASCII();
    private:
        void createEnemy(std::string enemyName, int HP, int atk); //Ran if there is an enemy inside file for the rooms.
        void deleteEnemy(); //Ran when enemy's health == 0.
        Enemies *enemy; //Will either point to NULL or a created enemy.
};

#endif