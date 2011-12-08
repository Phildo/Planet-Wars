//
//  Node.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//


#include "Node.h"

void Node::initStuff()
{
    this->neighborNodes = new Node*[6];
    Node *  nN = Model::getSelf()->nullNode;
    assignNeighbors(nN, nN, nN, nN, nN, nN);
    this->numNeighborNodes = 0;
    owner = Model::getSelf()->nullPlayer;
    row = NULL_LOCATION;
    column = NULL_LOCATION;
    layer = 0.0f;
    
    if(!Node::compiled) Node::compileDL();
}

Node::Node()
{
    setType(-1);
    initStuff();
}

Node::Node(int type)
{
    setType(type);
    initStuff();
}

Node::~Node()
{
    delete neighborNodes;
}

void Node::setType(int t)
{
    this->type = t;
    
    switch (t) {
        case TYPE_EARTH:
            this->setColor(EARTH_R, EARTH_G, EARTH_B, 1.0, 0.1, 0.5, 0.7);
            break;
        case TYPE_WIND:
            this->setColor(WIND_R, WIND_G, WIND_B, 1.0, 0.1, 0.5, 0.7);
            break;
        case TYPE_FIRE:
            this->setColor(FIRE_R, FIRE_G, FIRE_B, 1.0, 0.1, 0.5, 0.7);
            break;
        case TYPE_WATER:
            this->setColor(WATER_R, WATER_G, WATER_B, 1.0, 0.1, 0.5, 0.7);
            break;
        default:
            this->setColor(0.3, 0.3, 0.3, 1.0, 0.1, 0.5, 0.7);
            break;
    }
}

int Node::getRandomFreeNeighbor()
{
    int r = (int)(Model::random()*6);
    for(int i = 0; i < 6; i++)
    {
        if(this->neighborNodes[(r+i)%6] == Model::getSelf()->nullNode)
            return ((r+i)%6);
    }
    return -1;
}

int Node::getRandomNeighbor()
{
    int r = (int)(Model::random()*6);
    for(int i = 0; i < 6; i++)
    {
        if(this->neighborNodes[(r+i)%6] != Model::getSelf()->nullNode)
            return ((r+i)%6);
    }
    return -1;
}

void Node::assignNeighbors(Node *top, Node *topRight, Node *bottomRight, Node *bottom, Node *bottomLeft, Node *topLeft)
{
    this->neighborNodes[0] = top;
    this->neighborNodes[1] = topRight;
    this->neighborNodes[2] = bottomRight;
    this->neighborNodes[3] = bottom;
    this->neighborNodes[4] = bottomLeft;
    this->neighborNodes[5] = topLeft;
}

void Node::tick()
{
    if(owner == Model::getSelf()->nullPlayer) return;
    switch (type) {
        case TYPE_EARTH:
            this->owner->earthResources+=productionRate;
            break;
        case TYPE_WIND:
            this->owner->windResources+=productionRate;
            break;
        case TYPE_FIRE:
            this->owner->fireResources+=productionRate;
            break;
        case TYPE_WATER:
            this->owner->waterResources+=productionRate;
            break;
        default:
            //Nothin'
            break;
    }
    if(owner->home == this) owner->fleet->addShip();
}


//DRAWABLE GEO FUNCTIONS
bool Node::compiled = false;
GLuint Node::displayList;

void Node::compileDL()
{
    if(Node::compiled) return;
    Node::displayList = glGenLists(1);
    float sqrtOfThreeOverTwo = sqrt(3.0/2.0);

    glNewList(Node::displayList, GL_COMPILE);
    
    glBegin(GL_TRIANGLES);
    
    glVertex3f(0, 0, 0);
    glVertex3f(1, layer, 0);
    glVertex3f(0.5, layer, sqrtOfThreeOverTwo);

    glVertex3f(0, 0, 0);
    glVertex3f(0.5, layer, sqrtOfThreeOverTwo);
    glVertex3f(-0.5, layer, sqrtOfThreeOverTwo);
    
    glVertex3f(0, 0, 0);
    glVertex3f(-0.5, layer, sqrtOfThreeOverTwo);
    glVertex3f(-1, layer, 0);
    
    glVertex3f(0, 0, 0);
    glVertex3f(-1, layer, 0);
    glVertex3f(-0.5, layer, -1*sqrtOfThreeOverTwo);
    
    glVertex3f(0, 0, 0);
    glVertex3f(-0.5, layer, -1*sqrtOfThreeOverTwo);
    glVertex3f(0.5, layer, -1*sqrtOfThreeOverTwo);  
    
    glVertex3f(0, 0, 0);
    glVertex3f(0.5, layer, -1*sqrtOfThreeOverTwo);  
    glVertex3f(1, layer, 0);
    
    glEnd();
    glEndList();
    Node::compiled = true;
}

void Node::draw()
{
    if(!Node::compiled) return;
    setGLColor();
    glCallList(Node::displayList);
}

void Node::drawAtPosition()
{
    glPushMatrix();
    glTranslated(column*COL_SPACING, 0, row*ROW_SPACING);
    draw();
    glPopMatrix();
}
