//
//  Lane.cpp
//  PlanetWars
//
//  Created by Philip Dougherty on 12/5/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Lane.h"

bool Lane::compiled = false;
GLuint Lane::displayList;

Lane::Lane(int shift)
{
    if(!Lane::compiled) Lane::compileDL();
    this->shift = shift;
    setColor(0.9, 0.5, 0.3, 0.0, 0.5, 1.0, 1.0);
}

Lane::~Lane()
{
    
}

void Lane::compileDL()
{
    if(Lane::compiled) return;
    Lane::displayList = glGenLists(1);
    glNewList(Lane::displayList, GL_COMPILE);
    
    glBegin(GL_QUADS);	
    
    glVertex3f(0, -1, 0);
	glVertex3f(4, -1, 0);
	glVertex3f(4, -1, 50);
	glVertex3f(0, -1, 50);
    
	glEnd();
    
    glEndList();
    Lane::compiled = true;
}

void Lane::draw()
{
    if(!Lane::compiled) return;
    glPushMatrix();
    glTranslated(shift*4, 0, 0);
    glCallList(Lane::displayList);
    glPopMatrix();
}