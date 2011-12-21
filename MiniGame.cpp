#include "MiniGame.h"

MiniGame::MiniGame(Node * planet, Ship * attackerShip, Ship * defenderShip)
{
    node = planet;
    attacker = attackerShip;
    defender = defenderShip;
    
    lanes = new Lane*[NUM_LANES];
    for(int i = 0; i < NUM_LANES; i++)
    {
        lanes[i] = new Lane();
    }
    selectedALane = 0;
    selectedDLane = NUM_LANES-1;
    lanes[selectedALane]->setSelected(true, true);
    lanes[selectedDLane]->setSelected(true, false);
}

void MiniGame::changeLane(int direction, bool attacker)
{
    if(attacker)
    {
        if(direction == LEFT && selectedALane != 0)
            selectLane(selectedALane-1, true);
        else if(direction == RIGHT && selectedALane != 4)
            selectLane(selectedALane+1, true);
    }
    else
    {
        if(direction == LEFT && selectedDLane != 0)
            selectLane(selectedDLane-1, false);
        else if(direction == RIGHT && selectedDLane != 4)
            selectLane(selectedDLane+1, false);
    }
    
}

void MiniGame::selectLane(int lane, bool attacker)
{
    if(attacker)
    {
        lanes[selectedALane]->setSelected(false, true);
        selectedALane = lane;
        lanes[selectedALane]->setSelected(true, true); 
    }
    else
    {
        lanes[selectedDLane]->setSelected(false, false);
        selectedDLane = lane;
        lanes[selectedDLane]->setSelected(true, false); 
    }
    
}

void MiniGame::deployUnit(Ship * s, int type) {
    Unit * u = s->deployUnit(type);
    if(u != Model::getSelf()->nullUnit)
    {
        if(attacker == s)
            lanes[selectedALane]->deployUnit(u, true);
        else
            lanes[selectedDLane]->deployUnit(u, false);
    }
}

void MiniGame::update() {
    
    if(attacker->numWaterUnits + attacker->numEarthUnits + attacker->numWindUnits + attacker->numFireUnits == 0 &&
       lanes[0]->attackerIndex == 0 &&
       lanes[1]->attackerIndex == 0 &&
       lanes[2]->attackerIndex == 0 &&
       lanes[3]->attackerIndex == 0 &&
       lanes[4]->attackerIndex == 0)
        attacker->health -= 1000;
    if(defender->numWaterUnits + defender->numEarthUnits + defender->numWindUnits + defender->numFireUnits == 0 &&
       lanes[0]->defenderIndex == 0 &&
       lanes[1]->defenderIndex == 0 &&
       lanes[2]->defenderIndex == 0 &&
       lanes[3]->defenderIndex == 0 &&
       lanes[4]->defenderIndex == 0)
        defender->health -= 1000;
    
    if(attacker->health <= 0) 
    {
        Lane::winMini = true;
        Lane::attackerWin = false;
    }
    if(defender->health <= 0) 
    {
        Lane::winMini = true;
        Lane::attackerWin = true;
    }
     
    
    for(int i = 0; i < NUM_LANES; i++)
    {
        lanes[i]->tick();
    }
}


void MiniGame::drawGame() {
    //Draw Lanes
    for(int i = 0; i < NUM_LANES; i++)
    {
        glPushMatrix();
        glTranslated((double)((LANE_WIDTH*i)-(LANE_WIDTH*(int)(NUM_LANES/2))), 0.0, 0.0);
        lanes[i]->draw();
        glPopMatrix();
    }
    
    glPushMatrix();
    if(attacker->owner == Model::getSelf()->playerArray[0])
        glColor3f(1.0, 0.0, 0.0);
    else
        glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, LANE_LENGTH/2);
    glBegin(GL_QUADS);
    glVertex3d(-.5*(LANE_WIDTH*NUM_LANES), -100.0, 0.0);
    glVertex3d(.5*(LANE_WIDTH*NUM_LANES), -100.0, 0.0);
    glVertex3d(.5*(LANE_WIDTH*NUM_LANES), -100.0, -300.0);
    glVertex3d(-.5*(LANE_WIDTH*NUM_LANES), -100.0, -300.0);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    if(defender->owner == Model::getSelf()->playerArray[0])
        glColor3f(1.0, 0.0, 0.0);
    else
        glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, LANE_LENGTH/-2);
    glBegin(GL_QUADS);
    glVertex3d(-.5*(LANE_WIDTH*NUM_LANES), -100.0, 0.0);
    glVertex3d(.5*(LANE_WIDTH*NUM_LANES), -100.0, 0.0);
    glVertex3d(.5*(LANE_WIDTH*NUM_LANES), -100.0, 300.0);
    glVertex3d(-.5*(LANE_WIDTH*NUM_LANES), -100.0, 300.0);
    glEnd();
    glPopMatrix();
    
    
    
    
    //Draw Health
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslated(0.0, 500.0, -5000.0);
    glBegin(GL_QUADS);
    glVertex3f(-1* NUM_LANES * LANE_WIDTH / 2, 0.0, -100.0);
    glVertex3f(-1* NUM_LANES * LANE_WIDTH / 2, 0.0, 100.0);
    glVertex3f((-1* NUM_LANES * LANE_WIDTH / 2) + (NUM_LANES * LANE_WIDTH * ((float)defender->health/(float)SHIP_HEALTH)), 0.0, 100.0);
    glVertex3f((-1* NUM_LANES * LANE_WIDTH / 2) + (NUM_LANES * LANE_WIDTH * ((float)defender->health/(float)SHIP_HEALTH)), 0.0, -100.0);
    glEnd();
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslated(0.0, 500.0, 5000.0);
    glBegin(GL_QUADS);
    glVertex3f(-1* NUM_LANES * LANE_WIDTH / 2, 0.0, -100.0);
    glVertex3f(-1* NUM_LANES * LANE_WIDTH / 2, 0.0, 100.0);
    glVertex3f((-1* NUM_LANES * LANE_WIDTH / 2) + (NUM_LANES * LANE_WIDTH * ((float)attacker->health/(float)SHIP_HEALTH)), 0.0, 100.0);
    glVertex3f((-1* NUM_LANES * LANE_WIDTH / 2) + (NUM_LANES * LANE_WIDTH * ((float)attacker->health/(float)SHIP_HEALTH)), 0.0, -100.0);
    glEnd();
    glPopMatrix();
    
}




