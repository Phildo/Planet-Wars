//
//  Fleet.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Fleet.h"
#include "Model.h"

Fleet::Fleet(Player * o)
{
    owner = o;
    this->flagship = new Flagship();
    numShips = 0;
}

Fleet::~Fleet()
{
    delete this->flagship;
}

void Fleet::addShip(Node * n)
{
    if(n->ship != Model::getSelf()->nullShip) return;
    shipArray.resize(shipArray.size()+1);
    shipArray[shipArray.size()-1] = new Ship();
    shipArray[shipArray.size()-1]->loc = n;
    numShips++;
}

void Fleet::refreshShips()
{
    for(int i = 0; i < numShips; i++)
        shipArray[i]->done = false;
}

void Fleet::draw()
{
    for(int i = 0; i < numShips; i++)
        shipArray[i]->drawAtPosition();
}