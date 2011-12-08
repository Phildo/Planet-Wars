//
//  Fleet.h
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_FLEET
#define H_FLEET

class Player;
class Ship;
class Flagship;

#include <vector.h>
#include "Player.h"
#include "Flagship.h"
#include "Ship.h"

class Fleet
{
public:
    Flagship * flagship;
    vector<Ship *> shipArray;
    int numShips;
    
    Fleet();
    ~Fleet();
    
    void addShip();
    void refreshShips();
};
#endif