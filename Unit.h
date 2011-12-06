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

class Unit : public DrawableGeometry
{
public:

	double range;
	double position[3];
    int type;
    int level;
	int health;
	int attackDamage;
	int lane;
	bool canAttack;
	int team;
	bool isMoving;

	Unit(void); 
	Unit(int uType, int uLane, int uTeam);

	void takeDamage(int damage);
	void hasAttacked();
	double* getPosition();
	void update();
	void setMoving(bool moving);
	void setPosition();
	void checkType();
	bool isDead();

    static bool compiled;       //True iff displayList names a valid glDisplayList
    static GLuint displayList;  //Name of displaylist for object
    void compileDL();
    void draw();
    void drawAtPosition();


};

#endif