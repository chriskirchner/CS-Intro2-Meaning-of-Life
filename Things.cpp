/*
 * =====================================================================================
 *
 *       Filename:  Things.cpp
 *
 *    Description:  class implementation file for Things in Meaning of Life Game
 *
 *        Version:  1.0
 *        Created:  05/27/2015 11:30:26 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Kirchner (CK), kirchnch@onid.oregonstate.edu
 *   Organization:  OSU
 *
 * =====================================================================================
 */

#include "Things.hpp"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  setLocation
 *  Description:  sets location of player with while entering new room, leaving old 
 *                room, and switching link
 *   Parameters:  location of player
 * =====================================================================================
 */

void Player::setLocation(xy location)
{  
    Room *nextRoom = room->getNextRoom(location);
    if (nextRoom){
        if (nextRoom->isLocked() && key){
            removeKey();
            nextRoom->unlock();
        }
        else if (!room->isInRoom(location) &&
            nextRoom->isInRoom(location)){
            room->leave();
            nextRoom->enter();
            room = nextRoom;
            nextRoom = NULL;
        }
    }
    this->location = location;
}

void Player::removeQuestion()
{
    if (numQuestions){
        numQuestions--;
    }
}

bool Player::hasKey()
{
    return key;
}

void Player::addKey()
{
    key = true;
}

void Player::removeKey()
{
    key = false;
}

void Question::setLocation(xy location)
{
    this->location = location;
}

void Player::addQuestion()
{
    if (numQuestions < questionLimit){
        numQuestions++;
    }
}

int Player::getNumQuestions()
{
    return numQuestions;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Answer::getMove
 *  Description:  gets move Question is trying to make when instantiated (only moves
 *                once from nonexistence)
 *   Parameters:  meaningless character; should overload
 * =====================================================================================
 */

xy Question::getMove(char c)
{
    xy move;
    int x = rand() % (room->getDimensions().x - 1) + 1;
    int y = rand() % (room->getDimensions().y - 1) + 1;
    move.x = x + room->getOrigin().x;
    move.y = y + room->getOrigin().y;
    return move;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Answer::getMove
 *  Description:  gets random move Answer is trying to make 
 *   Parameters:  meaningless character; should overload
 * =====================================================================================
 */

xy Answer::getMove(char c)
{
    xy move;
    if (location.x == -1 && location.y == -1){
        int x = rand() % (room->getDimensions().x - 1) + 1;
        int y = rand() % (room->getDimensions().y - 1) + 1;
        move.x = x + room->getOrigin().x;
        move.y = y + room->getOrigin().y;
    }
    else {
        //also moves diagonal
        move.x = location.x;
        move.y = location.y;
        move.x += rand() % 3 - 1;
        move.y += rand() % 3 - 1;
    }
    return move;
}

xy Thing::getLocation()
{
    return location;
}

char Thing::getIcon()
{
    return icon;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Player::getMove
 *  Description:  gets move player is tyring to make based on character indication
 *                of direction
 *   Parameters:  direction character
 * =====================================================================================
 */

xy Player::getMove(char direction)
{
    xy move = location;
    if (direction == 'a'){
        move.x--;
    }
    else if (direction == 's'){
        move.y++;
    }
    else if (direction == 'w'){
        move.y--;
    }
    else if (direction == 'd'){
        move.x++;
    }
    return move;
}

Room *Player::getRoom()
{
    return room;
}
