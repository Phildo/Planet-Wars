//
//  Lane.h
//  PlanetWars
//
//  Created by Philip Dougherty on 12/5/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#ifndef LANE_H
#define LANE_H

#include "Model.h"
#include "DrawableGeometry.h"

class Lane: public DrawableGeometry
{
public:
    Lane(int shift);
    ~Lane();
    
    int shift;
    
    static bool compiled;       //True iff displayList names a valid glDisplayList
    static GLuint displayList;  //Name of displaylist for object
    void compileDL();
    void draw();
};

#endif