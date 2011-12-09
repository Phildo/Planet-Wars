//
//  main.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//


#ifndef _WIN32
    #include <OpenGL/OpenGL.h>
    #include <GLUT/GLUT.h>
#elif
    #include <GL\freeglut.h>
    #include <GL\GL.h>
#endif


#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "Model.h"

//MODEL ACCESSORS:: DO NOT ABUSE THESE!!!!
Model * model;
Player ** playerArray;
Map * map;
Node ** nodeArray;
Selector * selector;
Menu * menu;
MiniGame * game;

/////////
//GAME LOGIC FUNCTIONS
/////////
void initGame(int numPlayers, int numNodes)
{    
    //Make sure each player can have a starting node
    if(numNodes < numPlayers+1)
        throw new std::string("LESS NODES THAN PLAYERS");

    //Initialize Game Objects and assign them to main-accessible pointers
    nodeArray =  model->setNumNodes(numNodes);
    playerArray = model->setNumPlayers(numPlayers);
    selector = model->setSelector();
    map = model->setMap();
    game = model->setMiniGame(nodeArray[0], playerArray[0], playerArray[1]);
    menu = model->setMenu();
}

/////////
//GAME STATES
/////////

// This is the TITLE

void pregame(){
	//Main Viewport
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0 , ((double) Model::getSelf()->width) / ((double) Model::getSelf()->height), 1.0f , 100.0);
	glViewport(0 , 0 , Model::getSelf()->width, Model::getSelf()->height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Notes for the camera:
	// Eye`2`
	// Center
	// Lookat
	gluLookAt(
		Model::getSelf()->camCenterX+Model::getSelf()->mouseX*10, Model::getSelf()->zoom, Model::getSelf()->mouseY*-10, 
		0, 0, 0, 
		0, 0, -1
		); 

	menu->setMenu(TITLE);
	glPushMatrix();
	glScalef(10.0, 0, 7.0);
	menu->draw();
	glPopMatrix();
}

void mainMenu(){
	//Main Viewport
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0 , ((double) Model::getSelf()->width) / ((double) Model::getSelf()->height), 1.0f , 100.0);
	glViewport(0 , 0 , Model::getSelf()->width, Model::getSelf()->height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Notes for the camera:
	// Eye
	// Center
	// Lookat
	gluLookAt(
		Model::getSelf()->camCenterX+Model::getSelf()->mouseX*10, Model::getSelf()->zoom, Model::getSelf()->mouseY*-10, 
		0, 0, 0, 
		0, 0, -1
		); 

	menu->setMenu(META);
	glPushMatrix();
	glScalef(10.0, 0, 7.0);
	menu->draw();
	glPopMatrix();
}

void metapause(){
	//Main Viewport
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0 , ((double) Model::getSelf()->width) / ((double) Model::getSelf()->height), 1.0f , 100.0);
	glViewport(0 , 0 , Model::getSelf()->width, Model::getSelf()->height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Notes for the camera:
	// Eye
	// Center
	// Lookat
	gluLookAt(
		Model::getSelf()->camCenterX+Model::getSelf()->mouseX*10, Model::getSelf()->zoom, Model::getSelf()->mouseY*-10, 
		0, 0, 0, 
		0, 0, -1
		); 

	menu->setMenu(META);
	glPushMatrix();
	glScalef(10.0, 0, 7.0);
	menu->draw();
	glPopMatrix();
}

void minipause(){
	//Main Viewport
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0 , ((double) Model::getSelf()->width) / ((double) Model::getSelf()->height), 1.0f , 100.0);
	glViewport(0 , 0 , Model::getSelf()->width, Model::getSelf()->height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Notes for the camera:
	// Eye
	// Center
	// Lookat
	gluLookAt(
		Model::getSelf()->camCenterX+Model::getSelf()->mouseX*10, Model::getSelf()->zoom, Model::getSelf()->mouseY*-10, 
		0, 0, 0, 
		0, 0, -1
		); 

	menu->setMenu(MINI);
	glPushMatrix();
	glScalef(10.0, 0, 7.0);
	menu->draw();
	glPopMatrix();

}

void gameplay(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(model->camCenterX+model->mouseX*-10, model->zoom, model->camCenterY+model->mouseY*10,
              model->camCenterX, 0, model->camCenterY,
              0, 0, -1); 
    
	// Draw different aspects of the game during gameplay:
    if(model->finishTurn)
    {
        map->tick();
        for(int i = 0; i < Model::getSelf()->numPlayers; i++)
            playerArray[i]->endTurn();
        model->finishTurn = false;
    }
	map->draw();
    for(int i = 0; i < Model::getSelf()->numPlayers; i++)
        playerArray[i]->draw();
}

void minigame() { 
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 20.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    game->update();
	game->drawGame();
}


/////////
//GL FUNCTIONS
/////////

//Called when mouse dragged (sets mouseX and mouseY from -1 to 1)
void PassiveMotionFunc(int x, int y)
{
    model->mouseX = (-2.0*x/model->width)+1.0;
	model->mouseY = (2.0*y/model->height)-1.0;
}

void MouseFunc(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        map->selectSelected();
    }
}

void DisplayFunc()
{
	//Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Main Viewport
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0 , ((float) model->width) / ((float) model->height), 1.0f , 100.0);
	glViewport(0 , 0 , model->width, model->height);
    
   
	switch(model->state){
        case TITLE:
            pregame();
            break;
		case MAINMENU:
			mainMenu();
			break;
		case METAPAUSE:
			metapause();
			break;
		case MINIPAUSE:
			minipause();
        case GAMEPLAY:
            gameplay();
            break;
        case MINIGAME:
            minigame();
            break;
	}
    
    model->tickCount++;
	glutSwapBuffers();
}

void IdleFunc()
{
    glutPostRedisplay();
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	//SHOULD PUT KEY SWITCH STATEMENTS IN INDIVIDUAL STATE CASES
	//(ie each state has its own set of keystrokes)
	switch(model->state){
	case TITLE:
		switch (key)
		{
		case 13:
			model->state = MAINMENU;
			break;
		}
		break;
	case MAINMENU:
		switch (key)
		{
		case 13:
			model->state = GAMEPLAY;
			break;
		}
		break;
	case METAPAUSE:
		switch (key)
		{
		case 13:
			model->state = GAMEPLAY;
			break;
		}
		break;
	case MINIPAUSE:
		switch (key)
		{
		case 13:
			model->state = MINIGAME;
			break;
		}
		break;
	case GAMEPLAY:
		switch (key)
		{
		case 'p':
			model->state = METAPAUSE;
			break;
		}
		break;
	case MINIGAME:
		switch (key)
		{
		case 'p':
			model->state = MINIPAUSE;
			break;
		case '[': //left arrow
			game->changeLane(LEFT);
			break;
		case ']': //right arrow
			game->changeLane(RIGHT);
			break;
		case 'z':
			game->addUnit(model->playerArray[0], TYPE_WATER);
			break;
		case 'x':
			game->addUnit(model->playerArray[0], TYPE_EARTH);
			break;
		case 'c':
			game->addUnit(model->playerArray[0], TYPE_WIND);
			break;
		case 'v':
			game->addUnit(model->playerArray[0], TYPE_FIRE);
			break;
		}    

		break;
	}
	// General key statements:
	switch(key)
	{
	case 27: // Press the ESC key to exit the game immediately.
		exit(0);
		break;
	case 'p':
		//Menu::setMenu(META);
		break;
		// For state testing:
	case '1':
		model->state = GAMEPLAY;
		break;
	case '0':
		model->state = TITLE;
		break;
	case '2':
		model->state = MINIGAME;
		break;
		
	case ' ': // I'm not sure where this is supposed to go.
		model->finishTurn = true;
	}
}

void SpecialFunc(int key, int x, int y)
{
     //if(key == GLUT_KEY_F1){
     //mode = (mode + 1)%NUM_MODES;
     //}
}

//Called on Window Resize
void ReshapeFunc(int w, int h)
{
	if (h <= 0) 
		return;
    model->height = h;
	model->width = w;
}

void initGL(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0 , 0);
	glutInitWindowSize(model->width,model->height);
	glutCreateWindow("PlanetsConquerer!");
	//glutFullScreen();
	/*
	 * The following section is curser specification. You guys can choose what is appropriate,
	 * but for now I'm getting rid of it.
	 * Other types: GLUT_CURSOR_CROSSHAIR GLUT_CURSOR_NONE
	 */
	glutSetCursor(GLUT_CURSOR_NONE);
    
	//One-Time setups
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_FLAT);
    
    //Aim Stationary Light
    GLfloat pos[4] = {5.0f, 5.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    GLfloat full[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, full);
    glLightfv(GL_LIGHT0, GL_SPECULAR, full);
    glLightfv(GL_LIGHT0, GL_AMBIENT, full);
	
    //Callback Functions
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
    glutPassiveMotionFunc(PassiveMotionFunc);
    glutMouseFunc(MouseFunc);
    glutKeyboardFunc(KeyboardFunc);
    glutSpecialFunc(SpecialFunc);
}







int main (int argc, char * argv[])
{
    model = Model::getSelf();
    initGL(argc, argv);
    initGame(model->numPlayers, model->numNodes);
    glutMainLoop();

    std::cout << "Hello, World!\n";
    return 0;
}

