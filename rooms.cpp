#include <iostream>
#include <fstream>
#include <sstream>
#include "rooms.h"

Rooms::Rooms() {
    north = south = east = west = -1;
    enemy = NULL;
}

Rooms::~Rooms() {
    delete enemy;
}

void Rooms::printRoomsASCII() {
    std::cout << ASCIIRoomsArt << std::endl;
    return;
}

void Rooms::printEnemyASCII() {
    std::cout << ASCIIEnemyArt << std::endl;
    return;
}

void Rooms::createEnemy(std::string enemyName, int HP, int atk) {
    enemy = new Enemies(enemyName, HP, atk); //Before calling this, first check if there is an enemy.
    return;
}

void Rooms::deleteEnemy() {
    delete enemy; //Before calling this, first check if enemy's health is == 0.
    return;
}