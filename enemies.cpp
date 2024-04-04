#include "enemies.h"

Enemies::Enemies(std::string enemyName, int HP, int atk) {
    this->enemyName = enemyName;
    this->HP = HP;
    this->atk = atk;
}

std::string Enemies::getEnemyName() {
    return enemyName;
}

int Enemies::getHP() {
    return HP;
}

int Enemies::getMaxHP() {
    return maxHP;
}

int Enemies::getAttack() {
    return atk;
}