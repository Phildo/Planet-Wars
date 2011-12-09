//
//  Ship.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Ship.h"
#include "Model.h"
bool Ship::compiled = false;
GLuint Ship::displayList;

Ship::Ship(Player * o)
{
    this->shipType = SHIP_TYPE_GENERIC;
    layer = .25;
    owner = o;
    if(!Ship::compiled) compileDL();
	/* Ryan
	this->shipType = SHIP_TYPE_GENERIC;
    layer = .25;
    if(!Ship::compiled) compileDL();
	health = 20000;
	*/
}

Ship::~Ship()
{
    
}

void Ship::compileDL()
{
    //Sample compilation of a simple sphere 
    if(Ship::compiled) return;
    displayList = glGenLists(1);
    glNewList(Ship::displayList, GL_COMPILE);
    
	// Ryan
	/*//Set Color Here
    setColor(1.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0);
    setGLColor();
	
	// pyramids - ships on metamap
	GLfloat rtri = 0.0f;
	glTranslatef(0.0, 1.0, 0.0);
	glRotatef(rtri,0.0f,1.0f,0.0f);					// rotate pyramid on y-axis
	glBegin(GL_TRIANGLES);							//start to draw the pyramid
	
    glColor3f(1.0f,0.0f,0.0f);			// red
	glVertex3f( 0.0f, 1.0f, 0.0f);		// up-frontplane
	glColor3f(0.0f,1.0f,0.0f);			// green
	glVertex3f(-1.0f,-1.0f, 1.0f);		// left-frontplane
	glColor3f(0.0f,0.0f,1.0f);			// blue
	glVertex3f( 1.0f,-1.0f, 1.0f);		// right-frontplane

	glColor3f(1.0f,0.0f,0.0f);			// red
	glVertex3f( 0.0f, 1.0f, 0.0f);		// up-rightplane
	glColor3f(0.0f,0.0f,1.0f);			// blue
	glVertex3f( 1.0f,-1.0f, 1.0f);		// left-rightplane
	glColor3f(0.0f,1.0f,0.0f);			// green
	glVertex3f( 1.0f,-1.0f, -1.0f);		// right-rightplane

	glColor3f(1.0f,0.0f,0.0f);			// red
	glVertex3f( 0.0f, 1.0f, 0.0f);		// up-backplane
	glColor3f(0.0f,1.0f,0.0f);			// green
	glVertex3f( 1.0f,-1.0f, -1.0f);		// left-backplane
	glColor3f(0.0f,0.0f,1.0f);			// plane
	glVertex3f(-1.0f,-1.0f, -1.0f);		// right-backplane
    
	glColor3f(1.0f,0.0f,0.0f);			// red
	glVertex3f( 0.0f, 1.0f, 0.0f);		// up-leftplane
	glColor3f(0.0f,0.0f,1.0f);			// blue
	glVertex3f(-1.0f,-1.0f,-1.0f);		// left-leftplane
	glColor3f(0.0f,1.0f,0.0f);			// green
	glVertex3f(-1.0f,-1.0f, 1.0f);		// right-leftplane
	glEnd();							// end of drawing pyramid
    

    glPopMatrix();
	*/

    //DRAW SHIP HERE
    glPushMatrix();
    
    glBegin(GL_QUADS);
    glVertex3f(-.5*SHIP_SIZE, layer, -.5*SHIP_SIZE);
    glVertex3f(-.5*SHIP_SIZE, layer, .5*SHIP_SIZE);
    glVertex3f(.5*SHIP_SIZE, layer, .5*SHIP_SIZE);
    glVertex3f(.5*SHIP_SIZE, layer, -.5*SHIP_SIZE);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(.5*SHIP_SIZE, layer, -.5*SHIP_SIZE);
    glVertex3d(SHIP_SIZE, layer, 0);
    glVertex3d(.5*SHIP_SIZE, layer, .5*SHIP_SIZE);
    glEnd();
    
    glPopMatrix();
    
    glEndList();
    Ship::compiled = true;
}

void Ship::draw()
{
	/* Ryan
    if(!Ship::compiled) return;    
    glCallList(Ship::displayList);
	*/
    if(!Ship::compiled) return;   
    if(loc->selected) setColor(0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0);
    else setColor(0.4, 0.4, 0.4, 1.0, 1.0, 1.0, 1.0);
    setGLColor();
    glCallList(Ship::displayList);
}

void Ship::drawAtPosition()
{
    if(loc == Model::getSelf()->nullNode)
    {
        draw();
        return;
    }
    glPushMatrix();
    glTranslated(loc->column*COL_SPACING, 0, loc->row*ROW_SPACING);
    draw();
    glPopMatrix();
}

void Ship::moveToNode(Node *newLoc)
{
	/* Ryan
    if(loc->isNeighborOf(newLoc))
    {
        loc = newLoc;
        done = true;
    }
	*/
    if(done) return;
    if(loc->isNeighborOf(newLoc))
    {
        loc->ship = Model::getSelf()->nullShip;
        loc = newLoc;
        loc->ship = this;
        owner->conquerNode(loc);
        done = true;
    }
}
