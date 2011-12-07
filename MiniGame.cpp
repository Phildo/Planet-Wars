#include "MiniGame.h"
#include <math.h>

#include <iostream>

#include <windows.h>



MiniGame::MiniGame(void)
{

	//addUnit(1, 1, 0);
	//addUnit(2,2,0);
	//addUnit(3, 3, 0);
	//addUnit(4,4,0);
	laneSelect = 5;
	teamSelect = 0;
	numUnits = 0;
    
    lanes = new Lane*[NUM_LANES];
    for(int i = 0; i < NUM_LANES; i++)
    {
        lanes[i] = new Lane(i);
    }
    
    setColor(0.1, 0.2, 0.8, 0.0, 0.5, 1.0, 1.0);
	DrawableGeometry::setGLColor();
}

void MiniGame::checkAttacks() {

	for(int x = 0; x < MiniGame::numUnits; x++) {
		units[x]->canAttack = true;
		units[x]->isMoving = true;
	}

	for(int i = 0; i < MiniGame::numUnits; i++) {
		Unit *unit1 = MiniGame::units[i];

		if(unit1->canAttack) {

			//MessageBox(NULL, "I am just trying my wedding dress", NULL, NULL);

			for(int j = 0; j < MiniGame::numUnits; j++) {
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
	numUnits = numUnits + 1;
}


//only remove units at the end of an update for iteration purposes
void MiniGame::removeUnit(int index) {
	MiniGame::units.erase(units.begin() + index);
	numUnits = numUnits - 1;
}


void MiniGame::update() {


	for(int index = 0; index < numUnits; index++) {
		if(units[index]->isDead()) {
			removeUnit(index);
		}
		
	}

	for(int i = 0; i < units.size(); i++) {
		units[i]->update();
	}
	checkAttacks();
}


void MiniGame::drawGame() {
    setColor(0.1, 0.2, 0.8, 0.0, 0.5, 1.0, 1.0);
	DrawableGeometry::setGLColor();
    
    //Draw Units
	for(int i = 0; i < units.size(); i++) {
		units[i]->drawAtPosition();
	}

    //Draw Lanes
    for(int i = 0; i < NUM_LANES; i++)
    {
        if(laneSelect == i+1)
            setGLColor();
        else
            lanes[i]->setGLColor();
        lanes[i]->draw();
    }


	//draw team 0

	if(teamSelect != 0)
		setColor(0.9, 0.5, 0.3, 0.0, 0.5, 1.0, 1.0);
    setGLColor();

	glBegin(GL_QUADS);
    glVertex3f(0, -1, 0);
	glVertex3f(20, -1, 0);
	glVertex3f(20, -1, -10);
	glVertex3f(0, -1, -10);
	glEnd();


    setColor(0.1, 0.2, 0.8, 0.0, 0.5, 1.0, 1.0);
    
	//draw team 1
    if(teamSelect != 1)
		setColor(0.9, 0.5, 0.3, 0.0, 0.5, 1.0, 1.0);
    setGLColor();
    
	glBegin(GL_QUADS);
    glVertex3f(0, -1, 50);
	glVertex3f(20, -1, 50);
	glVertex3f(20, -1, 60);
	glVertex3f(0, -1, 60);
	glEnd();

}

void MiniGame::setLane(int lane) {
	laneSelect = lane;
}

void MiniGame::setTeamSelect(int team) {
	teamSelect = team;
}





