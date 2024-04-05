#include <iostream>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>
#include "room.h"
#include "player.h"
#include "bag.h"
// #include "enemies.h"

enum Directions { //Use these for moving in the vector. USE AS INTEGERS. MAYBE NOT USING THESE IF NO PRINTING CHARACTER AND MOVEMENT.
    Left = -1,
    Right = 1,
    Up = 1,
    Down = -1,
};

int getExit(const Room &room, const char direction) {
    switch(direction)
    {
        case 'n':
            return room.north;
        case 's':
            return room.south;
        case 'e':
            return room.east;
        case 'w':
            return room.west;
    }
    return 0; //Returns 0 to avoid warnings.
}

void setExit(Room &room, const char direction, const int roomIndex) {
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
    while (isspace(str.back())) {
        str.pop_back();
    }
    while (isspace(str.front())) {
        str.erase(str.begin());
    }
    return;
}

const Room *loadRooms(const std::string dungeonFilename) 
{
    std::ifstream fin(dungeonFilename);
    //Following if-statement checks for any file opening errors.
    if(!(fin.is_open()))
    {
        std::cerr << "Error: File did not open correctly" << std::endl;
        exit(1);
    }

    size_t tildeCount = 0; //# of tildes inside file. 3 for each room.
    std::string stringHolder; //Holds strings for counting # of tildes.
    while(getline(fin, stringHolder, '~')) tildeCount++; //Finds total of tildes inside file.
    
    //Calculates # of rooms. CHANGE DENOMINATOR TO HOWEVER MANY ARE NEEDED. I PUT 6, ONE PER READ IN (art counts as 2 because of enemy and room art).
    size_t roomCount = tildeCount / 6;

    Room *rooms = new Room[roomCount];

    //Following two lines jumps back to beginning of file.
    fin.clear();
    fin.seekg(0);

    //Reads in and stores the room's title, description, exits, enemy, and arts.
    //TODO: ADD READING IN THE ARTS AND ENEMY.
    for (size_t i = 0; i < roomCount; i++) {
        //Following four lines read and store the name and description then removes extra whitespaces.
        getline(fin, rooms[i].name, '~');
        stripWhitespace(rooms[i].name);
        getline(fin, rooms[i].description, '~');
        stripWhitespace(rooms[i].description);

        //Rest of code is for exits.
        std::string exits; //For reading in the exits.
        getline(fin, exits, '~');
        stripWhitespace(exits);
        std::istringstream sin(exits);
        char direction; //Direction of the exit.
        int room_index; //Room the exit leads to.
        while(sin >> direction >> room_index) setExit(rooms[i], direction, room_index); //Reads in the direction/index and sets the room exits.
        sin.clear(); //Clears istringstream for use again.
    }

    //dumpRooms(rooms, roomCount); //Uncomment for debugging.

    fin.close();
    return rooms;
}


int main() {
    // size_t sizeOfDungeon = 5;
    //const Room *rooms;
    Player player;
    Bag bag;
    player.decisions(bag);
    const Room *rooms;

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