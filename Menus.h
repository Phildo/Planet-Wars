//
//  Menus.h
//  SpongeBobWars
//
//  Created by Brandon Lewis on 11/30/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_MENUS
#define H_MENUS

#define TITLE 0
#define MAIN 1
#define MINI 2
#define META 3

#include "DrawableGeometry.h"

class Menus: public DrawableGeometry
{
public:
	static Menus * curMenu;

    //GL Vars
    int width;
    int height;
    double mouseX;
    double mouseY;
	static bool compiled;
	static GLuint displayList;

	// Camera Stuff:
    double zoom;
    double camCenterX;
    double camCenterY;
    void setCameraParams();

	// Fuctions:
	Menus();
	~Menus();
	void setMenu(int menu);
	void flipFlag();
	bool getFlag();
	void draw();

private:
	// Menu variables:
	bool menuFlag;
	void Menus::setTitle();
	void Menus::setMain();
	void Menus::setMetaPause();
	void Menus::setMiniPause();
	void Menus::compileDL();
};

#endif