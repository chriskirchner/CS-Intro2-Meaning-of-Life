/*
 * =====================================================================================
 *
 *       Filename:  Map.hpp
 *
 *    Description:  class specification file for Mapping the Meaning of Life Game
 *
 *        Version:  1.0
 *        Created:  05/27/2015 10:47:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Kirchner (CK), kirchnch@onid.oregonstate.edu
 *   Organization:  OSU
 *
 * =====================================================================================
 */

#ifndef MAP_HPP
#define MAP_HPP

#include "XY.hpp"
#include "Things.hpp"
#include "Rooms.hpp"
#include <vector>

class Thing;
class Room;

class Map
{
    private:
        char **map;
        std::vector<Thing *> *things;
        std::vector<Room *> *rooms;
        xy dimensions;
    public:
        //passed by reference instead of pointer so vectors were not updating
        Map(int,int);
        ~Map();
        void addRooms(std::vector<Room *>*);
        void addThings(std::vector<Thing *>*);
        void buildMap();
        void clearMap();
        char buildWall(int);
        void setLocation(char,xy);
        char getCharacter(xy);
        bool isNearby(char,xy);
        void unlockRooms();
        bool isLocked(xy);
        xy getDimensions();
};

#endif
                                                                                         
