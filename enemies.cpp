#include <iostream>
#include "enemies.h"

Enemies::Enemies(std::string enemyName, std::string enemyDialogue, std::string ASCIIEnemyArt, int HP, int atk) {
    this->enemyName = enemyName;
    this->enemyDialogue = enemyDialogue;
    this->ASCIIEnemyArt = ASCIIEnemyArt;
    this->HP = HP;
    this->atk = atk;
}

const void Enemies::displayEnemyStats() {
    std::cout << "\n\033[4m" << enemyName << "'s stats\033[0m" << std::endl; //Underlined enemyName's stats.
    std::cout << "HP: " << HP << '/' << maxHP << std::endl;
    std::cout << "ATK: ?" << std::endl; //atk << std::endl; if you want to actually display the attack of the enemy.
    return;
}

const std::string Enemies::getEnemyName() {
    return enemyName;
}

const std::string Enemies::getEnemyDialogue() {
    return enemyDialogue;
}

const std::string Enemies::getASCIIEnemyArt() {
    return ASCIIEnemyArt;
}

const int Enemies::getHP() {
    return HP;
}

const int Enemies::getMaxHP() {
    return maxHP;
}

const int Enemies::getAttack() {
    return atk;
}