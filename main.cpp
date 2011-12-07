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
    game = model->setMiniGame();
    menu = model->setMenu();
}

/////////
//GAME STATES
/////////

void pregame(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(model->camCenterX+model->mouseX*-10, model->zoom, model->camCenterY+model->mouseY*10, 
              model->camCenterX, 0, model->camCenterY, 
              0, 0, -1); 
    
	menu->setMenu(TITLE);
	glPushMatrix();
	glScalef(5.0, 1, 5.0);
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
	map->draw();
}

void minigame() { 
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10.0, 50.0, -20.0, 10.0, 0.0, 20.0, 0.0, 1.0, 0.0);
    
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

void DisplayFunc()
{
	//Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Main Viewport
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0 , ((float) model->width) / ((float) model->height), 1.0f , 100.0);
	glViewport(0 , 0 , model->width, model->height);
    
	// The following set the different modes of the game.
    
    //model->state = MINIGAME;
	switch(model->state){
        case TITLE:
            pregame();
            break;
        case GAMEPLAY:
            gameplay();
            break;
        case MINIGAME:
            minigame();
            break;
	}
    
	//DoubleBuffering
	glutSwapBuffers();
}

void IdleFunc()
{
    glutPostRedisplay();
}

void KeyboardFunc(unsigned char key, int x, int y)
{
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
            
        case '[': //left arrow
            if(game->laneSelect < 5)
                game->setLane(game->laneSelect+1);
            break;
            
        case ']': //right arrow
            if(game->laneSelect > 1)
                game->setLane(game->laneSelect-1);
            break;
            
        case 'q':
            game->setTeamSelect(1);
            break;
            
        case 'a':
            game->setTeamSelect(0);
            break;
        case 'z':
            game->addUnit(1, game->laneSelect, game->teamSelect);
            break;
            
        case 'x':
            game->addUnit(2, game->laneSelect, game->teamSelect);
            break;
            
        case 'c':
            game->addUnit(3, game->laneSelect, game->teamSelect);
            break;
            
        case 'v':
            game->addUnit(4, game->laneSelect, game->teamSelect);
            break;
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
	glutCreateWindow("Sponge Bob to the Stars!");
	//glutFullScreen();
    
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

