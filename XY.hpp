/*
 * =====================================================================================
 *
 *       Filename:  Rooms.hpp
 *
 *    Description:  
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

#ifndef XY_HPP
#define XY_HPP

struct xy
{
    int x;
    int y;
    xy()
    {
        this->x = -1;
        this->y = -1;
    }
    xy(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

#endif


