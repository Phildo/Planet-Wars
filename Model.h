//
//  Model.h
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_MODEL
#define H_MODEL

///////
//CONSTANTS
///////

//GL CONSTANTS
#define WIDTH 500
#define HEIGHT 400

//STATE CONSTANTS
#define TITLEMENU 0
#define MAINMENU 1
#define GAMEPLAY 2
#define MINIPAUSE 3
#define METAPAUSE 4
#define MINIGAME 5

//MENU
#define TITLE 0
#define MAIN 1
#define MINI 2
#define META 3

//GAME CONSTANTS
#define NUM_LANES 5
#define MAP_DENSITY 3 //1(linear) to 6(full mesh)
#define MAP_DENSITY_STRICTNESS 1000000 //Number of attempts worth spending to try and fit density rule
#define NULL_LOCATION 99999 //'unattainable' row/column to be used for non-placed nodes

//MAP GEO
#define ROW_SPACING 1.3
#define COL_SPACING 1.6

//NODE/UNIT TYPES
#define NUM_TYPES  4
#define TYPE_WATER 0
#define TYPE_EARTH 1
#define TYPE_WIND  2
#define TYPE_FIRE  3

//SHIP TYPES
#define NUM_SHIP_TYPES     4
#define SHIP_TYPE_GENERIC  0
#define SHIP_TYPE_FLAGSHIP 1
#define SHIP_TYPE_CARRIER  2
#define SHIP_TYPE_BATTLE   3

//DEFAULTS
#define DEFAULT_NUM_PLAYERS 2
#define DEFAULT_NUM_NODES 20
#define DEFAULT_STATE MINIGAME

//Forward declarations- everything has access to everything (woah)
class Menu;
class Player;
class Fleet;
class Flagship;
class Ship;
class Unit;
class Map;
class Node;
class Selector;
class MiniGame;

#include <iostream>
#include <string>
#include <math.h>

#include "Menu.h"
#include "Player.h"
#include "Fleet.h"
#include "Flagship.h"
#include "Ship.h"
#include "Unit.h"
#include "Map.h"
#include "Node.h"
#include "Selector.h"
#include "MiniGame.h"

//Singleton class
class Model
{
public:
    /////////
    //Singleton Vars
    /////////
    static Model * selfPtr;
    
    /////////
    //GL Vars
    /////////
    int width;
    int height;
    float mouseX;
    float mouseY;
    float zoom;
    float camCenterX;
    float camCenterY;
    
    /////////
    //Game Vars
    /////////
        //NullVars
    Player * nullPlayer;
    Unit * nullUnit;
    Node * nullNode;
        //GameObjects
	Menu * menu;
    Player ** playerArray;
    Map * map;
    Node ** nodeArray;
    Selector * selector;
    MiniGame * mgame;
        //Game State Vars
    int state;
    int numPlayers;
    int numNodes;
    int teamSelect;
        //MapVars
    int rowMax;
    int rowMin;
    int colMax;
    int colMin;
    
    //////////
    //Model Getters/Setters
    //////////
    static Model * getSelf();
    void setCameraParams();
    Player ** setNumPlayers(int numPlayers);
    Node ** setNumNodes(int numNodes);
    Map * setMap();
    Selector * setSelector();
    Menu * setMenu();
    MiniGame * setMiniGame();

    Model();
    ~Model();
    
    //HELPER FUNCTIONS
    static float random();
};

#endif