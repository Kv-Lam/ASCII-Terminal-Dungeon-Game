#include "enemies.h"

Enemies::Enemies(std::string enemyName, std::string enemyDialogue, int HP, int atk) {
    this->enemyName = enemyName;
    this->enemyDialogue = enemyDialogue;
    this->HP = HP;
    this->atk = atk;
}

const std::string Enemies::getEnemyName() {
    return enemyName;
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