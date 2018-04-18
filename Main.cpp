/*
 * =====================================================================================
 *
 *       Filename:  Main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/27/2015 12:17:45 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Kirchner (CK), kirchnch@onid.oregonstate.edu
 *   Organization:  OSU
 *
 * =====================================================================================
 */

#include "Rooms.hpp"
#include "Display.hpp"
#include "Things.hpp"
#include "XY.hpp"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

void buildRooms(Map *map, vector<Room *> *rooms, vector<Thing *> *things)
{
    int roomWidth = 28;
    int roomHeight = 10;

    StartRoom *r1 = new StartRoom("Genesis", map, things, 
        xy(0,0), xy(roomWidth/4,roomHeight));
    RegularRoom *r2 = new RegularRoom("Sati", map, things,
        xy(roomWidth/4,0), xy(3*roomWidth/4,roomHeight));
    RegularRoom *r3 = new RegularRoom("Dhamma Vicaya", map, things,
        xy(roomWidth,0), xy(roomWidth,roomHeight));
    RegularRoom *r4 = new RegularRoom("Viriya", map, things,
        xy(2*roomWidth,0), xy(roomWidth,roomHeight));
    SafeRoom*r5 = new SafeRoom("Emptiness", map, things,
        xy(2*roomWidth,roomHeight), xy(roomWidth,roomHeight));
    RegularRoom *r6 = new RegularRoom("Piti", map, things,
        xy(2*roomWidth,2*roomHeight), xy(roomWidth,roomHeight));
    RegularRoom *r7 = new RegularRoom("Passaddhi", map, things,
        xy(roomWidth,2*roomHeight), xy(roomWidth,roomHeight));
    RegularRoom *r8 = new RegularRoom("Samadhi",  map, things,
        xy(0,2*roomHeight), xy(roomWidth,roomHeight));
    UnlockRoom*r9 = new UnlockRoom("Upekkha", map, things,
        xy(0,roomHeight), xy(roomWidth,roomHeight));
    LastRoom *r10 = new LastRoom("IS", map, things,
        xy(roomWidth,roomHeight), xy(roomWidth,roomHeight));

    r1->setDoors(r2, xy(roomWidth/4,roomHeight/2));
    r2->setDoors(r1, xy(0,roomHeight/2), r3, xy(3*roomWidth/4, roomHeight/2));
    r3->setDoors(r2, xy(0,roomHeight/2), r4, xy(roomWidth, roomHeight/2));
    r4->setDoors(r3, xy(0,roomHeight/2), r5, xy(roomWidth/2, roomHeight));
    r5->setDoors(r4, xy(roomWidth/2,0), r6, xy(roomWidth/2, roomHeight));
    r6->setDoors(r5, xy(roomWidth/2,0), r7, xy(0, roomHeight/2));
    r7->setDoors(r6, xy(roomWidth,roomHeight/2), r8, xy(0, roomHeight/2));
    r8->setDoors(r7, xy(roomWidth,roomHeight/2), r9, xy(roomWidth/2,0));
    r9->setDoors(r8, xy(roomWidth/2,roomHeight), r10, xy(roomWidth,roomHeight/2));
    r10->setDoors(r9, xy(0,roomHeight/2));
    
    rooms->push_back(r1);
    rooms->push_back(r2);
    rooms->push_back(r3);
    rooms->push_back(r4);
    rooms->push_back(r5);
    rooms->push_back(r6);
    rooms->push_back(r7);
    rooms->push_back(r8);
    rooms->push_back(r9);
    rooms->push_back(r10);
}

void moveThings(Map *map, vector<Thing *> *things)
{
    for (unsigned int i=1; i<things->size(); i++){
        Thing *thing = things->at(i);
        if (thing->getIcon() == '@'){
            bool validMove = false;
            int tries = 0;
            do{
                xy move = thing->getMove('0');
                char space = map->getCharacter(move);
                if (space == ' '){
                    thing->setLocation(move);
                    //don't build map here, things can float over each other
                    validMove = true;
                }
                else{
                    tries++;
                }
            }while(!validMove && tries != 4);
            
            xy location = thing->getLocation();
            if (map->isNearby('0', location)){
                Player *player = static_cast<Player *>(things->at(0));
                player->removeQuestion();
            }
        }
    }
}

void startGame(Player **player, Map **map, vector<Room *> **rooms,
                vector<Thing *> **things, Display **display){
    //clean up memory later
    *map = new Map(101,31);
    *rooms = new vector<Room *>; 
    *things = new vector<Thing *>;
    buildRooms(*map, *rooms, *things);

    *player = new Player((*rooms)->at(0),xy(1,1));
    *display = new Display(*player,*map);

    (*map)->addRooms(*rooms);
    (*things)->push_back(*player);
    (*map)->addThings(*things);
    (*map)->buildMap();
}

void removeThing(vector<Thing *> *things, xy location){
    for (unsigned int i=1; i<things->size(); i++){
        Thing *thing = things->at(i);
        if (thing->getLocation().x == location.x &&
            thing->getLocation().y == location.y){
            things->erase(things->begin() + i);
        }
    }
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{
    srand(time(NULL));

    Map *map = NULL;
    Player *player = NULL;
    vector<Thing *> *things = NULL;
    vector<Room *> *rooms = NULL;
    Display *display = NULL;

    char userOption;
    cout << "Start the game (y/N)?";
    cin >> userOption;
    if (userOption != 'y' && userOption != 'Y'){
        exit(0);
    }
    
    startGame(&player, &map, &rooms, &things, &display);
    int gameTime = 120;

    time_t t0 = time(0);
    time_t t1;
    int duration;

    system("clear");
    display->refresh();
    cout << "Time Left [s]: " << gameTime;

    bool quit = false;
    bool gotQuestion = false;
    bool win = false;
    bool lose = false;
    do {
        userOption = display->getOption();

        t1 = time(0);
        duration = difftime (t1, t0);
        if (duration > gameTime){
            lose = true;
        }
        if (things->size() == 1 && gotQuestion){
            win = true;
        }

        if (userOption == 'r' || userOption == 'R'){
            startGame(&player, &map, &rooms, &things, &display);
            t0 = time(0);
            win = false;
            lose = false;
            gotQuestion = false;
            display->refresh();
        }
        else if ((userOption == 'a' || userOption == 's' || 
            userOption == 'w' || userOption == 'd') && !win && !lose){
            xy move = player->getMove(userOption);
            char space = map->getCharacter(move);
            if (space != '-' && space != '|'){
                if (space == ' '){
                    player->setLocation(move);
                    map->buildMap();
                }
                else if (space == '?'){
                    player->setLocation(move);
                    player->addQuestion();
                    removeThing(things, move);
                    map->buildMap();
                    gotQuestion = true;
                }
                else if (space == '*'){
                    player->setLocation(move);
                    player->addKey();
                    removeThing(things, move);
                    map->buildMap();
                }
            }
            moveThings(map, things);
            display->refresh();
            display->showPlayerProfile();
        }
        else if (userOption == 'h' || userOption == 'H'){
            display->refresh();
            display->showHelp();
        }
        else if (userOption == 'c' || userOption == 'C'){
            display->refresh();
            display->showCommands();
        }
        else if (userOption == 'q' || userOption == 'Q'){
            quit = true;
        }

        cout << "Time Left [s]: " << gameTime - duration << endl;

        if (win){
            cout << "SUCCESS! You have found the meaning of life" << endl;
            cout << "Unfortunately, you are in a locked room" << endl;
            display->refresh();
        }
        else if (lose){
            display->refresh();
            cout << "GAME OVER!  You did not find the meaning of life" << endl;
            cout << "Or is the meaning just to find one? " << endl;
        }

        
    }while(!quit);


    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
