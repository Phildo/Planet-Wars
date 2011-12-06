//
//  Model.h
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_MODEL
#define H_MODEL

/**
 * CONSTANTS
 */

//GL CONSTANTS
#define WIDTH 500
#define HEIGHT 400

//GAME CONSTANTS
#define MAP_DENSITY 3 //1(linear) to 6(full mesh)
#define MAP_DENSITY_STRICTNESS 1000000 //Number of attempts worth spending to try and fit density rule
#define NULL_LOCATION 99999 //'unattainable' row/column to be used for non-placed nodes

//Node/Unit Types
#define NUM_TYPES  4
#define TYPE_WATER 0
#define TYPE_EARTH 1
#define TYPE_WIND  2
#define TYPE_FIRE  3

//Ship Types
#define NUM_SHIP_TYPES     4
#define SHIP_TYPE_GENERIC  0
#define SHIP_TYPE_FLAGSHIP 1
#define SHIP_TYPE_CARRIER  2
#define SHIP_TYPE_BATTLE   3

/**
 * END_CONSTANTS
 */


//Forward declarations- everything has access to everything (woah)
class Player;
class Node;
class Selector;
class Unit;
class Ship;
class Flagship;
class Fleet;
class Menus;

#include "Player.h"
#include "Node.h"
#include "Selector.h"
#include "Unit.h"
#include "Ship.h"
#include "Flagship.h"
#include "Fleet.h"
#include "Menus.h"

//Singleton class
class Model
{
public:
    static Model * selfPtr;
    static Model * getSelf();
    
    //GL Vars
    int width;
    int height;
    double mouseX;
    double mouseY;
    
    //Game Vars
    Player * nullPlayer;
    Node * nullNode;
    Unit * nullUnit;
	Menus * curMenu;
    
    Player ** playerArray;
    Node ** nodeArray;
    Selector * selector;

    
    int numPlayers;
    int numNodes;
    int rowMax;
    int rowMin;
    int colMax;
    int colMin;
    double zoom;
    double camCenterX;
    double camCenterY;
    void setCameraParams();
    
    void setNumPlayers(int numPlayers);
    void setNumNodes(int numNodes);
    Selector * setSelector();
    Menus * setMenu(int menu);

    Model();
    ~Model();
    
    //HELPER FUNCTIONS
    static double random();
};

#endif