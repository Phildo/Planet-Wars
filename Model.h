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
#define VICTORY 6

#define P_ONE_TURN 0
#define P_TWO_TURN 1

//MENU
#define TITLE 0
#define MAIN 1
#define MINI 2
#define META 3

//GAME CONSTANTS
#define MAX_UNITS 10
#define NUM_LANES 5
#define MAP_DENSITY 1 //1(linear) to 6(full mesh)
#define MAP_DENSITY_STRICTNESS 1000000 //Number of attempts worth spending to try and fit density rule
#define NULL_LOCATION 99999 //'unattainable' row/column to be used for non-placed nodes
#define SHIP_COST 10

//MAP GEO
#define ROW_SPACING 1.3
#define COL_SPACING 1.6

//MINIGAME GEO
#define LANE_WIDTH 1000
#define LANE_LENGTH 10000

//SIHP GEO
#define SHIP_SIZE 1

//NODE/UNIT TYPES
#define NUM_TYPES  5
#define TYPE_WATER 0
#define TYPE_EARTH 1
#define TYPE_WIND  2
#define TYPE_FIRE  3
#define TYPE_DARK  4

//TYPE COLOR VARS
#define WATER_R 0.0f
#define WATER_G 0.0f
#define WATER_B 1.0f
#define EARTH_R 0.2f
#define EARTH_G 0.4f
#define EARTH_B 0.1f
#define WIND_R 0.5f
#define WIND_G 0.5f
#define WIND_B 1.0f
#define FIRE_R 1.0f
#define FIRE_G 0.0f
#define FIRE_B 0.0f
#define DARK_R 0.1f
#define DARK_G 0.1f
#define DARK_B 0.1f

//PLAYER COLORS
#define PLAYER_1_R 0.6f
#define PLAYER_1_G 0.2f
#define PLAYER_1_B 0.2f
#define PLAYER_2_R 0.2f
#define PLAYER_2_G 0.2f
#define PLAYER_2_B 0.6f

//TYPE ATTRIBUTE VARIABLES
#define WATER_HEALTH 10000;
#define WATER_DAMAGE 100;
#define WATER_RANGE 200;
#define WATER_SPEED 3;
#define WATER_COOL 5;

#define EARTH_HEALTH 50000;
#define EARTH_DAMAGE 10;
#define EARTH_RANGE 100;
#define EARTH_SPEED 1;
#define EARTH_COOL 5;

#define WIND_HEALTH 2000;
#define WIND_DAMAGE 50;
#define WIND_RANGE 1000;
#define WIND_SPEED 5;
#define WIND_COOL 2;

#define FIRE_HEALTH 10000;
#define FIRE_DAMAGE 150;
#define FIRE_RANGE 500;
#define FIRE_SPEED 3;
#define FIRE_COOL 6;

//SHIP TYPES
#define NUM_SHIP_TYPES     4
#define SHIP_TYPE_GENERIC  0
#define SHIP_TYPE_FLAGSHIP 1
#define SHIP_TYPE_CARRIER  2
#define SHIP_TYPE_BATTLE   3

#define SHIP_HEALTH 10000000

//DEFAULTS
#define DEFAULT_NUM_PLAYERS 2
#define DEFAULT_NUM_NODES 50
#define SEED 1
#define DEFAULT_STATE TITLE

//Forward declarations- everything has access to everything (woah)
class Menu;
class Player;
class Ship;
class Unit;
class Hud;
class Map;
class Node;
class Selector;
class MiniGame;

#include <iostream>
#include <string>
#include <math.h>
#include <time.h>

#include "Menu.h"
#include "Player.h"
#include "Ship.h"
#include "Unit.h"
#include "Hud.h"
#include "Map.h"
#include "Node.h"
#include "Selector.h"
#include "TextPrint.h"
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
    int tickCount;
    
    /////////
    //Game Vars
    /////////
        //NullVars
    Player * nullPlayer;
    Unit * nullUnit;
    Node * nullNode;
    Ship * nullShip;
        //GameObjects
	Menu * menu;
    Player ** playerArray;
    Hud * hud;
    Map * map;
    Node ** nodeArray;
    Selector * selector;
    MiniGame * mgame;
        //Game State Vars
    Node * selectedNode;
    Ship * selectedShip;
    int state;
    int playerturn;
    bool finishTurn;
    int numPlayers;
    int numNodes;
    int teamSelect;
        //MapVars
    int rowMax;
    int rowMin;
    int colMax;
    int colMin;
    
    bool victor;
    
    //////////
    //Model Getters/Setters
    //////////
    static Model * getSelf();
    void setCameraParams();
    Player ** setNumPlayers(int numPlayers);
    Node ** setNumNodes(int numNodes);
    Hud * setHud();
    Map * setMap();
    Selector * setSelector();
    Menu * setMenu();
    MiniGame * setMiniGame(Node * planet, Ship * attacker, Ship * defender);
    
    void enterMiniGame(Node * planet, Ship * attacker, Ship * defender);
    void winMiniGame(bool attacker);
    
    Model();
    ~Model();
    
    //HELPER FUNCTIONS
    static float random();
};

#endif