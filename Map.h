//
//  Map.h
//  PlanetWars
//
//  Created by Philip Dougherty on 12/5/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef MAP_H
#define MAP_H

#include "Model.h"
#include "Node.h"
#include "Selector.h"

class Map
{
public:
    Node ** nodeArray;
    Selector * selector;
    
    Map(int numNodes);
    ~Map();
    
    void linkNodeToNeighbors(Node * node);
    void createNodeMap(int numNodes);
    void tick();
    void draw();
};
#endif