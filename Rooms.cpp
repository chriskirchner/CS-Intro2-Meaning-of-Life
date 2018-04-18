/*
 * =====================================================================================
 *
 *       Filename:  Rooms.cpp
 *
 *    Description:  class implementation file of Room behaviors in Meaning of Life Game
 *
 *        Version:  1.0
 *        Created:  05/27/2015 12:13:46 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Kirchner (CK), kirchnch@onid.oregonstate.edu
 *   Organization:  OSU
 *
 * =====================================================================================
 */

#include "Rooms.hpp"

//brings the Room to Life
Room::Room(std::string name, Map *map, std::vector<Thing *> *things,
        xy origin, xy dimensions)
{
    this->name = name;
    this->map = map;
    this->things = things;
    this->origin = origin;
    this->dimensions = dimensions;
}

std::string Room::getName()
{
    return name;
}

bool Room::isDoor(xy location)
{
    if ((doors.d1.x + origin.x == location.x && doors.d1.y + origin.y == location.y)
     || (doors.d2.x + origin.x == location.x && doors.d2.y + origin.y == location.y) 
     || (doors.d3.x + origin.x == location.x && doors.d3.y + origin.y == location.y)
     || (doors.d4.x + origin.x == location.x && doors.d4.y + origin.y == location.y)){

        return true;
    }
    else{
        return false;
    }
}

xy Room::getOrigin()
{
    return origin;
}

xy Room::getDimensions()
{
    return dimensions;
}

//bring the Doors to Life
void Room::setDoors(Room *r1, xy d1, Room *r2, xy d2, 
                    Room *r3, xy d3, Room *r4, xy d4)
{
    doors = Doors(r1, d1, r2, d2, r3, d3, r4, d4);
}

Doors Room::getDoors(){
    return doors;
}

//is the location in this room?
bool Room::isInRoom(xy location){
    if (location.x <= (origin.x + dimensions.x) &&
        location.y <= (origin.y + dimensions.y) &&
        location.x >= (origin.x) &&
        location.y >= (origin.y)){
        return true;
    }
    else{
        return false;
    }
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getNextRoom
 *  Description:  returns the next room behind the door the player is located
 *   Parameters:  location of player
 * =====================================================================================
 */

Room *Room::getNextRoom(xy location){
    Room *nextRoom = NULL; 
    xy tmp;
    for (int i=-1; i<2; i++){
        tmp.x = location.x + i;
        tmp.y = location.y;
        //returns the room pointer paralleled with location 
        //check all directions since direction was not tied to Door
        if (tmp.x == doors.d1.x + origin.x 
            && tmp.y == doors.d1.y + origin.y){
            nextRoom = doors.r1;
        }
        else if (tmp.x == doors.d2.x + origin.x
            && tmp.y == doors.d2.y + origin.y){
            nextRoom = doors.r2;
        }
        else if (tmp.x == doors.d3.x + origin.x
            && tmp.y == doors.d3.y + origin.y){
            nextRoom = doors.r3;
        }
        else if (tmp.x == doors.d4.x + origin.x
            && tmp.y == doors.d4.y + origin.y){
            nextRoom = doors.r4;
        }

    }
    for (int i=-1; i<2; i++){
        tmp.x = location.x;
        tmp.y = location.y + i;
        if (tmp.x == doors.d1.x + origin.x 
            && tmp.y == doors.d1.y + origin.y){
            nextRoom = doors.r1;
        }
        else if (tmp.x == doors.d2.x + origin.x
            && tmp.y == doors.d2.y + origin.y){
            nextRoom = doors.r2;
        }
        else if (tmp.x == doors.d3.x + origin.x
            && tmp.y == doors.d3.y + origin.y){
            nextRoom = doors.r3;
        }
        else if (tmp.x == doors.d4.x + origin.x
            && tmp.y == doors.d4.y + origin.y){
            nextRoom = doors.r4;
        }
    }
    return nextRoom;
}

void Room::leave()
{
    locked = true;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  RegularRoom::enter
 *  Description:  creates Question and Answer upon entry
 *   Parameters:  none
 * =====================================================================================
 */
void RegularRoom::enter()
{
    //create Question and add to Things
    Question *q = new Question(this);
    bool validMove = false;
    do{
        xy move = q->getMove('0');
        if (map->getCharacter(move) == ' '){
            q->setLocation(move);
            validMove = true;
        }
    }while(!validMove);
    things->push_back(q);

    //create Answer and add to Things
    validMove = false;
    Answer *a = new Answer(this);
    do{
        xy move = a->getMove('0');
        if (map->getCharacter(move) == ' '){
            a->setLocation(move);
            validMove = true;
        }
    }while(!validMove);
    things->push_back(a);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  StartRoom::enter
 *  Description:  converts players Questions to a Key
 *   Parameters:  none
 * =====================================================================================
 */

void StartRoom::enter()
{
    Player *player = static_cast<Player *>(things->at(0));
    while (player->getNumQuestions() && numQuestions < questionLimit){
        player->removeQuestion();
        numQuestions++;
    }
    if (numQuestions == questionLimit){
        bool validMove = false;
        Key *k = new Key(this);
        do{
            xy move = k->getMove('0');
            if (map->getCharacter(move) == ' '){
                k->setLocation(move);
                validMove = true;
            }
        }while(!validMove);
        things->push_back(k);
    }
    map->unlockRooms();
}

//unlock all rooms except the first
void UnlockRoom::enter()
{
    map->unlockRooms();
}

//does nothing!
void SafeRoom::enter(){
    return;
}

//removes everything except player
void LastRoom::enter()
{
    int size = things->size();
    things->erase(things->begin() + 1, things->begin()+size);
}

bool Room::isLocked()
{
   return locked; 
}

void Room::unlock()
{
    locked = false;
}

void Room::lock()
{
    locked = true;
}
