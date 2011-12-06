//
//  Model.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#include <iostream>
#include <string>
#include <math.h>

#include "Model.h"

Model * Model::selfPtr = NULL;

Model::Model()
{
    if(Model::selfPtr)
        throw (new std::string("DO NOT CALL CONSTRUCTOR DIRECTLY. USE Model::getSelf()"));
    
    width = WIDTH;
    height = HEIGHT;
    
    this->nullNode = NULL;
    this->nullPlayer = NULL;
    this->nullUnit = NULL;
        
    this->rowMax = 0;
    this->rowMin = 0;
    this->colMax = 0;
    this->colMin = 0;
    
    //HELPER STUFF
    srand(0);
}

Model * Model::getSelf()
{
    if(!Model::selfPtr)
        Model::selfPtr = new Model();
    return selfPtr;
}

Model::~Model()
{
    delete playerArray;
    delete nodeArray;
    delete selector;
    delete selfPtr;
}

void Model::setNumPlayers(int numPlayers)
{
    Model::getSelf()->numPlayers = numPlayers;
    Model::getSelf()->playerArray = new Player*[numPlayers];
}

void Model::setNumNodes(int numNodes)
{
    Model::getSelf()->numNodes = numNodes;
    Model::getSelf()->nodeArray = new Node*[numNodes];
}

Selector * Model::setSelector()
{
    this->selector = new Selector();
    return this->selector;
}

Menus * Model::setMenu(int menu){
	this->curMenu = new Menus();
	this->curMenu->setMenu(menu);
    return this->curMenu;
}

void Model::setCameraParams()
{
    Model::getSelf()->zoom = 4*sqrt(std::max ((double)(rowMax - rowMin), (double)(colMax-colMin))*2.0);
    camCenterX = (colMax + colMin)/2.0;
    camCenterY = (rowMax + rowMin)/2.0;
}

/**
 * HELPER FUNCTIONS
 * Need not do anything specific towards model. Just a universal hub to put useful stuff.
 */

//Generates a value from 0-1. Just makes code cleaner.
double Model::random()
{
    return rand()/(double)RAND_MAX;
}
