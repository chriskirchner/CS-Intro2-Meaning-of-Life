/*
 * =====================================================================================
 *
 *       Filename:  Map.cpp
 *
 *    Description:  class implementation file for Mapping Meaning of Life Game
 *
 *        Version:  1.0
 *        Created:  05/27/2015 11:08:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Kirchner (CK), kirchnch@onid.oregonstate.edu
 *   Organization:  OSU
 *
 * =====================================================================================
 */

#include "Map.hpp"

//instantiate Map with dimensions
Map::Map(int width, int height)
{
    dimensions.x = width;
    dimensions.y = height;
    this->rooms = rooms;
    this->things = things;
    map = new char*[width];

    for (int i=0; i<width; i++){
        map[i] = new char[height];
    }

    for (int y=0; y<height; y++){
        for (int x=0; x<width; x++){
            map[x][y] = ' ';
        }
    }
}

Map::~Map()
{
    for (int i=0; i<dimensions.x; i++){
        delete [] map[i];
    }
    delete [] map;
}


//add rooms to Map (self-explanatory?)
void Map::addRooms(std::vector<Room *> *rooms)
{
    this->rooms = rooms;
}

//add things to map
void Map::addThings(std::vector<Thing* > *things)
{
    this->things = things;
}

//clears map if player outside of room
//(not needed if player is inside rooms only)
void Map::clearMap()
{
    for (int y=0; y<dimensions.y; y++){
        for (int x=0; x<dimensions.x; x++){
            map[x][y] = ' ';
        }
    }
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  buildMap
 *  Description:  builds/updates map based on Room events and interaction with Things
 *   Parameters:  none; pointer to Rooms and Things
 * =====================================================================================
 */

void Map::buildMap()
{
    clearMap();
    int numRooms = rooms->size();
    for (int i=0; i<numRooms; i++){

        //get room box
        Room *room = rooms->at(i);
        int x0 = room->getOrigin().x;
        int y0 = room->getOrigin().y;
        int width = room->getDimensions().x;
        int height = room->getDimensions().y;

        //print walls (|,-), locked doors (#), and spaces
        for (int y=y0; y<=y0+height; y++){
           for (int x=x0; x<=x0+width; x++){
               if (x == x0 || x == x0+width){
                   if (!room->isDoor(xy(x,y))){
                       map[x][y] = '|';
                   }
                   else if (room->isDoor(xy(x,y)) && 
                            isLocked(xy(x,y))){
                       map[x][y] = '#';
                   }
                   else {
                       map[x][y] = ' ';
                   }
               }
               else if (y == y0 || y == y0+height){ 
                   if (!room->isDoor(xy(x,y))){
                       map[x][y] = '-';
                   }
                   else if (room->isDoor(xy(x,y)) && 
                            isLocked(xy(x,y))){
                       map[x][y] = '#';
                   }
                   else {
                       map[x][y] = ' ';
                   }
               }
           }
        }
    }
    
    //print things
    int numThings = things->size();
    for (int i=0; i<numThings; i++){
        
        Thing *thing = things->at(i);
        int xT = thing->getLocation().x;
        int yT = thing->getLocation().y;
        
        for (int y=0; y<dimensions.y; y++){
           for (int x=0; x<dimensions.x; x++){
               if (x == xT && y == yT){
                   map[x][y] = thing->getIcon();
               }
           }
        }
    }
}


char Map::getCharacter(xy location)
{
    int x = location.x;
    int y = location.y;
    return map[x][y];
}

xy Map::getDimensions()
{
    return dimensions;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  isNearby
 *  Description:  tests whether the "icon" (character/Thing) is nearby, 
 *                one space over from location 
 *   Parameters:  character icon and location
 * =====================================================================================
 */

bool Map::isNearby(char icon, xy location)
{
    int x;
    int y;
    for (int i=-1; i<2; i++){
        for (int j=-1; j<2; j++){
            x = location.x + i;
            y = location.y + j;
            if (map[x][y] == icon){
                return true;
            }
        }
    }
    return false;
}

//unlock all room except the last
void Map::unlockRooms()
{
    int size = rooms->size();
    for (int i=0; i<size-1; i++){
        Room *room = rooms->at(i);
        room->unlock();
    }
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  isLocked
 *  Description:  tests whether the Door belonging to two Rooms is locked by at
 *                least one Room
 *   Parameters:  location (of door)
 * =====================================================================================
 */

bool Map::isLocked(xy location)
{
    int size = rooms->size();
    for (int i=0; i<size; i++){
        Room *room = rooms->at(i);
        if (room->isDoor(location) && room->isLocked()){
            return true;
        }
    }
    return false;
}
