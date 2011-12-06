//
//  Node.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include <math.h>
#include "Node.h"
#include "Model.h"

void Node::initStuff()
{
    this->neighborNodes = new Node*[6];
    Node *  nN = Model::getSelf()->nullNode;
    assignNeighbors(nN, nN, nN, nN, nN, nN);
    this->numNeighborNodes = 0;
    row = NULL_LOCATION;
    column = NULL_LOCATION;
    layer = 0;
    
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
            this->setColor(0.2, 0.4, 0.1, 1.0, 0.1, 1.0, 0.7);
            break;
        case TYPE_WIND:
            this->setColor(1.0, 1.0, 0.2, 1.0, 0.1, 0.5, 0.7);
            break;
        case TYPE_FIRE:
            this->setColor(1.0, 0.0, 0.0, 1.0, 0.1, 0.5, 0.7);
            break;
        case TYPE_WATER:
            this->setColor(0.0, 0.0, 1.0, 1.0, 0.1, 0.5, 0.7);
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
    
}


//DRAWABLE GEO FUNCTIONS
bool Node::compiled = false;
GLuint Node::displayList;

void Node::compileDL()
{
    if(Node::compiled) return;
    Node::displayList = glGenLists(1);
    double sqrtOfThreeOverTwo = sqrt(3.0/2.0);

    glNewList(Node::displayList, GL_COMPILE);
    
    glBegin(GL_TRIANGLES);
    
    glVertex3d(0, 0, 0);
    glVertex3d(1, layer/5, 0);
    glVertex3d(0.5, layer/5, sqrtOfThreeOverTwo);

    glVertex3d(0, 0, 0);
    glVertex3d(0.5, layer/5, sqrtOfThreeOverTwo);
    glVertex3d(-0.5, layer/5, sqrtOfThreeOverTwo);
    
    glVertex3d(0, 0, 0);
    glVertex3d(-0.5, layer/5, sqrtOfThreeOverTwo);
    glVertex3d(-1, layer/5, 0);
    
    glVertex3d(0, 0, 0);
    glVertex3d(-1, layer/5, 0);
    glVertex3d(-0.5, layer/5, -1*sqrtOfThreeOverTwo);
    
    glVertex3d(0, 0, 0);
    glVertex3d(-0.5, layer/5, -1*sqrtOfThreeOverTwo);
    glVertex3d(0.5, layer/5, -1*sqrtOfThreeOverTwo);  
    
    glVertex3d(0, 0, 0);
    glVertex3d(0.5, layer/5, -1*sqrtOfThreeOverTwo);  
    glVertex3d(1, layer/5, 0);
    
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
    glTranslated(column*2, 0, row*1.2);
    draw();
    glPopMatrix();
}
