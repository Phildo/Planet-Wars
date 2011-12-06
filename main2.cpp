//
//  main.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

 // MAC only libraries / previous version.
/*
#import <OpenGL/OpenGL.h>
#import <GLUT/GLUT.h>
*/
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL\freeglut.h>
#include <GL\GL.h>


#include "Model.h"
#include "Menus.h"

#define TITLEMENU 0
#define MAINMENU 1
#define GAMEPLAY 2
#define MINIPAUSE 3
#define METAPAUSE 4
#define MINIGAME 5

int numPlayers = 3;
int numNodes = 50;
int state = 0;

Player ** playerArray;
Node ** nodeArray;
Selector * selector;

/*
 * GAME LOGIC FUNCTIONS
 */

void linkNodeToNeighbors(Node * node)
{
    int col;
    int row;
    for(int i = 0; i < 6; i++)
    {
        switch (i) {
            case 0:
                col = node->column;
                row = node->row+2;
                break;
            case 1:
                col = node->column+1;
                row = node->row+1;
                break;
            case 2:
                col = node->column+1;
                row = node->row-1;
                break;
            case 3:
                col = node->column;
                row = node->row-2;
                break;
            case 4:
                col = node->column-1;
                row = node->row-1;
                break;
            case 5:
                col = node->column-1;
                row = node->row+1;
                break;
            default:
                throw new std::string("PICKED NEIGHBOR OUTSIDE BOUNDS");
                break;
        }

        for(int j = 0; j < Model::getSelf()->numNodes; j++)
        {
            if(nodeArray[j]->column == col && nodeArray[j]->row == row)
            {
                node->neighborNodes[i] = nodeArray[j];
                nodeArray[j]->neighborNodes[(i+3)%6] = node;
                node->numNeighborNodes++;
                nodeArray[j]->numNeighborNodes++;
            }
        }
    }
}

void createNodeMap(Node * centerNode, int numNodes)
{
    //  Two important nodes in this algorithm- sourceNode and newNeighbor. 
    //  sourceNode is the node currently looking to add a neighbor (and should already be assigned a location). 
    //  newNeighbor is the node that is looking to be placed, and will be placed next to sourceNode.
    Node* sourceNode;
    Node* newNeighbor;
    int nodesLeftToBeAssigned = numNodes;
    int rNode;
    int rNeighbor;
    int numAssignAttempts;
    bool sourceEligible;
    
    int rowMin = 0;
    int rowMax = 0;
    int colMin = 0;
    int colMax = 0;
    
    //Holds all nodes yet to be assigned. Node gets removed as it is assigned a location
    //Starts with all nodes but 'centerNode', as it is by definition already assigned
    Node** copyArray = new Node*[numNodes];
    for(int i = 0; i < numNodes-1; i++)
    {
        if(i < Model::getSelf()->numPlayers) copyArray[i] = nodeArray[i];
        else copyArray[i] = nodeArray[i+1];
    }
    nodesLeftToBeAssigned--;
    
    centerNode->row = 0;
    centerNode->column = 0;
    //sourceNode = centerNode;

    bool nodeAssigned = false;
    //Assign each node a location
    while(nodesLeftToBeAssigned > 0)
    {
        //Pick a random node from copyArray
        sourceNode = centerNode;
        rNode = (int)(Model::random()*nodesLeftToBeAssigned);
        newNeighbor = copyArray[rNode];
        nodeAssigned = false;
        
        //Algorithm ensures node is assigned
        numAssignAttempts = 0;
        while(!nodeAssigned)
        {
            //If already tried more than 5 times, ignore the MAP_DENSITY rule
            if(numAssignAttempts < MAP_DENSITY_STRICTNESS)
                sourceEligible = sourceNode->numNeighborNodes < MAP_DENSITY && ((rNeighbor = sourceNode->getRandomFreeNeighbor()) != -1);
            else
                sourceEligible = (rNeighbor = sourceNode->getRandomFreeNeighbor()) != -1;
            
            //If the current source node is eligible to have a neighbor
            if(sourceEligible)
            {
                //Assign the new node a location coordinate
                switch (rNeighbor) {
                    case 0:
                        newNeighbor->row = sourceNode->row+2;
                        newNeighbor->column = sourceNode->column;
                        break;
                    case 1:
                        newNeighbor->row = sourceNode->row+1;
                        newNeighbor->column = sourceNode->column+1;
                        break;
                    case 2:
                        newNeighbor->row = sourceNode->row-1;
                        newNeighbor->column = sourceNode->column+1;
                        break;
                    case 3:
                        newNeighbor->row = sourceNode->row-2;
                        newNeighbor->column = sourceNode->column;
                        break;
                    case 4:
                        newNeighbor->row = sourceNode->row-1;
                        newNeighbor->column = sourceNode->column-1;
                        break;
                    case 5:
                        newNeighbor->row = sourceNode->row+1;
                        newNeighbor->column = sourceNode->column-1;
                        break;
                    default:
                        throw new std::string("PICKED NEIGHBOR OUTSIDE BOUNDS");
                        break;
                }
                
                //Uncomment for debugging info
                //std::cout << "SourceNode: " << sourceNode->column << "," << sourceNode->row << std::endl;
                //std::cout << "NeighborNode: " << newNeighbor->column << "," << newNeighbor->row << "\n" << std::endl;

                //Link new node to all other neighbors based on coordinate
                linkNodeToNeighbors(newNeighbor);
                
                //Remove node from copyArray
                for(int i = rNode; i < nodesLeftToBeAssigned-1; i++)
                {
                    copyArray[i] = copyArray[i+1];
                }
                nodesLeftToBeAssigned--;
                
                if(newNeighbor->row < rowMin)
                    rowMin = newNeighbor->row;
                if(newNeighbor->row > rowMax)
                    rowMax = newNeighbor->row;
                if(newNeighbor->column < colMin)
                    colMin = newNeighbor->column;
                if(newNeighbor->column > colMax)
                    colMax = newNeighbor->column;
                
                nodeAssigned = true;
            }
            //Otherwise assign a current neighbor of the source node as the new source node
            else
            {
                sourceNode = sourceNode->neighborNodes[sourceNode->getRandomNeighbor()];
                numAssignAttempts++;
            }
        }
    }
    Model::getSelf()->rowMin = rowMin;
    Model::getSelf()->rowMax = rowMax;
    Model::getSelf()->colMin = colMin;
    Model::getSelf()->colMax = colMax;
    Model::getSelf()->setCameraParams();
    
    delete copyArray;
}

void initGame(int numPlayers, int numNodes)
{    
    //Make sure each player can have a starting node
    if(numNodes < numPlayers+1)
        throw new std::string("LESS NODES THAN PLAYERS");
    
    //Allocate space for all Players and Nodes
    Model::getSelf()->setNumPlayers(numPlayers);
    Model::getSelf()->setNumNodes(numNodes);
    
    //Copy pointers from model as it is likely they will be used often
    //**BE CAREFUL- DO NOT ABUSE THIS**
    playerArray = Model::getSelf()->playerArray;
    nodeArray = Model::getSelf()->nodeArray;
    //Set Selector (called here instead of in constructor to allow for GL to be allocated first)
    selector = Model::getSelf()->setSelector();

    //Create players and assign each a node
    for(int i = 0; i < numPlayers; i++)
    {
        playerArray[i] = new Player();
        nodeArray[i] = new Node(i%NUM_TYPES);
        playerArray[i]->conquerNode(nodeArray[i]);
    }
    
    //Create 'center' node (used in generating map
    Node * centerNode;
    centerNode = nodeArray[numPlayers] = new Node((int)(Model::random()*NUM_TYPES));
    
    //Create neutral nodes
    for(int i = numPlayers+1; i < numNodes; i++)
    {
        nodeArray[i] = new Node((int)(Model::random()*NUM_TYPES));
    }
    
    //Create map out of Nodes
    createNodeMap(centerNode, numNodes);
}


/*
 * GL FUNCTIONS
 */

//DRAWING FUNCTIONS

void drawSelector()
{
    int tCol = (int)-5*Model::getSelf()->mouseX;
    int tRow = (int)5*Model::getSelf()->mouseY;
    if((tCol + tRow)%2 == 0)
    {
        selector->column = tCol;
        selector->row = tRow;
    }
    glPushMatrix();
    glTranslated(selector->column*2, 0, selector->row*1.2);
    selector->draw();
    glPopMatrix();
}

void drawMap()
{
	
    
    for(int i = 0; i < Model::getSelf()->numNodes; i++)
    {
        glPushMatrix();
        glTranslated(nodeArray[i]->column*2, 0, nodeArray[i]->row*1.2);
        nodeArray[i]->draw();
        glPopMatrix();
    }
    
}

//CALLBACK FUNCTIONS

//Called when mouse dragged (sets mouseX and mouseY from -1 to 1)
void PassiveMotionFunc(int x, int y)
{
    Model::getSelf()->mouseX = (-2.0*x/Model::getSelf()->width)+1.0;
	Model::getSelf()->mouseY = (2.0*y/Model::getSelf()->height)-1.0;
}


void pregame(){
	//Main Viewport
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0 , ((double) Model::getSelf()->width) / ((double) Model::getSelf()->height), 1.0f , 100.0);
	glViewport(0 , 0 , Model::getSelf()->width, Model::getSelf()->height);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Model::getSelf()->camCenterX+Model::getSelf()->mouseX*10, Model::getSelf()->zoom, Model::getSelf()->camCenterY+Model::getSelf()->mouseY*-10, 
		Model::getSelf()->camCenterX, 0, Model::getSelf()->camCenterY, 
		0, 0, 1); 

	Model::getSelf()->setMenu(TITLE);
	glPushMatrix();
	glScalef(5.0, 1, 5.0);
	Model::getSelf()->curMenu->draw();
	glPopMatrix();
}

void gameplay(){
	//Main Viewport
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0 , ((double) Model::getSelf()->width) / ((double) Model::getSelf()->height), 1.0f , 100.0);
	glViewport(0 , 0 , Model::getSelf()->width, Model::getSelf()->height);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Model::getSelf()->camCenterX+Model::getSelf()->mouseX*10, Model::getSelf()->zoom, Model::getSelf()->camCenterY+Model::getSelf()->mouseY*-10, Model::getSelf()->camCenterX, 0, Model::getSelf()->camCenterY, 0, 0, -1); 

	// Draw different aspects of the game during gameplay:
	drawMap();
	drawSelector();
}

void DisplayFunc()
{
	//Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// The following set the different modes of the game.
	switch(state){
	case TITLE:
		pregame();
		break;
	case GAMEPLAY:
		gameplay();
		break;
	case MINIGAME:
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
		 //Menus::setMenu(META);
		break;
     // For state testing:
	 case '1':
		 state = GAMEPLAY;
		 break;
	 case '0':
		 state = TITLE;
	 }
}

void SpecialFunc(int key, int x, int y)
{
    /*
     if(key == GLUT_KEY_F1){
     mode = (mode + 1)%NUM_MODES;
     }
     */
}

//Called on Window Resize
void ReshapeFunc(int w, int h)
{
	if (h <= 0) 
		return;
    Model::getSelf()->height = h;
	Model::getSelf()->width = w;
}

void initGL(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0 , 0);
	glutInitWindowSize(Model::getSelf()->width,Model::getSelf()->height);
	glutCreateWindow("Sponge Bob to the Stars!");
	glutFullScreen();
    
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
    initGL(argc, argv);
    initGame(numPlayers, numNodes);
    glutMainLoop();

    std::cout << "Hello, World!\n";
    return 0;
}

