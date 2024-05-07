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
    //Trim trailing whitespace.
    while (!str.empty() && isspace(str.back())) str.pop_back();

    //Trim leading whitespace.
    while (!str.empty() && isspace(str.front())) str.erase(str.begin());

    return;
}

Rooms *loadRooms(const std::string dungeonFilename) 
{
    std::ifstream fin(dungeonFilename);
    //Following if-statement checks for any file opening errors.
    if(!(fin.is_open())) {
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

    //Reads in and stores the room's title, description, exits, enemy data, and arts.
    for (size_t i = 0; i < roomCount; i++) {
        //Following variables are for reading in information from the file.
        char direction; //Direction of the exit.
        int HP, ATK;
        int room_index; //Rooms the exit leads to.
        std::string exits, enemyName, stats, ASCIIEnemyArt, dialogue;

        //Following four lines read and store the name and description then removes extra whitespaces.
        getline(fin, rooms[i].name, '~');
        stripWhitespace(rooms[i].name);
        getline(fin, rooms[i].description, '~');
        stripWhitespace(rooms[i].description);

        //Following eight lines is for exits and enemy data/arts.
        getline(fin, exits, '~');
        stripWhitespace(exits);
        std::istringstream sin(exits);
        while(sin >> direction >> room_index) setExit(rooms[i], direction, room_index); //Reads in the direction/index and sets the room exits.
        sin.clear(); //Clears istringstream for use in next loop.
        
        //Rest of the code reads in room art and enemy info. Read in EVERYTHING about the enemy first. If enemyName ! empty, create enemy with all read in values.
        getline(fin, rooms[i].ASCIIRoomArt, '~');
        getline(fin, enemyName, '~');
        stripWhitespace(enemyName);
        getline(fin, stats, '~');
        stripWhitespace(stats);
        sin.str(stats);
        sin >> HP >> ATK;
        sin.clear();
        getline(fin, ASCIIEnemyArt, '~');
        getline(fin, dialogue, '~');
        if (!enemyName.empty()) rooms[i].createEnemy(enemyName, dialogue, ASCIIEnemyArt, HP, ATK);
    }

    fin.close();
    return rooms;
}


int main(int argc, char *argv[]) {
    if(2 != argc) {
        std::cerr << "Usage: ./mud fileName" << std::endl;
        return 1;
    }

    Rooms *rooms = loadRooms(argv[1]); //Returns a pointer to an array of Rooms.

    Player player;
    Inventory inventory;
    player.decisions(inventory, rooms); //Starts the actual game.
    delete[] rooms; //Clears up the memory used.
    return 0;
}