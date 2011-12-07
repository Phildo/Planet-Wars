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

//HELPER CONSTANTS
#define LEFT 0
#define RIGHT 1

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
#define MAP_DENSITY 1 //1(linear) to 6(full mesh)
#define MAP_DENSITY_STRICTNESS 1000000 //Number of attempts worth spending to try and fit density rule
#define NULL_LOCATION 99999 //'unattainable' row/column to be used for non-placed nodes

//MAP GEO
#define ROW_SPACING 1.3
#define COL_SPACING 1.6

//MINIGAME GEO
#define LANE_WIDTH 10
#define LANE_LENGTH 100

//NODE/UNIT TYPES
#define NUM_TYPES  4
#define TYPE_WATER 0
#define TYPE_EARTH 1
#define TYPE_WIND  2
#define TYPE_FIRE  3

//TYPE COLOR VARS
#define WATER_R 0.0
#define WATER_G 0.0
#define WATER_B 1.0
#define EARTH_R 0.2
#define EARTH_G 0.4
#define EARTH_B 0.1
#define WIND_R 1.0
#define WIND_G 1.0
#define WIND_B 0.2
#define FIRE_R 1.0
#define FIRE_G 0.0
#define FIRE_B 0.0

//TYPE ATTRIBUTE VARIABLES
#define WATER_HEALTH 1000;
#define WATER_DAMAGE 100;
#define WATER_RANGE 2;
#define WATER_SPEED 3;
#define WATER_COOL 5;

#define EARTH_HEALTH 5000;
#define EARTH_DAMAGE 10;
#define EARTH_RANGE 1;
#define EARTH_SPEED 1;
#define EARTH_COOL 5;

#define WIND_HEALTH 200;
#define WIND_DAMAGE 50;
#define WIND_RANGE 10;
#define WIND_SPEED 5;
#define WIND_COOL 2;

#define FIRE_HEALTH 1000;
#define FIRE_DAMAGE 150;
#define FIRE_RANGE 5;
#define FIRE_SPEED 3;
#define FIRE_COOL 6;

//SHIP TYPES
#define NUM_SHIP_TYPES     4
#define SHIP_TYPE_GENERIC  0
#define SHIP_TYPE_FLAGSHIP 1
#define SHIP_TYPE_CARRIER  2
#define SHIP_TYPE_BATTLE   3

//DEFAULTS
#define DEFAULT_NUM_PLAYERS 2
#define DEFAULT_NUM_NODES 100
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
    MiniGame * setMiniGame(Node * planet, Player * attacker, Player * defender);

    Model();
    ~Model();
    
    //HELPER FUNCTIONS
    static float random();
};

#endif