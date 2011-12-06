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
    layer = -1;
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
    double sqrtOfThreeOverTwo = sqrt(3.0/2.0);
    glPushMatrix();
    //glScaled(100, 10, 10);
    glNewList(Selector::displayList, GL_COMPILE);
    
    glBegin(GL_TRIANGLES);
    
    glVertex3d(0, layer/5, 0);
    glVertex3d(1, layer/5, 0);
    glVertex3d(0.5, layer/5, sqrtOfThreeOverTwo);
    
    glVertex3d(0, layer/5, 0);
    glVertex3d(0.5, layer/5, sqrtOfThreeOverTwo);
    glVertex3d(-0.5, layer/5, sqrtOfThreeOverTwo);
    
    glVertex3d(0, layer/5, 0);
    glVertex3d(-0.5, layer/5, sqrtOfThreeOverTwo);
    glVertex3d(-1, layer/5, 0);
    
    glVertex3d(0, layer/5, 0);
    glVertex3d(-1, layer/5, 0);
    glVertex3d(-0.5, layer/5, -1*sqrtOfThreeOverTwo);
    
    glVertex3d(0, layer/5, 0);
    glVertex3d(-0.5, layer/5, -1*sqrtOfThreeOverTwo);
    glVertex3d(0.5, layer/5, -1*sqrtOfThreeOverTwo);  
    
    glVertex3d(0, layer/5, 0);
    glVertex3d(0.5, layer/5, -1*sqrtOfThreeOverTwo);  
    glVertex3d(1, layer/5, 0);
    
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

void Selector::set(int x, int y)
{
    int tCol = (int)-5*x;
    int tRow = (int)5*y;
    if((tCol + tRow)%2 == 0)
    {
        this->column = tCol;
        this->row = tRow;
    }
}

void Selector::drawAtPosition()
{
    glPushMatrix();
    glTranslated(column*2, 0, row*1.2);
    draw();
    glPopMatrix();
}