//
//  Player.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Player.h"

Player::Player()
{
    fireResources = 0;
    waterResources = 0;
    earthResources = 0;
    airResources = 0;
    
    this->fleet = new Fleet();
    this->myNodes = new Node*[Model::getSelf()->numNodes];
    this->nodesOwned = 0;
}

Player::~Player()
{
    delete this->fleet;
}

bool Player::iOwnNode(Node *node)
{
    for(int i = 0; i < this->nodesOwned; i++)
    {
        if(myNodes[i] == node)
            return true;
    }
    return false;
}

void Player::attackNode(Node *attackNode, Node *defendNode)
{
    
}

void Player::conquerNode(Node *node)
{
    if(!iOwnNode(node))
        myNodes[nodesOwned++] = node;
    node->owner = this;
}

Unit * Player::deployUnit(Node *planet, int type)
{
    //Check if unit of requested type exists on any ships on current planet,
    //or if player contains enough resources to create another one. 
    //If so, remove unit from player's army and return unit. Else, return null.
    
    return Model::getSelf()->nullUnit;
}