

#ifndef H_NODE
#define H_NODE

#include "Node.h"

class MapCreator
{
public:
	MapCreator(void);
	~MapCreator(void);
	void linkNodeToNeighbors(Node * node);
	void createNodeMap(Node * centerNode, int numNodes);
};

#endif
