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

/* colors! http://www.codebuilder.me/2014/01/color-terminal-text-in-c/ */
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

Display::Display(Player *player, Map *map)
{
    this->player = player; 
    this->map = map; 
	this->player_icon = player->getIcon();
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
            char c = map->getCharacter(location);
			if (c == player_icon){
				cout << RED << c;
			}
			else {
				cout << RESET << c;
			}
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
