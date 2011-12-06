//
//  Selector.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/12/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include <math.h>
#include "Selector.h"

bool Selector::compiled = false;
GLuint Selector::displayList;

Selector::Selector()
{
    layer = -.25f;
    setColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    row = 0;
    column = 0;
    if(!Selector::compiled) Selector::compileDL();
}

Selector::~Selector()
{
    
}

void Selector::compileDL()
{
    if(Selector::compiled) return;
    Selector::displayList = glGenLists(1);
    float sqrtOfThreeOverTwo = sqrt(3.0/2.0);
    glPushMatrix();
    glNewList(Selector::displayList, GL_COMPILE);
    ;
    glScalef(1.1f, 1.0f, 1.1f);
    glBegin(GL_TRIANGLES);
    
    glVertex3f(0, layer, 0);
    glVertex3f(1, layer, 0);
    glVertex3f(0.5, layer, sqrtOfThreeOverTwo);
    
    glVertex3f(0, layer, 0);
    glVertex3f(0.5, layer, sqrtOfThreeOverTwo);
    glVertex3f(-0.5, layer, sqrtOfThreeOverTwo);
    
    glVertex3f(0, layer, 0);
    glVertex3f(-0.5, layer, sqrtOfThreeOverTwo);
    glVertex3f(-1, layer, 0);
    
    glVertex3f(0, layer, 0);
    glVertex3f(-1, layer, 0);
    glVertex3f(-0.5, layer, -1*sqrtOfThreeOverTwo);
    
    glVertex3f(0, layer, 0);
    glVertex3f(-0.5, layer, -1*sqrtOfThreeOverTwo);
    glVertex3f(0.5, layer, -1*sqrtOfThreeOverTwo);  
    
    glVertex3f(0, layer, 0);
    glVertex3f(0.5, layer, -1*sqrtOfThreeOverTwo);  
    glVertex3f(1, layer, 0);
    
    glEnd();
    glPopMatrix();
    glEndList();    Selector::compiled = true;

}

void Selector::draw()
{
    if(!Selector::compiled) return;
    setGLColor();
    glCallList(Selector::displayList);
}

void Selector::set(float x, float y)
{
    int tCol = (int)5*x;
    int tRow = (int)-5*y;
    if((tCol + tRow)%2 == 0)
    {
        this->column = tCol;
        this->row = tRow;
    }
}

void Selector::drawAtPosition()
{
    glPushMatrix();
    glTranslated(column*1.7, 0, row*1.3);
    draw();
    glPopMatrix();
}