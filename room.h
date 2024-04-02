#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

class Room {
    public:
        Room();
        std::string name;
        std::string description;
        std::vector<std::vector<char> > dungeonRoom; //Interior is 3x8, but the walls will make it a 5 x 10. Used to print out the room once player enters.
    private:
        int getExit(const Room &room, const char direction);
        void setExit(Room &room, const char direction, const int roomIndex);
        //Following four variables will hold which room the direction leads to.
        int north; 
        int south;
        int east;
        int west;
};

#endif