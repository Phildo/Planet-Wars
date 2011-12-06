//
//  Unit.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Unit.h"
#include "Model.h"




Unit::Unit(void) {

}

Unit::Unit(int uType, int uLane, int uTeam) {
    type = uType;
    level = 1;
    lane = uLane;
    canAttack = true;
	team = uTeam;
	setPosition();
	isMoving = true;

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

void Unit::draw() {
	

	glPushMatrix();

	
	glTranslated(position[0], position[1], position[2]);

	//glRotatef( X, 1.0f, 0.0f, 0.0f);
	//glRotatef( Y, 0.0f, 1.0f, 0.0f);
	//glRotatef( Z, 0.0f, 0.0f, 1.0f);

	glLineWidth( 3.0 );
	
	//glEnable(GL_LIGHTING);

	glBegin( GL_LINE_LOOP );/// don't workglPointSize( 0.0 );
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();

	gluQuadricDrawStyle(quadric, GLU_FILL );
	
	//glColor3d(1.0,  0.0, 0.0);

	//DrawableGeometry::setColor(1.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0);
	Unit::checkType();	
	DrawableGeometry::setGLColor();

	
	gluSphere( quadric , 1 , 36 , 18 );

	gluDeleteQuadric(quadric);
	glEndList();

	//glDisable(GL_LIGHTING);

	glEnd();


	glPopMatrix();

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
		Unit::health = 1000;
		Unit::attackDamage = 100;
		Unit::range = 4;
		DrawableGeometry::setColor(1.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0);
		break;

	case 2:
		Unit::health = 1800;
		Unit::attackDamage = 50;
		Unit::range = 1;
		DrawableGeometry::setColor(0.0, 1.0, 0.0, 0.0, 0.5, 1.0, 1.0);
		break;

	case 3:
		Unit::health = 800;
		Unit::attackDamage = 180;
		Unit::range = 3;
		DrawableGeometry::setColor(0.0, 0.0, 1.0, 0.0, 0.5, 1.0, 1.0);
		break;

	case 4:
		Unit::health = 700;
		Unit::attackDamage = 80;
		Unit::range = 10;
		DrawableGeometry::setColor(1.0, 0.0, 1.0, 0.0, 0.5, 1.0, 1.0);
		break;


	}

}

bool Unit::isDead() {
	return health < 0;
}










