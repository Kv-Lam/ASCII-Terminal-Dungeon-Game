#include <iostream>
#include "room.h"

Room::Room() {
    north = south = east = west = -1;
}

Room::~Room() {
    delete enemy;
}

int Room::getExit(const Room &room, const char direction) {
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

void Room::setExit(Room &room, const char direction, const int roomIndex) {
    switch(direction)
    {
        case 'n':
            north = roomIndex;
            break;
        case 's':
            south = roomIndex;
            break;
        case 'e':
            east = roomIndex;
            break;
        case 'w':
            west = roomIndex;
            break;
    }
    return;
}

void Room::printRoomASCII() {
    std::cout << ASCIIRoomArt << std::endl;
    return;
}

void Room::printEnemyASCII() {
    std::cout << ASCIIEnemyArt << std::endl;
    return;
}

void Room::createEnemy(std::string enemyName, int HP, int atk) {
    enemy = new Enemies(enemyName, HP, atk); //Before calling this, first check if there is an enemy.
    return;
}

void Room::deleteEnemy() {
    delete enemy; //Before calling this, first check if enemy's health is == 0.
    return;
}
