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

char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
        
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}

void strokeNumber(int n)
{
    if(n == 0)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
    char * c = itoa(n, 10);
    for(int i = 0; c[i] != NULL; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c[i]);
        glTranslatef(100, 0.0, 0.0);
    }
}

bool Hud::compiled = false;       //True iff displayList names a valid glDisplayList
GLuint Hud::metaDl;
GLuint Hud::miniDl;
GLuint Hud::mapvDl;
GLuint Hud::typeMappingDlA;
GLuint Hud::typeMappingDlB;

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
    
    
    Hud::typeMappingDlA = glGenLists(1);
    glNewList(Hud::typeMappingDlA, GL_COMPILE);
    
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(0.001, 0.001, 0.001);
    glTranslatef(-460, 300, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '<');
    glTranslatef(70, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '-');
    glTranslatef(70, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'w');
    glTranslatef(150, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
    glTranslatef(70, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '-');
    glTranslatef(70, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '>');
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslated(-0.5, 0.0, 0.0);
    glColor3f(WATER_R, WATER_G, WATER_B);
    glBegin(GL_QUADS);
    glVertex3d(0.0, 0.25, 0.0);
    glVertex3d(0.25, 0.25, 0.0);
    glVertex3d(0.25, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glPushMatrix();
    glTranslatef(0.1, -0.1, 0.0);
    glScalef(0.001, 0.001, 0.001);
    glColor3f(1.0, 1.0, 1.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'a');
    glPopMatrix();
    glTranslated(0.25, 0.0, 0.0);
    glColor3f(EARTH_R, EARTH_G, EARTH_B);
    glBegin(GL_QUADS);
    glVertex3d(0.0, 0.25, 0.0);
    glVertex3d(0.25, 0.25, 0.0);
    glVertex3d(0.25, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glPushMatrix();
    glTranslatef(0.1, -0.1, 0.0);
    glScalef(0.001, 0.001, 0.001);
    glColor3f(1.0, 1.0, 1.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 's');
    glPopMatrix();
    glTranslated(0.25, 0.0, 0.0);
    glColor3f(WIND_R, WIND_G, WIND_B);
    glBegin(GL_QUADS);
    glVertex3d(0.0, 0.25, 0.0);
    glVertex3d(0.25, 0.25, 0.0);
    glVertex3d(0.25, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glPushMatrix();
    glTranslatef(0.1, -0.1, 0.0);
    glScalef(0.001, 0.001, 0.001);
    glColor3f(1.0, 1.0, 1.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'd');
    glPopMatrix();
    glTranslated(0.25, 0.0, 0.0);
    glColor3f(FIRE_R, FIRE_G, FIRE_B);
    glBegin(GL_QUADS);
    glVertex3d(0.0, 0.25, 0.0);
    glVertex3d(0.25, 0.25, 0.0);
    glVertex3d(0.25, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glPushMatrix();
    glTranslatef(0.1, -0.1, 0.0);
    glScalef(0.001, 0.001, 0.001);
    glColor3f(1.0, 1.0, 1.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'f');
    glPopMatrix();
    glPopMatrix();
    
    glEndList();
    
    
    Hud::typeMappingDlB = glGenLists(1);
    glNewList(Hud::typeMappingDlB, GL_COMPILE);
    
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(0.001, 0.001, 0.001);
    glTranslatef(-460, 300, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '<');
    glTranslatef(70, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '-');
    glTranslatef(70, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'i');
    glTranslatef(150, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
    glTranslatef(70, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '-');
    glTranslatef(70, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '>');
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(-0.5, 0.0, 0.0);
    glColor3f(WATER_R, WATER_G, WATER_B);
    glBegin(GL_QUADS);
    glVertex3d(0.0, 0.25, 0.0);
    glVertex3d(0.25, 0.25, 0.0);
    glVertex3d(0.25, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glPushMatrix();
    glTranslatef(0.1, -0.1, 0.0);
    glScalef(0.001, 0.001, 0.001);
    glColor3f(1.0, 1.0, 1.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'j');
    glPopMatrix();
    glTranslated(0.25, 0.0, 0.0);
    glColor3f(EARTH_R, EARTH_G, EARTH_B);
    glBegin(GL_QUADS);
    glVertex3d(0.0, 0.25, 0.0);
    glVertex3d(0.25, 0.25, 0.0);
    glVertex3d(0.25, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glPushMatrix();
    glTranslatef(0.1, -0.1, 0.0);
    glScalef(0.001, 0.001, 0.001);
    glColor3f(1.0, 1.0, 1.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'k');
    glPopMatrix();
    glTranslated(0.25, 0.0, 0.0);
    glColor3f(WIND_R, WIND_G, WIND_B);
    glBegin(GL_QUADS);
    glVertex3d(0.0, 0.25, 0.0);
    glVertex3d(0.25, 0.25, 0.0);
    glVertex3d(0.25, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glPushMatrix();
    glTranslatef(0.1, -0.1, 0.0);
    glScalef(0.001, 0.001, 0.001);
    glColor3f(1.0, 1.0, 1.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'l');
    glPopMatrix();
    glTranslated(0.25, 0.0, 0.0);
    glColor3f(FIRE_R, FIRE_G, FIRE_B);
    glBegin(GL_QUADS);
    glVertex3d(0.0, 0.25, 0.0);
    glVertex3d(0.25, 0.25, 0.0);
    glVertex3d(0.25, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glPushMatrix();
    glTranslatef(0.1, -0.1, 0.0);
    glScalef(0.001, 0.001, 0.001);
    glColor3f(1.0, 1.0, 1.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, ';');
    glPopMatrix();
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
    glPushMatrix();
    glTranslated(-5.0, 0.0, -10.0);
    glScalef(2.0, 2.0, 2.0);
    glCallList(typeMappingDlA);
    glTranslatef(0.0, 1.0, 0.0);
    glRotated(90, 1.0, 0.0, 0.0);
    if(Model::getSelf()->mgame->attacker->owner == Model::getSelf()->playerArray[0])
        Model::getSelf()->mgame->attacker->draw();
    else
        Model::getSelf()->mgame->defender->draw();
    glPopMatrix();
    glPushMatrix();
    glTranslated(5.0, 0.0, -10.0);
    glScalef(2.0, 2.0, 2.0);
    glCallList(typeMappingDlB);
    glTranslatef(0.0, 1.0, 0.0);
    glRotated(90, 1.0, 0.0, 0.0);
    if(Model::getSelf()->mgame->attacker->owner == Model::getSelf()->playerArray[1])
        Model::getSelf()->mgame->attacker->draw();
    else
        Model::getSelf()->mgame->defender->draw();
    glPopMatrix();
    glPopMatrix();

}

void Hud::drawMapv()
{
    if(!Hud::compiled) return;
    
    glPushMatrix();
    glTranslatef(0.0, 0.0, -2);
    glColor3f(1.0, 1.0, 1.0);
    glScalef(0.001, 0.001, 0.001);
    glTranslatef(-1000, -1000, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 's');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'p');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'a');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'c');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
    glTranslatef(80, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 't');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
    glTranslatef(80, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'b');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'u');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'y');
    glTranslatef(80, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 's');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'h');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'i');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'p');
    glTranslatef(80, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '(');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '1');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
    glTranslatef(60, 40, 0.0);
    gluSphere(gluNewQuadric(), 40, 5, 5);
    glTranslatef(40, -40, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, ')');
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 0.0, -2);
    if(Model::getSelf()->playerturn == P_ONE_TURN)
        glColor3f(PLAYER_1_R, PLAYER_1_G, PLAYER_1_B);
    else
        glColor3f(PLAYER_2_R, PLAYER_2_G, PLAYER_2_B);
    glScalef(0.001, 0.001, 0.001);
    glTranslatef(-700, 800, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '\'');
    glTranslatef(30, 0, 0.0);
    if(Model::getSelf()->playerturn == P_ONE_TURN)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, 'q');
    else
        glutStrokeCharacter(GLUT_STROKE_ROMAN, 'p');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '\'');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 't');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
    glTranslatef(80, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'n');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'd');
    glTranslatef(80, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 't');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'u');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'r');
    glTranslatef(30, 0, 0.0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'n');
    glPopMatrix();

    
    
    
    setColor(0.5f, 0.5f, 0.5f, 1.0f, 0.1f, 0.5f, 0.7f);
    setGLColor();
    glCallList(mapvDl);
    float dif = -2.0f/((float)NUM_TYPES+2.0f);
    glPushMatrix();
    glTranslated(-1.5, 0.2, 0.0);
    glTranslatef(0.0, 1.0, -2.0);
    glTranslatef(0.0, dif, 0.0);
    
    glPushMatrix();
    //glTranslated(0.1, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glScalef(0.001, 0.001, 0.001);
    glTranslated(200.0, 0.0, 0.0);
    //glRotated(-90, 1.0, 0.0, 0.0);
    strokeNumber(pOneShip->owner->numShips);
    glPopMatrix();
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
        //glTranslated(0.1, 0.0, 0.0);
        glColor3f(1.0, 1.0, 1.0);
        glScalef(0.001, 0.001, 0.001);
        glTranslated(200.0, 0.0, 0.0);
        //glRotated(-90, 1.0, 0.0, 0.0);
        if(i == 0)
            strokeNumber(pOneShip->owner->waterNodesOwned);
        else if(i == 1)
            strokeNumber(pOneShip->owner->earthNodesOwned);
        else if(i == 2)
            strokeNumber(pOneShip->owner->windNodesOwned);
        else if(i == 3)
            strokeNumber(pOneShip->owner->fireNodesOwned);
        else if(i == 4)
            strokeNumber(pOneShip->owner->darkNodesOwned);

        glPopMatrix();
        glPushMatrix();
        if(Model::getSelf()->playerturn == P_ONE_TURN)
            pOneRot+=0.1f;
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
    glPushMatrix();
    //glTranslated(0.1, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glScalef(0.001, 0.001, 0.001);
    glTranslated(200.0, 0.0, 0.0);
    //glRotated(-90, 1.0, 0.0, 0.0);
    strokeNumber(pOneShip->owner->darkResources);
    glPopMatrix();
    glRotatef(pOneRot, 0.0, 1.0, 0.0);

    gluSphere(gluNewQuadric(), 0.15, 5, 5);
    glPopMatrix();
    
    
    
    glPushMatrix();
    glTranslated(1.5, 0.2, 0.0);
    glTranslatef(0.0, 1.0, -2.0);
    glTranslatef(0.0, dif, 0.0);
    glPushMatrix();
    //glTranslated(0.1, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glScalef(0.001, 0.001, 0.001);
    glTranslated(-270.0, 0.0, 0.0);
    //glRotated(-90, 1.0, 0.0, 0.0);
    glPushMatrix();
    if(pTwoShip->owner->numShips > 10)
        glTranslatef(-180, 0.0, 0.0);
    if(pTwoShip->owner->numShips > 100)
        glTranslatef(-180, 0.0, 0.0);
    strokeNumber(pTwoShip->owner->numShips);
    glPopMatrix();
    glPopMatrix();
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
        //glTranslated(0.1, 0.0, 0.0);
        glColor3f(1.0, 1.0, 1.0);
        glScalef(0.001, 0.001, 0.001);
        glTranslated(-270.0, 0.0, 0.0);
        //glRotated(-90, 1.0, 0.0, 0.0);
        if(i == 0)
        {
            glPushMatrix();
            if(pTwoShip->owner->waterNodesOwned > 10)
                glTranslatef(-180, 0.0, 0.0);
            if(pTwoShip->owner->waterNodesOwned > 100)
                glTranslatef(-180, 0.0, 0.0);
            strokeNumber(pTwoShip->owner->waterNodesOwned);
            glPopMatrix();
        }
        else if(i == 1)
        {
            glPushMatrix();
            if(pTwoShip->owner->earthNodesOwned > 10)
                glTranslatef(-180, 0.0, 0.0);
            if(pTwoShip->owner->earthNodesOwned > 100)
                glTranslatef(-180, 0.0, 0.0);
            strokeNumber(pTwoShip->owner->earthNodesOwned);
            glPopMatrix();
        }
        else if(i == 2)
        {
            glPushMatrix();
            if(pTwoShip->owner->windNodesOwned > 10)
                glTranslatef(-180, 0.0, 0.0);
            if(pTwoShip->owner->windNodesOwned> 100)
                glTranslatef(-180, 0.0, 0.0);
            strokeNumber(pTwoShip->owner->windNodesOwned);
            glPopMatrix();
        }
        else if(i == 3)
        {
            glPushMatrix();
            if(pTwoShip->owner->fireNodesOwned > 10)
                glTranslatef(-180, 0.0, 0.0);
            if(pTwoShip->owner->fireNodesOwned > 100)
                glTranslatef(-180, 0.0, 0.0);
            strokeNumber(pTwoShip->owner->fireNodesOwned);
            glPopMatrix();
        }
        else if(i == 4)
        {
            glPushMatrix();
            if(pTwoShip->owner->darkNodesOwned > 10)
                glTranslatef(-180, 0.0, 0.0);
            if(pTwoShip->owner->darkNodesOwned > 100)
                glTranslatef(-180, 0.0, 0.0);
            strokeNumber(pTwoShip->owner->darkNodesOwned);
            glPopMatrix();
        }
        
        glPopMatrix();
        glPushMatrix();
        if(Model::getSelf()->playerturn == P_TWO_TURN)
            pTwoRot+=0.1f;
        else
            pTwoRot+=0.01f;
        if(pTwoRot == 360.0f)
            pTwoRot = 0.0;
        glRotatef(pTwoRot, 0.0, 1.0, 0.0);       
        glRotatef(80, 1.0f, 0.0f, 0.0f);
        glScalef(0.1,0.1,0.1);
        pTwoNodes[i]->draw();
        glPopMatrix();
    }
    glTranslatef(0.0, dif, 0.0);
    glPushMatrix();
    //glTranslated(0.1, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glScalef(0.001, 0.001, 0.001);
    glTranslated(-270.0, 0.0, 0.0);
    //glRotated(-90, 1.0, 0.0, 0.0);
    glPushMatrix();
    if(pTwoShip->owner->darkResources > 10)
        glTranslatef(-180, 0.0, 0.0);
    if(pTwoShip->owner->darkResources > 100)
        glTranslatef(-180, 0.0, 0.0);
    strokeNumber(pTwoShip->owner->darkResources);
    glPopMatrix();
    glPopMatrix();
    glRotatef(pTwoRot, 0.0, 1.0, 0.0);
    
    gluSphere(gluNewQuadric(), 0.15, 5, 5);
    glPopMatrix();
    
	//if (Model::getSelf()->zoom < 0) 
	//	TextPrint::hudText(0, 17, -2, 0.77f, 0.29f, 0.13f,GLUT_BITMAP_TIMES_ROMAN_24, "WARNING: ZOOMED PAST RECOMENDED AREA");


}