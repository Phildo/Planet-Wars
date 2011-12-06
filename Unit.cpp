//
//  Unit.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Unit.h"
#include "Model.h"

bool Unit::compiled = false;
GLuint Unit::displayList;

Unit::Unit(void) {
    if(!Unit::compiled) Unit::compileDL();
}

Unit::Unit(int uType, int uLane, int uTeam) {
    type = uType;
    level = 1;
    lane = uLane;
    canAttack = true;
	team = uTeam;
    isMoving = true;
	setPosition();
    checkType();
    if(!Unit::compiled) Unit::compileDL();
}

void Unit::takeDamage(int damage) {

	health = health - damage;

}

void Unit::hasAttacked() {
	isMoving = false;
	canAttack = false;
}

double* Unit::getPosition() {
	return Unit::position;
}

void Unit::setMoving(bool moving) {
	isMoving = moving;
}

void Unit::update() {

	if(isMoving && team == 0) {
		Unit::position[2] += .1;
	}

	if(isMoving && team == 1) {
		Unit::position[2] -= .1;
	}
}

void Unit::setPosition() {


	if(team == 0) {
		switch(lane) {

		case 1: 
			position[0] = 2.0;
			position[1] = 0.0;
			position[2] = 0.0;
			break;

		case 2: 
			position[0] = 6.0;
			position[1] = 0.0;
			position[2] = 0.0;
			break;

		case 3: 
			position[0] = 10.0;
			position[1] = 0.0;
			position[2] = 0.0;
			break;

		case 4: 
			position[0] = 14.0;
			position[1] = 0.0;
			position[2] = 0.0;
			break;

		case 5: 
			position[0] = 18.0;
			position[1] = 0.0;
			position[2] = 0.0;
			break;

		default:
			position[0] = 0.0;
			position[1] = 0.0;
			position[2] = 0.0;
			break;
		}
	}

	if(team == 1) {
		switch(lane) {

		case 1: 
			position[0] = 2.0;
			position[1] = 0.0;
			position[2] = 50.0;
			break;

		case 2: 
			position[0] = 6.0;
			position[1] = 0.0;
			position[2] = 50.0;
			break;

		case 3: 
			position[0] = 10.0;
			position[1] = 0.0;
			position[2] = 50.0;
			break;

		case 4: 
			position[0] = 14.0;
			position[1] = 0.0;
			position[2] = 50.0;
			break;

		case 5: 
			position[0] = 18.0;
			position[1] = 0.0;
			position[2] = 50.0;
			break;

		default:
			position[0] = 0.0;
			position[1] = 0.0;
			position[2] = 50.0;
			break;
		}
	}
	

}

void Unit::checkType() {
	
	switch(type) {

	case 1:
		health = 1000;
		attackDamage = 100;
		range = 4;
		setColor(1.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0);
		break;

	case 2:
		health = 1800;
		attackDamage = 50;
		range = 1;
		setColor(0.0, 1.0, 0.0, 0.0, 0.5, 1.0, 1.0);
		break;

	case 3:
		health = 800;
		attackDamage = 180;
		range = 3;
		setColor(0.0, 0.0, 1.0, 0.0, 0.5, 1.0, 1.0);
		break;

	case 4:
		health = 700;
		attackDamage = 80;
		range = 10;
		DrawableGeometry::setColor(1.0, 0.0, 1.0, 0.0, 0.5, 1.0, 1.0);
		break;
	}
}

bool Unit::isDead() {
	return health < 0;
}

void Unit::compileDL()
{
    if(Unit::compiled) return;
    Unit::displayList = glGenLists(1);
    glNewList(Unit::displayList, GL_COMPILE);
    
	gluSphere(gluNewQuadric(), 1, 36, 18);
    
    glEndList();
    Unit::compiled = true;
}

void Unit::draw()
{
    if(!Unit::compiled) return;
    setGLColor();
    glCallList(Unit::displayList);
}

void Unit::drawAtPosition()
{
    glPushMatrix();
	glTranslated(position[0], position[1], position[2]);
    draw();
    glPopMatrix();
}









