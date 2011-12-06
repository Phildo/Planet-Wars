//
//  Player.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Player.h"
#include "Model.h"

Player::Player()
{
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
}