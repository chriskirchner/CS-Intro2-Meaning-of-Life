/*
 * =====================================================================================
 *
 *       Filename:  Things.hpp
 *
 *    Description:  class specification file for Things in Meaning of Life Game
 *
 *        Version:  1.0
 *        Created:  05/27/2015 12:58:00 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Kirchner (CK), kirchnch@onid.oregonstate.edu
 *   Organization:  OSU
 *
 * =====================================================================================
 */

#ifndef THINGS_HPP
#define THINGS_HPP

#include "XY.hpp"
#include "Rooms.hpp"

class Room;

class Thing
{
    protected:
        char icon;
        xy location; 
        Room *room;
    public:
        Thing(Room *r, xy l = xy(-1,-1)) : location(l), room(r) {};
        virtual void setLocation(xy) = 0;
        virtual xy getMove(char) = 0;
        xy getLocation();
        char getIcon();
};

class Player : public Thing
{
    private:
       int numQuestions;
       int questionLimit;
       bool key;
       bool atEntrance;
    public:
        Player(Room *r, xy l) : Thing(r,l) 
        {
            icon = '0';
            questionLimit = 7;
            numQuestions = 0;
            key = false;
            atEntrance = false;
        }
        Room *getRoom();
        void setLocation(xy);
        xy getMove(char);
        void addQuestion();
        void removeQuestion();
        int getNumQuestions();
        bool hasKey();
        void addKey();
        void removeKey();
};

class Question : public Thing
{
    public:
        Question(Room *r) : Thing(r) 
        {
            icon = '?';
        }
        void setLocation(xy);
        xy getMove(char);
};

class Answer : public Question
{
    public:
        Answer(Room *r) : Question(r)
        {
            icon = '@';
        }
        xy getMove(char);
};

class Key : public Question
{
    public:
        Key(Room *r) : Question(r)
        {
            icon = '*';
        }
};

#endif


