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
}

Fleet::~Fleet()
{
    delete this->flagship;
}