#include <iostream>
#include <vector>
#include <cctype>
// #include "room.h"
#include "player.h"
// #include "enemies.h"

enum Directions { //Use these for moving in the vector. USE AS INTEGERS.
    Left = -1,
    Right = 1,
    Up = 1,
    Down = -1,
};

enum ObjectsInRoom { //USE THESE AS CHAR VALUES IN ASCII TABLE FOR PRINTING DUNGEON ROOMS.
    Door = 219,
};

int main() {
    // size_t sizeOfDungeon = 5;
    //const Room *rooms;
    Player player;
    player.decisions();
    // std::cout << player.getAttack() << ' ' << player.getHP() << std::endl;
    //int currentRoom = 0;
    // std::vector<std::vector<Room> > dungeon(sizeOfDungeon, std::vector<Room>(sizeOfDungeon)); //Each position corresponds to a new room.
    //std::vector<std::vector<std::string> > dungeon(sizeOfDungeon, std::vector<std::string>(sizeOfDungeon, "st")); This is how to make a 2D sized array of strings.
    // for(int i = 0; i < sizeOfDungeon; i++) {
    //     for(int j = 0; j < sizeOfDungeon; j++) {
    //         std::cout << dungeon[i][j].name;
    //     }
    //     std::cout << std::endl;
    // }
    // delete rooms;
    return 0;
}