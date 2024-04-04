#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

#include "enemies.h"

class Enemies; //Forward declaration for compiling.

class Room {
    public:
        Room();
        ~Room();
        std::string name;
        std::string description;
        std::string ASCIIRoomArt;
        std::string ASCIIEnemyArt; //MAYBE?
        void printRoomASCII();
        void printEnemyASCII();
    private:
        int getExit(const Room &room, const char direction);
        void setExit(Room &room, const char direction, const int roomIndex);
        void createEnemy(std::string enemyName, int HP, int atk);
        void deleteEnemy();
        Enemies *enemy;
        //Following four variables will hold which room the direction leads to.
        int north; 
        int south;
        int east;
        int west; 
};

#endif
