/*
 * =====================================================================================
 *
 *       Filename:  Display.cpp
 *
 *    Description:  class implementation file for Displaying Meaning of Life Game
 *
 *        Version:  1.0
 *        Created:  05/26/2015 11:48:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Kirchner (CK), kirchnch@onid.oregonstate.edu
 *   Organization:  OSU
 *
 * =====================================================================================
 */

#include "Display.hpp"
#include <iostream>
using namespace std;

Display::Display(Player *player, Map *map)
{
    this->player = player; 
    this->map = map; 
}

void Display::refresh()
{
    showMap();
    showMenuBar();
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  showMap
 *  Description:  prints the contents of the Map
 *   Parameters:  none, contains Map pointer
 * =====================================================================================
 */

void Display::showMap()
{
    xy dimensions = map->getDimensions();
    for (int y=0; y<dimensions.y; y++){
        for (int x=0; x<dimensions.x; x++){
            xy location(x,y);
            cout << map->getCharacter(location);
        }
        cout << endl;
    }
}

void Display::showMenuBar()
{
    cout << "[R]estart | [C]ommands | [H]elp | [Q]uit " << endl;
}

void Display::showCommands()
{
    cout << "           ------------" << endl;
    cout << "           [w] UP" << endl;
    cout << "[a] LEFT               [d] RIGHT" << endl;
    cout << "           [s] DOWN" << endl;
    cout << endl;
}

void Display::showRoom()
{   
    Room *room = player->getRoom();
    cout << "Room of " << room->getName() << endl;
}

void Display::showPlayerProfile()
{
    cout << endl;
    showRoom();
    cout << "Questions Collected: " << player->getNumQuestions() << endl;
    cout << "Has Key: ";
    if (player->hasKey()){
        cout << "yes";
    }
    else{
        cout << "no";
    }
    cout << endl;
}

void Display::showHelp()
{
    cout << "                        ---------" << endl;
    cout << "Welcome to the Meaning of Life Game" << endl << endl
         << "...where you turn questions into a key to" << endl
         << "unlock the meaning of life.  Beware of" << endl
         << "the evil Answers (\"@\") that will steal away" << endl
         << "your questions." << endl << endl;
    cout << "HOW TO: " << endl;
    cout << "Walk through all the rooms to collect questions." << endl
         << "The second to last room will unlock all rooms that" << endl
         << "close behind you, except for the very last room" << endl
         << "To unlock the last room, you need to go to the first" << endl
         << "room and convert 6 questions to get a key (*)." << endl
         << "Pick up the key and use it to open up the door to" << endl
         << "the last room where you will find the meaning of" << endl
         << "life, blah.  Goodluck!" << endl << endl;
}

char Display::getOption()
{
    char c;
    system("stty raw");
    cin >> c; 
    system("stty cooked");
    system("clear");
    return c;
}
