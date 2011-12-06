//
//  Unit.h
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_UNIT
#define H_UNIT

#include <GL\freeglut.h>
#include <GL\GL.h>
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
	void draw();
	void update();
	void setMoving(bool moving);
	void setPosition();
	void checkType();
	bool isDead();



};

#endif