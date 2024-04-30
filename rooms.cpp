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

void Rooms::createEnemy(std::string enemyName, int HP, int atk) {
    if(enemyName == "none") return;
    enemy = new Enemies(enemyName, HP, atk);
    return;
}

void Rooms::deleteEnemy() {
    if(!enemy->getHP()) delete enemy; //Deletes enemy if the health of it is == 0.
    return;
}