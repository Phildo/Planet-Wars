


#include "MapCreator.h"
#include "Node.h"


MapCreator::MapCreator(void)
{
}


MapCreator::~MapCreator(void)
{
}


/*
 * GAME LOGIC FUNCTIONS
 */

void MapCreator::linkNodeToNeighbors(Node * node)
{
    int col;
    int row;
    for(int i = 0; i < 6; i++)
    {
        switch (i) {
            case 0:
                col = node->column;
                row = node->row+2;
                break;
            case 1:
                col = node->column+1;
                row = node->row+1;
                break;
            case 2:
                col = node->column+1;
                row = node->row-1;
                break;
            case 3:
                col = node->column;
                row = node->row-2;
                break;
            case 4:
                col = node->column-1;
                row = node->row-1;
                break;
            case 5:
                col = node->column-1;
                row = node->row+1;
                break;
            default:
                throw new std::string("PICKED NEIGHBOR OUTSIDE BOUNDS");
                break;
        }

        for(int j = 0; j < Model::getSelf()->numNodes; j++)
        {
            if(nodeArray[j]->column == col && nodeArray[j]->row == row)
            {
                node->neighborNodes[i] = nodeArray[j];
                nodeArray[j]->neighborNodes[(i+3)%6] = node;
                node->numNeighborNodes++;
                nodeArray[j]->numNeighborNodes++;
            }
        }
    }
}

void MapCreator::createNodeMap(Node * centerNode, int numNodes)
{
    //  Two important nodes in this algorithm- sourceNode and newNeighbor. 
    //  sourceNode is the node currently looking to add a neighbor (and should already be assigned a location). 
    //  newNeighbor is the node that is looking to be placed, and will be placed next to sourceNode.
    Node* sourceNode;
    Node* newNeighbor;
    int nodesLeftToBeAssigned = numNodes;
    int rNode;
    int rNeighbor;
    int numAssignAttempts;
    bool sourceEligible;
    
    int rowMin = 0;
    int rowMax = 0;
    int colMin = 0;
    int colMax = 0;
    
    //Holds all nodes yet to be assigned. Node gets removed as it is assigned a location
    //Starts with all nodes but 'centerNode', as it is by definition already assigned
    Node** copyArray = new Node*[numNodes];
    for(int i = 0; i < numNodes-1; i++)
    {
        if(i < Model::getSelf()->numPlayers) copyArray[i] = nodeArray[i];
        else copyArray[i] = nodeArray[i+1];
    }
    nodesLeftToBeAssigned--;
    
    centerNode->row = 0;
    centerNode->column = 0;
    //sourceNode = centerNode;

    bool nodeAssigned = false;
    //Assign each node a location
    while(nodesLeftToBeAssigned > 0)
    {
        //Pick a random node from copyArray
        sourceNode = centerNode;
        rNode = (int)(Model::random()*nodesLeftToBeAssigned);
        newNeighbor = copyArray[rNode];
        nodeAssigned = false;
        
        //Algorithm ensures node is assigned
        numAssignAttempts = 0;
        while(!nodeAssigned)
        {
            //If already tried more than 5 times, ignore the MAP_DENSITY rule
            if(numAssignAttempts < MAP_DENSITY_STRICTNESS)
                sourceEligible = sourceNode->numNeighborNodes < MAP_DENSITY && ((rNeighbor = sourceNode->getRandomFreeNeighbor()) != -1);
            else
                sourceEligible = (rNeighbor = sourceNode->getRandomFreeNeighbor()) != -1;
            
            //If the current source node is eligible to have a neighbor
            if(sourceEligible)
            {
                //Assign the new node a location coordinate
                switch (rNeighbor) {
                    case 0:
                        newNeighbor->row = sourceNode->row+2;
                        newNeighbor->column = sourceNode->column;
                        break;
                    case 1:
                        newNeighbor->row = sourceNode->row+1;
                        newNeighbor->column = sourceNode->column+1;
                        break;
                    case 2:
                        newNeighbor->row = sourceNode->row-1;
                        newNeighbor->column = sourceNode->column+1;
                        break;
                    case 3:
                        newNeighbor->row = sourceNode->row-2;
                        newNeighbor->column = sourceNode->column;
                        break;
                    case 4:
                        newNeighbor->row = sourceNode->row-1;
                        newNeighbor->column = sourceNode->column-1;
                        break;
                    case 5:
                        newNeighbor->row = sourceNode->row+1;
                        newNeighbor->column = sourceNode->column-1;
                        break;
                    default:
                        throw new std::string("PICKED NEIGHBOR OUTSIDE BOUNDS");
                        break;
                }
                
                //Uncomment for debugging info
                //std::cout << "SourceNode: " << sourceNode->column << "," << sourceNode->row << std::endl;
                //std::cout << "NeighborNode: " << newNeighbor->column << "," << newNeighbor->row << "\n" << std::endl;

                //Link new node to all other neighbors based on coordinate
                linkNodeToNeighbors(newNeighbor);
                
                //Remove node from copyArray
                for(int i = rNode; i < nodesLeftToBeAssigned-1; i++)
                {
                    copyArray[i] = copyArray[i+1];
                }
                nodesLeftToBeAssigned--;
                
                if(newNeighbor->row < rowMin)
                    rowMin = newNeighbor->row;
                if(newNeighbor->row > rowMax)
                    rowMax = newNeighbor->row;
                if(newNeighbor->column < colMin)
                    colMin = newNeighbor->column;
                if(newNeighbor->column > colMax)
                    colMax = newNeighbor->column;
                
                nodeAssigned = true;
            }
            //Otherwise assign a current neighbor of the source node as the new source node
            else
            {
                sourceNode = sourceNode->neighborNodes[sourceNode->getRandomNeighbor()];
                numAssignAttempts++;
            }
        }
    }
    Model::getSelf()->rowMin = rowMin;
    Model::getSelf()->rowMax = rowMax;
    Model::getSelf()->colMin = colMin;
    Model::getSelf()->colMax = colMax;
    Model::getSelf()->setCameraParams();
    
    delete copyArray;
}
