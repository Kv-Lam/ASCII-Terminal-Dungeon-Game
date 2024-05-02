#include <iostream>
#include <fstream>
#include <sstream>
#include "rooms.h"

Rooms::Rooms() {
    north = south = east = west = -1;
    enemy = NULL;
    ASCIIRoomArt = "";
}

Rooms::~Rooms() {
    delete enemy;
}

const std::string Rooms::getASCIIRoomArt() {
    return ASCIIRoomArt;
}

void Rooms::createEnemy(std::string enemyName, std::string enemyDialogue, std::string ASCIIEnemyArt, int HP, int atk) {
    if(isspace(enemyName[0])) return; //If the first character is a space, then don't create an enemy. TODO: MOVE THIS TO LOADROOM AS A CHECK TO CALL CREATEENEMY.
    enemy = new Enemies(enemyName, enemyDialogue, ASCIIEnemyArt,HP, atk);
    return;
}

void Rooms::deleteEnemy() {
    delete enemy; //Deletes enemy if the health of it is == 0.
    return;
}