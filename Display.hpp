/*
 * =====================================================================================
 *
 *       Filename:  Display.hpp
 *
 *    Description:  class specification file for Displaying Meaning of Life Game 
 *                  
 *
 *        Version:  1.0
 *        Created:  05/07/2015 01:15:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Kirchner (CK), kirchnch@onid.oregonstate.edu
 *   Organization:  OSU
 *
 * =====================================================================================
 */

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <cstdlib>
#include "Map.hpp"
#include "Rooms.hpp"

class Display
{
    private:
        Map *map;
        Player *player;
    public:
        Display(Player*,Map*);
        void refresh();
        void showMap();
        void showMenuBar();
        void showCommands();
        void showHelp();
        void showRoom();
        void showPlayerProfile();
        char getOption();
};

#endif
