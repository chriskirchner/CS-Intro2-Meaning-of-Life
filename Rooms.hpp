/*
 * =====================================================================================
 *
 *       Filename:  Rooms.hpp
 *
 *    Description:  class specification file of Rooms in Meaning of Life Game
 *
 *        Version:  1.0
 *        Created:  05/26/2015 11:27:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Kirchner (CK), kirchnch@onid.oregonstate.edu
 *   Organization:  OSU
 *
 * =====================================================================================
 */

#ifndef ROOMS_HPP
#define ROOMS_HPP

#include "XY.hpp"
#include "Things.hpp"
#include "Map.hpp"
#include <cstdlib>
#include <string>
#include <vector>

class Room;
class Thing;
class Map;

//Doors link Rooms with location
struct Doors
{
    Room *r1;
    xy d1;
    Room *r2;
    xy d2;
    Room *r3;
    xy d3;
    Room *r4;
    xy d4;
    Doors() {}
    Doors(Room *r1, xy d1, Room *r2 = NULL, xy d2 = xy(-1,-1),
            Room *r3 = NULL, xy d3 = xy(-1,-1),
            Room *r4 = NULL, xy d4 = xy(-1,-1))
    {
        this->r1 = r1;
        this->d1 = d1;
        this->r2 = r2;
        this->d2 = d2;
        this->r3 = r3;
        this->d3 = d3;
        this->r4 = r4;
        this->d4 = d4;
    }
};

class Room
{
    protected: 
        std::string name;
        xy dimensions;
        xy origin;
        Doors doors;
        Map *map;
        std::vector<Thing *> *things;
        bool locked;
    public:
        Room(std::string,Map*,std::vector<Thing *>*,xy,xy);
        std::string getName();
        xy getOrigin();
        xy getDimensions();
        virtual void enter() = 0;
        void leave();
        void addDoor(xy, Room*);
        bool isDoor(xy);
        bool isAtEntrance(xy);
        void setDoors(Room *r1 = NULL, xy d1 = xy(-1,-1), 
            Room *r2 = NULL, xy d2 = xy(-1,-1),
            Room *r3 = NULL, xy d3 = xy(-1,-1),
            Room *r4 = NULL, xy d4 = xy(-1,-1));
        Doors getDoors();
        bool isInRoom(xy location);
        Room *getNextRoom(xy location);
        bool isLocked();
        void lock();
        void unlock();
}; 

class RegularRoom : public Room
{
    public:
        RegularRoom(std::string n, Map *m, std::vector<Thing*> *t, xy o, xy d)
        : Room(n,m,t,o,d) 
        {
            locked = false;
        }
        void enter();
};

class StartRoom : public Room
{
    private:
       int numQuestions; 
       int questionLimit;
    public:
        StartRoom(std::string n, Map *m, std::vector<Thing*> *t, xy o, xy d)
        : Room(n,m,t,o,d) 
        {
            locked = false;
            numQuestions = 0;
            questionLimit = 6;
        }
        void enter();
};

class SafeRoom : public Room
{
    public:
        SafeRoom(std::string n, Map *m, std::vector<Thing*> *t, xy o, xy d)
        : Room(n,m,t,o,d) 
        {
            locked = false;
        }
        void enter();
};

class UnlockRoom: public Room
{
    public:
        UnlockRoom(std::string n, Map *m, std::vector<Thing*> *t, xy o, xy d)
        : Room(n,m,t,o,d) 
        {
            locked = false;
        }
        void enter();
};

class LastRoom: public Room
{
    public:
        LastRoom(std::string n, Map *m, std::vector<Thing*> *t, xy o, xy d)
        : Room(n,m,t,o,d) 
        {
            locked = true;
        }
        void enter();
};

#endif
