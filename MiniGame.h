#ifndef MINIGAME_H
#define MINIGAME_H

#include <vector>
#include "DrawableGeometry.h"
#include "Unit.h"

using namespace std;

class MiniGame : public DrawableGeometry
{
public:
	MiniGame(void);

	vector<Unit*> units;
	int numUnits;
	int laneSelect;
	int teamSelect;


	void checkAttacks();
	void attackUnit(Unit *attacker, Unit *attackee);
	double distance(Unit *unit1, Unit *unit2);
	void addUnit(int uType, int uLane, int uTeam);
	void removeUnit(int index);
	void drawGame();
	void update();
	void setLane(int lane);
	void setTeamSelect(int team);
};

#endif