//
//  Fleet.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Fleet.h"
#include "Model.h"

Fleet::Fleet()
{
    this->flagship = new Flagship();
    numShips = 0;
}

Fleet::~Fleet()
{
    delete this->flagship;
}

void Fleet::addShip()
{
    shipArray.resize(shipArray.size()+1);
    shipArray[shipArray.size()-1] = new Ship();
}

void Fleet::refreshShips()
{
    for(int i = 0; i < numShips; i++)
        shipArray[i]->done = false;
}