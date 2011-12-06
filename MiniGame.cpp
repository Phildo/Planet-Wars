#include "MiniGame.h"
#include <math.h>

#include <iostream>


MiniGame::MiniGame(void)
{

	//addUnit(1, 1, 0);
	//addUnit(2,2,0);
	//addUnit(3, 3, 0);
	//addUnit(4,4,0);
	laneSelect = 5;
	teamSelect = 0;


}

void MiniGame::checkAttacks() {


	for(int i = 0; i < MiniGame::numUnits; i++) {
		Unit *unit1 = MiniGame::units[i];

		if(unit1->canAttack) {

			for(int j = 0; j < MiniGame::numUnits; i++) {
			Unit *unit2 = MiniGame::units[j];

			if( unit1->lane == unit2->lane && distance(unit1, unit2) < unit1->range && unit1->team != unit2->team ) {
					attackUnit(unit1, unit2);
				}
			}
		}
	}
}


void MiniGame::attackUnit(Unit *attacker, Unit *attackee) {

	attackee->takeDamage(attacker->attackDamage);
	attacker->hasAttacked();

}


double MiniGame::distance(Unit *unit1, Unit *unit2) {

	double* pos1 = unit1->getPosition();
	double* pos2 = unit2->getPosition();

	return sqrt( pow(pos1[0] - pos2[0], 2.0) + pow(pos1[1] - pos2[1], 2.0) + pow(pos1[2] - pos2[2], 2.0) );

}


void MiniGame::addUnit(int uType, int uLane, int uTeam) {

	Unit *newUnit = new Unit(uType, uLane, uTeam);
	MiniGame::units.push_back(newUnit);
	numUnits++;
}


//only remove units at the end of an update for iteration purposes
void MiniGame::removeUnit(int index) {

	MiniGame::units.erase(units.begin() + index);
	numUnits--;

}


void MiniGame::update() {

	//int index = 0;

	for(int i = 0; i < units.size(); i++) {

		units[i]->update();
	}

	//for(std::vector<Unit*>::iterator it = units.begin(); it != units.end(); ++it, index++) {
	//	if(units[index]->isDead()) {
	//		removeUnit(index);
	//	}
	//	
	//}



}


void MiniGame::drawGame() {

	glPushMatrix();
	
	for(int i = 0; i < units.size(); i++) {

		units[i]->draw();

	}

	
	

	//lane 1
	glPushMatrix();

	if(laneSelect == 1) {

		DrawableGeometry::setColor(0.1, 0.2, 0.8, 0.0, 0.5, 1.0, 1.0);
		setGLColor();

	}
	else {
		DrawableGeometry::setColor(0.9, 0.5, 0.3, 0.0, 0.5, 1.0, 1.0);
		setGLColor();
	}


	glBegin(GL_QUADS);	
    
    glVertex3d(0, -1, 0);
	glVertex3d(4, -1, 0);
	glVertex3d(4, -1, 50);
	glVertex3d(0, -1, 50);

	glEnd();

	glPopMatrix();


	//lane 2
	glPushMatrix();

	if(laneSelect == 2) {

		DrawableGeometry::setColor(0.1, 0.2, 0.8, 0.0, 0.5, 1.0, 1.0);
		setGLColor();

	}
	else {
		DrawableGeometry::setColor(0.9, 0.5, 0.3, 0.0, 0.5, 1.0, 1.0);
		setGLColor();
	}

	glBegin(GL_QUADS);
    
    glVertex3d(4, -1, 0);
	glVertex3d(8, -1, 0);
	glVertex3d(8, -1, 50);
	glVertex3d(4, -1, 50);

	glEnd();
	
	glPopMatrix();

	

	//lane 3
	glPushMatrix();

	if(laneSelect == 3) {
		DrawableGeometry::setColor(0.1, 0.2, 0.8, 0.0, 0.5, 1.0, 1.0);
		setGLColor();
	}
	else {
		DrawableGeometry::setColor(0.9, 0.5, 0.3, 0.0, 0.5, 1.0, 1.0);
		setGLColor();
	}



	glBegin(GL_QUADS);
    
    glVertex3d(8, -1, 0);
	glVertex3d(12, -1, 0);
	glVertex3d(12, -1, 50);
	glVertex3d(8, -1, 50);

	glEnd();
	
	glPopMatrix();



	//lane 4
	glPushMatrix();

	if(laneSelect == 4) {
		DrawableGeometry::setColor(0.1, 0.2, 0.8, 0.0, 0.5, 1.0, 1.0);
		setGLColor();
	}
	else {
		DrawableGeometry::setColor(0.9, 0.5, 0.3, 0.0, 0.5, 1.0, 1.0);
		setGLColor();
	}

	glBegin(GL_QUADS);
    
    glVertex3d(12, -1, 0);
	glVertex3d(16, -1, 0);
	glVertex3d(16, -1, 50);
	glVertex3d(12, -1, 50);

	glEnd();

	glPopMatrix();

	
	//lane 5
	glPushMatrix();

	if(laneSelect == 5) {
		DrawableGeometry::setColor(0.1, 0.2, 0.8, 0.0, 0.5, 1.0, 1.0);
		setGLColor();
	}
	else {
		DrawableGeometry::setColor(0.9, 0.5, 0.3, 0.0, 0.5, 1.0, 1.0);
		setGLColor();
	}

	glBegin(GL_QUADS);
    
    glVertex3d(16, -1, 0);
	glVertex3d(20, -1, 0);
	glVertex3d(20, -1, 50);
	glVertex3d(16, -1, 50);

	glEnd();

	glPopMatrix();

	//draw team 0
	glPushMatrix();

	if(teamSelect == 0) {
		DrawableGeometry::setColor(0.1, 0.2, 0.8, 0.0, 0.5, 1.0, 1.0);
		setGLColor();
	}
	else {
		DrawableGeometry::setColor(0.9, 0.5, 0.3, 0.0, 0.5, 1.0, 1.0);
		setGLColor();
	}

	glBegin(GL_QUADS);
    
    glVertex3d(0, -1, 0);
	glVertex3d(20, -1, 0);
	glVertex3d(20, -1, -10);
	glVertex3d(0, -1, -10);

	glEnd();

	glPopMatrix();

	//draw team 1
	glPushMatrix();

	if(teamSelect == 1) {
		DrawableGeometry::setColor(0.1, 0.2, 0.8, 0.0, 0.5, 1.0, 1.0);
		setGLColor();
	}
	else {
		DrawableGeometry::setColor(0.9, 0.5, 0.3, 0.0, 0.5, 1.0, 1.0);
		setGLColor();
	}

	glBegin(GL_QUADS);
    
    glVertex3d(0, -1, 50);
	glVertex3d(20, -1, 50);
	glVertex3d(20, -1, 60);
	glVertex3d(0, -1, 60);

	glEnd();

	glPopMatrix();

	
	
	
	glPopMatrix();



}


void MiniGame::setLane(int lane) {

	laneSelect = lane;

}

void MiniGame::setTeamSelect(int team) {
	teamSelect = team;
}





