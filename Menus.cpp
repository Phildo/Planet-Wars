//
//  Menus.cpp
//  SpongeBobWars
//
//  Created by Brandon Lewis on 11/30/2011
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Menus.h"
#include <iostream>

Menus * Menus::curMenu = NULL;
bool Menus::compiled = false;
GLuint Menus::displayList;

// Building the different kinds of menues for display:

Menus::Menus()
{
    layer = 0;
    setColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0); // Base color
    if(!Menus::compiled) Menus::compileDL();
}

Menus::~Menus()
{

}

// Different types of menus:
void Menus::setTitle(){
	menuFlag = true;
    setColor(.81, .194, .7212, 1.0, 1.0, 1.0, 1.0);

}

void Menus::setMain(){
	menuFlag = true;
	
    setColor(.9, .7, .8, 1.0, 1.0, 1.0, 1.0);

}

void Menus::setMetaPause(){
	menuFlag = true;
    setColor(.323, .321, .321, 1.0, 1.0, 1.0, 1.0);
}

void Menus::setMiniPause(){
	menuFlag = true;
    setColor(.431, .61, .71, 1.0, 1.0, 1.0, 1.0);
}


// Changes to the specified menu, calling this will pause all game actions until the player presses resume.
// This is also going to compile the menu, so everything should be controlled using this and the flag functions.
void Menus::setMenu(int menu){
	switch (menu){
	case TITLE:
		Menus::setTitle();
		break;
	case MAIN:
		Menus::setMain();
		break;
	case MINI:
		Menus::setMiniPause();
		break;
	case META:
		Menus::setMetaPause();
	}
}

// Resets the flage and turns off the menu display.
void Menus::flipFlag(){
	menuFlag = false;
}

bool Menus::getFlag(){
	return this->menuFlag;
}

void Menus::draw(){
    if(!Menus::compiled || !menuFlag) return;
    setGLColor();
    glCallList(Menus::displayList);
}

void Menus::compileDL()
{
    if(Menus::compiled) return;
    Menus::displayList = glGenLists(1);
    glPushMatrix();
    //glScaled(100, 10, 10);
    glNewList(Menus::displayList, GL_COMPILE);
    
    glBegin(GL_QUADS);
    
    glVertex3d(-1, layer, -1);
	glVertex3d(-1, layer, 1);
	glVertex3d(1, layer, 1);
    glVertex3d(1, layer, -1);
    
    glEnd();
    glPopMatrix();
    glEndList();
	Menus::compiled = true;

}