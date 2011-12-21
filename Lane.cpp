//
//  Lane.cpp
//  PlanetWars
//
//  Created by Philip Dougherty on 12/5/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Lane.h"

//DRAWABLE GEOMETRY STUFF
bool Lane::compiled = false;
GLuint Lane::selectedList;
GLuint Lane::unselectedList;

bool Lane::winMini = false;
bool Lane::setWinMini = false;
bool Lane::attackerWin = false;

Lane::Lane()
{
    if(!Lane::compiled) Lane::compileDL();
    
    attackerUnits = new Unit*[MAX_UNITS * NUM_TYPES];
    attackerIndex = 0;
    defenderUnits = new Unit*[MAX_UNITS * NUM_TYPES];
    defenderIndex = 0;

    aSelected = false;
    dSelected = false;
    
    furthestAttacker = 0;
    furthestDefender = 0;
}

Lane::~Lane()
{
    
}

void Lane::compileDL()
{
    if(Lane::compiled) return;
    Lane::unselectedList = glGenLists(1);
    glNewList(Lane::unselectedList, GL_COMPILE);
    glBegin(GL_QUADS);	
    glColor3f(0.9f, 0.5f, 0.3f);
    glVertex3f(-1*LANE_WIDTH/2.0, -100, 0);
	glVertex3f(LANE_WIDTH/2.0, -100, 0);
	glVertex3f(LANE_WIDTH/2.0, -100, LANE_LENGTH/2.0);
	glVertex3f(-1*LANE_WIDTH/2.0, -100, LANE_LENGTH/2.0);
    
	glEnd();
    
    glEndList();
    
    
    Lane::selectedList = glGenLists(1);
    glNewList(Lane::selectedList, GL_COMPILE);
    glBegin(GL_TRIANGLES);	
    
    glColor3f(0.5f, 0.5f, 1.0f);
    glVertex3f(-1*LANE_WIDTH/2.0, -100, 0);
	glVertex3f(LANE_WIDTH/2.0, -100, 0);
    glColor3f(0.9f, 0.5f, 0.3f);
	glVertex3f(LANE_WIDTH/2.0, -100, LANE_LENGTH/2.0);
    
    
	glVertex3f(-1*LANE_WIDTH/2.0, -100, LANE_LENGTH/2.0);
    glVertex3f(LANE_WIDTH/2.0, -100, LANE_LENGTH/2.0);
    glColor3f(0.5f, 0.5f, 1.0f);
    glVertex3f(-LANE_WIDTH/2.0, -100, 0);
    
	glEnd();
    
    glEndList();
    
    Lane::compiled = true;
}

void Lane::draw()
{
    if(!Lane::compiled) return;
    glDisable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, LANE_LENGTH/2.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    if(aSelected)
        glCallList(Lane::selectedList);
    else
        glCallList(Lane::unselectedList);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -LANE_LENGTH/2.0);
    if(dSelected)
        glCallList(Lane::selectedList);
    else
        glCallList(Lane::unselectedList);
    glPopMatrix();

    
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, LANE_LENGTH/2.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    for(int i = 0; i < attackerIndex; i++)
        attackerUnits[i]->drawAtPosition();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -LANE_LENGTH/2.0);
    for(int i = 0; i < defenderIndex; i++)
        defenderUnits[i]->drawAtPosition();
    glPopMatrix();

    
    
    glEnable(GL_LIGHTING);
    glShadeModel(GL_FLAT);
}

//LOGIC STUFF

void Lane::removeUnitFromArray(Unit * u, bool attacker)
{
    bool found = false;
    if(attacker)
    {
        for(int i = 0; i < attackerIndex; i++)
        {
            if(found) attackerUnits[i-1] = attackerUnits[i];
            if(attackerUnits[i] == u)
            {
                delete u;
                found = true;
            }
        }
        attackerIndex--;
        
        if(attackerIndex == 0)
            furthestAttacker = 0;
        else
            furthestAttacker = findFurthestUnit(true)->pos; 
    }
    
    else
    {
        for(int i = 0; i < defenderIndex; i++)
        {
            if(found) defenderUnits[i-1] = defenderUnits[i];
            if(defenderUnits[i] == u)
            {
                delete u;
                found = true;
            }
        }
        defenderIndex--;
        
        if(defenderIndex == 0)
            furthestDefender = 0;
        else
            furthestDefender = findFurthestUnit(false)->pos; 
    }
}

void Lane::setSelected(bool selected, bool attacker)
{
    if(attacker)
        aSelected = selected;
    else
        dSelected = selected;
}

void Lane::deployUnit(Unit * unit, bool attacker)
{
    if(attacker)
    {
        attackerUnits[attackerIndex] = unit;
        attackerIndex++;
    }
    else
    {
        defenderUnits[defenderIndex] = unit;
        defenderIndex++;
    }
}

void Lane::advanceUnit(Unit * unit, bool attacker)
{
    if(attacker)
    {
        if(unit->pos+unit->speed > LANE_LENGTH-furthestDefender-unit->range)
        {
            if(LANE_LENGTH-furthestDefender-unit->range > unit->pos) 
                unit->pos = LANE_LENGTH-furthestDefender-unit->range;
        }
        else
            unit->pos = unit->pos+unit->speed;
        
        if(unit->pos > furthestAttacker) furthestAttacker = unit->pos;
    }
    else
    {
        if(unit->pos+unit->speed > LANE_LENGTH-furthestAttacker-unit->range)
        {
            if(LANE_LENGTH-furthestAttacker-unit->range > unit->pos) 
                unit->pos = LANE_LENGTH-furthestAttacker-unit->range;
        }
        else
            unit->pos = unit->pos+unit->speed;
        
        if(unit->pos > furthestDefender) furthestDefender = unit->pos;
    }
}

void Lane::actUnit(Unit * unit, bool attacker)
{
    bool kill;
    Unit * furthest;
    if(attacker)
    {
        if(defenderIndex != 0)
        {
            if(unit->pos+unit->range >= LANE_LENGTH-furthestDefender)
            {
                furthest = findFurthestUnit(false);
                kill = unit->attack(furthest);
                if(kill)
                {
                    removeUnitFromArray(furthest, false);
                }
            }
        }
        else
        {
            //Attack Ship
            Model::getSelf()->mgame->defender->health -= unit->damage;
            if(Model::getSelf()->mgame->defender->health <= 0)
            {
                Lane::winMini = true;
                Lane::attackerWin = true;
            }
        }
    }
    else
    {
        if(attackerIndex != 0)
        {
            if(unit->pos+unit->range >= LANE_LENGTH-furthestAttacker)
            {
                furthest = findFurthestUnit(true);
                kill = unit->attack(furthest);
                if(kill)
                {
                    removeUnitFromArray(furthest, true);
                }
            }
        }
        else
        {
            //Attack Ship
            Model::getSelf()->mgame->attacker->health -= unit->damage;
            if(Model::getSelf()->mgame->attacker->health <= 0)
            {
                Lane::winMini = true;
                Lane::attackerWin = false;
            }
        }
    }
}

Unit* Lane::findFurthestUnit(bool attacker)
{
    int furthestPos = -1;
    Unit * u;
    if(attacker)
    {
        for(int i = 0; i < attackerIndex; i++)
        {
            if(attackerUnits[i]->pos > furthestPos)
            {
                furthestPos = attackerUnits[i]->pos;
                u = attackerUnits[i];
            }
        }
    }
    else
    {
        for(int i = 0; i < defenderIndex; i++)
        {
            if(defenderUnits[i]->pos > furthestPos)
            {
                furthestPos = defenderUnits[i]->pos;
                u = defenderUnits[i];
            }
        }
    }
    return u;
}

void Lane::tick()
{
    if(Lane::winMini)
    {
        if(Lane::setWinMini) return;
        Lane::setWinMini = true;
        Model::getSelf()->winMiniGame(attackerWin);
        return;
    }
    

    //Update Units' Positions
    for(int i = 0; i < defenderIndex; i++)
    {
        advanceUnit(defenderUnits[i], false);
    }
    for(int i = 0; i < attackerIndex; i++)
    {
        advanceUnit(attackerUnits[i], true);
    }
    
    //Attack Units
    for(int i = 0; i < defenderIndex; i++)
    {
        actUnit(defenderUnits[i], false);
    }
    for(int i = 0; i < attackerIndex; i++)
    {
        actUnit(attackerUnits[i], true);
    }
}