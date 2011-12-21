#include "Hud.h"


Hud::Hud(void)
{
    pOneNodes = new Node *[NUM_TYPES];
    pTwoNodes = new Node *[NUM_TYPES];
    
    pOneShip = new Ship(Model::getSelf()->playerArray[0]);
    pTwoShip = new Ship(Model::getSelf()->playerArray[1]);
    
    for(int i = 0; i < NUM_TYPES; i++)
    {
        pOneNodes[i] = new Node(i);
        pOneNodes[i]->owner = Model::getSelf()->playerArray[0];
        pOneNodes[i]->display = true;
        pOneRot = 0;
        pTwoNodes[i] = new Node(i);
        pTwoNodes[i]->owner = Model::getSelf()->playerArray[1];
        pTwoNodes[i]->display = true;
        pTwoRot = 0;
    }
    if(!Hud::compiled) Hud::compileDL();
}


Hud::~Hud(void)
{
}

bool Hud::compiled = false;       //True iff displayList names a valid glDisplayList
GLuint Hud::metaDl;
GLuint Hud::miniDl;
GLuint Hud::mapvDl;
GLuint Hud::typeMappingDl;

void Hud::compileDL()
{
    if(Hud::compiled) return;
    
    Hud::metaDl = glGenLists(1);
    glNewList(Hud::metaDl, GL_COMPILE);
    
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    
    glEnd();
    glPopMatrix();
    
    glEndList();   
    
    
    
    
    Hud::miniDl = glGenLists(1);
    glNewList(Hud::miniDl, GL_COMPILE);
    
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    
    glEnd();
    glPopMatrix();
    
    glEndList();   
    
    
    Hud::typeMappingDl = glGenLists(1);
    glNewList(Hud::typeMappingDl, GL_COMPILE);
    
    glPushMatrix();
    glTranslated(-0.5, 0.0, 0.0);
    glColor3f(WATER_R, WATER_G, WATER_B);
    glBegin(GL_QUADS);
    glVertex3d(0.0, 0.25, 0.0);
    glVertex3d(0.25, 0.25, 0.0);
    glVertex3d(0.25, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glTranslated(0.25, 0.0, 0.0);
    glColor3f(EARTH_R, EARTH_G, EARTH_B);
    glBegin(GL_QUADS);
    glVertex3d(0.0, 0.25, 0.0);
    glVertex3d(0.25, 0.25, 0.0);
    glVertex3d(0.25, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glTranslated(0.25, 0.0, 0.0);
    glColor3f(WIND_R, WIND_G, WIND_B);
    glBegin(GL_QUADS);
    glVertex3d(0.0, 0.25, 0.0);
    glVertex3d(0.25, 0.25, 0.0);
    glVertex3d(0.25, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glTranslated(0.25, 0.0, 0.0);
    glColor3f(FIRE_R, FIRE_G, FIRE_B);
    glBegin(GL_QUADS);
    glVertex3d(0.0, 0.25, 0.0);
    glVertex3d(0.25, 0.25, 0.0);
    glVertex3d(0.25, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glPopMatrix();
    
    glEndList();
    
    
    
    Hud::mapvDl = glGenLists(1);
    glNewList(Hud::mapvDl, GL_COMPILE);
    /*
    float w = (float)Model::getSelf()->width/(float)Model::getSelf()->height;
    float h = (float)Model::getSelf()->height/(float)Model::getSelf()->width;
    glPushMatrix();
    glScalef(w*1.5, h*1.5, 1.0);
    glBegin(GL_QUADS);
    
    //Left
    glVertex3f(-1, -1, -2.0f);
    glVertex3f(-1, 1, -2.0f);
    glVertex3f(-.9, 1, -2.0f);
    glVertex3f(-.9, -1, -2.0f);
    
    //Right
    glVertex3f(.9, -1, -2.0f);
    glVertex3f(.9, 1, -2.0f);
    glVertex3f(1, 1, -2.0f);
    glVertex3f(1, -1, -2.0f);
    
    //Top
    glVertex3f(-1, .9, -2.0f);
    glVertex3f(-1, 1, -2.0f);
    glVertex3f(1, 1, -2.0f);
    glVertex3f(1, .9, -2.0f);
    
    //Bottom
    glVertex3f(-1, -1, -2.0f);
    glVertex3f(-1, -.9, -2.0f);
    glVertex3f(1, -.9, -2.0f);
    glVertex3f(1, -1, -2.0f);

    glEnd();
    glPopMatrix();
    */
    glEndList();   
    
    
    
    
    Hud::compiled = true;
}

void Hud::drawMeta()
{
    if(!Hud::compiled) return;

}

void Hud::drawMini()
{
    if(!Hud::compiled) return;

    

}

void Hud::drawMapv()
{
    if(!Hud::compiled) return;
    setColor(0.5f, 0.5f, 0.5f, 1.0f, 0.1f, 0.5f, 0.7f);
    setGLColor();
    glCallList(mapvDl);
    float dif = -2.0f/((float)NUM_TYPES+2.0f);
    glPushMatrix();
    glTranslated(-1.5, 0.2, 0.0);
    glTranslatef(0.0, 1.0, -2.0);
    glTranslatef(0.0, dif, 0.0);
    
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glRotatef(pOneRot, 0.0, 1.0, 0.0);
    glTranslated(0.0, 0.0, -0.4);
    glRotatef(80, 1.0f, 0.0f, 0.0f);
    pOneShip->numWaterUnits = ((float)pOneShip->owner->waterNodesOwned/(float)(pOneShip->owner->nodesOwned-pOneShip->owner->darkNodesOwned))*MAX_UNITS;
    pOneShip->numEarthUnits = ((float)pOneShip->owner->earthNodesOwned/(float)(pOneShip->owner->nodesOwned-pOneShip->owner->darkNodesOwned))*MAX_UNITS;
    pOneShip->numWindUnits = ((float)pOneShip->owner->windNodesOwned/(float)(pOneShip->owner->nodesOwned-pOneShip->owner->darkNodesOwned))*MAX_UNITS;
    pOneShip->numFireUnits = ((float)pOneShip->owner->fireNodesOwned/(float)(pOneShip->owner->nodesOwned-pOneShip->owner->darkNodesOwned))*MAX_UNITS;
    pOneShip->draw();
    glPopMatrix();
    
    for(int i = 0; i < NUM_TYPES; i++)
    {
        glTranslatef(0.0, dif, 0.0);
        glPushMatrix();
        if(Model::getSelf()->playerturn == P_ONE_TURN)
            pOneRot+=.1f;
        else
            pOneRot+=.01f;
        if(pOneRot == 360.0f)
            pOneRot = 0.0;
        glRotatef(pOneRot, 0.0, 1.0, 0.0);
        glRotatef(80, 1.0f, 0.0f, 0.0f);
        glScalef(0.1,0.1,0.1);
        pOneNodes[i]->draw();
        glPopMatrix();
    }
    glTranslatef(0.0, dif, 0.0);
    glRotatef(pOneRot, 0.0, 1.0, 0.0);

    gluSphere(gluNewQuadric(), 0.15, 5, 5);
    glPopMatrix();
    
    
    
    glPushMatrix();
    glTranslated(1.5, 0.2, 0.0);
    glTranslatef(0.0, 1.0, -2.0);
    glTranslatef(0.0, dif, 0.0);
    
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glRotatef(pTwoRot, 0.0, 1.0, 0.0);
    glTranslated(0.0, 0.0, -0.4);
    glRotatef(80, 1.0f, 0.0f, 0.0f);
    pTwoShip->numWaterUnits = ((float)pTwoShip->owner->waterNodesOwned/(float)(pOneShip->owner->nodesOwned-pOneShip->owner->darkNodesOwned))*MAX_UNITS;
    pTwoShip->numEarthUnits = ((float)pTwoShip->owner->earthNodesOwned/(float)(pOneShip->owner->nodesOwned-pOneShip->owner->darkNodesOwned))*MAX_UNITS;
    pTwoShip->numWindUnits = ((float)pTwoShip->owner->windNodesOwned/(float)(pOneShip->owner->nodesOwned-pOneShip->owner->darkNodesOwned))*MAX_UNITS;
    pTwoShip->numFireUnits = ((float)pTwoShip->owner->fireNodesOwned/(float)(pOneShip->owner->nodesOwned-pOneShip->owner->darkNodesOwned))*MAX_UNITS;
    pTwoShip->draw();
    glPopMatrix();
    
    for(int i = 0; i < NUM_TYPES; i++)
    {
        glTranslatef(0.0, dif, 0.0);
        glPushMatrix();
        if(Model::getSelf()->playerturn == P_TWO_TURN)
            pTwoRot+=.1f;
        else
            pTwoRot+=.01f;
        if(pTwoRot == 360.0f)
            pTwoRot = 0.0;
        glRotatef(pTwoRot, 0.0, 1.0, 0.0);       
        glRotatef(80, 1.0f, 0.0f, 0.0f);
        glScalef(0.1,0.1,0.1);
        pTwoNodes[i]->draw();
        glPopMatrix();
    }
    glTranslatef(0.0, dif, 0.0);
    glRotatef(pTwoRot, 0.0, 1.0, 0.0);
    
    gluSphere(gluNewQuadric(), 0.15, 5, 5);
    glPopMatrix();
    
}