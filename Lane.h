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

using namespace std;

class Lane: public DrawableGeometry
{
public:
    Lane();
    ~Lane();

    Unit ** attackerUnits;
    int attackerIndex;
    Unit ** defenderUnits;
    int defenderIndex;
    int furthestAttacker;
    int furthestDefender;
    
    bool aSelected;
    bool dSelected;
    
    void removeUnitFromArray(Unit * u, bool attacker);
    void setSelected(bool selected, bool attacker);
    void deployUnit(Unit * unit, bool attacker);
    void advanceUnit(Unit * unit, bool attacker);
    void actUnit(Unit * unit, bool attacker);
    Unit* findFurthestUnit(bool attacker);
    void tick();
    
    static bool compiled;       //True iff displayList names a valid glDisplayList
    static GLuint unselectedList;  //Name of displaylist for object
    static GLuint selectedList;
    GLuint displayList;
    void compileDL();
    void draw();
};

#endif