#include "room.h"

Room::Room() : dungeonRoom(3 , std::vector<char>(8, '.')){
    north = south = east = west = -1;
}

int Room::getExit(const Room &room, const char direction) {
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

void Room::setExit(Room &room, const char direction, const int roomIndex) {
    switch(direction)
    {
        case 'n':
            north = roomIndex;
            break;
        case 's':
            south = roomIndex;
            break;
        case 'e':
            east = roomIndex;
            break;
        case 'w':
            west = roomIndex;
            break;
    }
    return;
}