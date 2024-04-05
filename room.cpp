#include <iostream>
#include <fstream>
#include <sstream>
#include "room.h"

Room::Room() {
    north = south = east = west = -1;
    enemy = NULL;
}

Room::~Room() {
    delete enemy;
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