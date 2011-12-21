//
//  Unit.h
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_UNIT
#define H_UNIT

#include "Model.h"
#include "DrawableGeometry.h"
#include "Player.h"

class Unit : public DrawableGeometry
{
public:

    Unit(void); 
	Unit(int type, Player * o, bool attacker);
    void initThings();
    
    bool attacker;
    Player * owner;
    
    int pos;
    
    int type;
    int level;
    
    int health;
    int maxHealth;
    int damage;
    int speed;
	int range;
    int cooldown;

    void reset();
    void resetCooldown();
    void setType(int type);
    void setTypeColor(int type);
    bool attack(Unit * enemy);

    static bool compiled;       //True iff displayList names a valid glDisplayList
    static GLuint typeList;  //Name of displaylist for object
    static GLuint teamList;  //Name of displaylist for object
    static GLuint healthBar;
    void compileDL();
    void draw();
    void drawAtPosition();
};

#endif