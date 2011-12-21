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
}




