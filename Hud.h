#ifndef HUD_H
#define HUD_H

#include "Model.h"
#include "DrawableGeometry.h"
#include "Node.h"
#include "Ship.h"

class Hud: public DrawableGeometry
{
public:
	Hud(void);
	~Hud(void);
    
    static bool compiled;       //True iff displayList names a valid glDisplayList
    static GLuint metaDl;
    static GLuint miniDl;
    static GLuint mapvDl;
    static GLuint typeMappingDl;
    
    Node ** pOneNodes;
    Ship * pOneShip;
    float pOneRot;
    Node ** pTwoNodes;
    Ship * pTwoShip;
    float pTwoRot;
    
    void compileDL();       //Stores geometry in a displayList   
	void drawMeta();
	void drawMini();
    void drawMapv();
};

#endif