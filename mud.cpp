#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "rooms.h"
#include "player.h"
#include "inventory.h"
#include "enemies.h"

void setExit(Rooms &room, const char direction, const int roomIndex) {
    switch(direction)
    {
        case 'n':
            room.north = roomIndex;
            break;
        case 's':
            room.south = roomIndex;
            break;
        case 'e':
            room.east = roomIndex;
            break;
        case 'w':
            room.west = roomIndex;
            break;
    }
    return;
}

void stripWhitespace(std::string &str) {
    // Trim trailing whitespace
    while (!str.empty() && isspace(str.back())) {
        str.pop_back();
    }

    // Trim leading whitespace
    while (!str.empty() && isspace(str.front())) {
        str.erase(str.begin());
    }
    return;
}

Rooms *loadRooms(const std::string dungeonFilename) 
{
    std::ifstream fin(dungeonFilename);
    //Following if-statement checks for any file opening errors.
    if(!(fin.is_open()))
    {
        std::cerr << "Error: File did not open correctly" << std::endl;
        exit(1);
    }

    size_t tildeCount = 0; //# of tildes inside file. 8 for each room.
    std::string stringHolder; //Holds strings for counting # of tildes.
    while(getline(fin, stringHolder, '~')) tildeCount++; //Finds total of tildes inside file.
    
    //Calculates # of rooms. 8 things to read in: room name, room description, exits, room art, enemy name, enemy stats, enemy art, and enemy dialogue.
    size_t roomCount = tildeCount / 8;

    Rooms *rooms = new Rooms[roomCount];

    //Following two lines jumps back to beginning of file.
    fin.clear();
    fin.seekg(0);

    int HP, ATK;

    //Reads in and stores the room's title, description, exits, enemy data, and arts.
    //TODO: ADD READING IN THE ARTS AND ENEMY.
    for (size_t i = 0; i < roomCount; i++) {
        //Following four lines read and store the name and description then removes extra whitespaces.
        getline(fin, rooms[i].name, '~');
        stripWhitespace(rooms[i].name);
        getline(fin, rooms[i].description, '~');
        stripWhitespace(rooms[i].description);

        //Rest of code is for exits and enemy data/arts.
        std::string exits, enemyName, stats, ASCIIEnemyArt, dialogue; //For reading in the exits.
        getline(fin, exits, '~');
        stripWhitespace(exits);
        std::istringstream sin(exits);
        char direction; //Direction of the exit.
        int room_index; //Rooms the exit leads to.
        while(sin >> direction >> room_index) setExit(rooms[i], direction, room_index); //Reads in the direction/index and sets the room exits.
        sin.clear(); //Clears istringstream for use again.
        getline(fin, rooms[i].ASCIIRoomArt, '~');
        getline(fin, enemyName, '~');
        stripWhitespace(enemyName);
        getline(fin, stats, '~');
        stripWhitespace(stats);
        std::istringstream enemyStats(stats);
        enemyStats >> HP >> ATK;
        // std::cout << HP << "Enemy #" << i << "'s HP" << std::endl; //For testing if HP is being correctly stored.
        enemyStats.clear();
        getline(fin, ASCIIEnemyArt, '~');
        getline(fin, dialogue, '~');
        //Read in EVERYTHING about the enemy first. If enemyName ! empty, create enemy with all read in values. Else, do not create enemy.
        if (!enemyName.empty()) rooms[i].createEnemy(enemyName, dialogue, ASCIIEnemyArt, HP, ATK);
    }

    //dumpRoomss(rooms, roomCount); //Uncomment for debugging.

    fin.close();
    return rooms;
}


int main(int argc, char *argv[]) {
    if(2 != argc) {
        std::cerr << "Usage: ./mud fileName" << std::endl;
        return 1;
    }

    Rooms *rooms = loadRooms(argv[1]); //This also checks for whether the file is openable.

    Player player;
    Inventory inventory;
    player.decisions(inventory, rooms);
    delete[] rooms;
    return 0;
}