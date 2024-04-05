#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

#include "enemies.h"

class Enemies; //Forward declaration for compiling.

class Room {
    friend void setExit(Room &room, const char direction, const int roomIndex);
    friend int getExit(const Room &room, const char direction);
    public:
        Room();
        ~Room();
        std::string name;
        std::string description;
        std::string ASCIIRoomArt;
        std::string ASCIIEnemyArt;
        void printRoomASCII();
        void printEnemyASCII();
    private:
        void createEnemy(std::string enemyName, int HP, int atk); //Ran if there is an enemy inside file for the room.
        void deleteEnemy(); //Ran when enemy's health == 0.
        Enemies *enemy; //Will either point to NULL or a created enemy.
        //Following four variables will hold which room the direction leads to.
        int north;
        int south;
        int east;
        int west; 
};

#endif