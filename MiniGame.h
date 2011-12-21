#ifndef MINIGAME_H
#define MINIGAME_H

class Lane;
#include <math.h>
#include <iostream>
#include "Model.h"
#include "Player.h"
#include "Unit.h"
#include "Lane.h"

class MiniGame
{
public:
	MiniGame(Node * node, Ship * attackerShip, Ship * defenderShip);
    
    Node * node;
    Ship * attacker;
    Ship * defender;

    Lane ** lanes;
    int selectedALane;
    int selectedDLane;
    
    void changeLane(int direction, bool attacker);
    void selectLane(int lane, bool attacker);
    void deployUnit(Ship * s, int type);
	void update();
    void drawGame();
};

#endif