#ifndef HUD_H
#define HUD_H

#include "Model.h"
#include "DrawableGeometry.h"
//#ifdef TARGET_OS_MAC
    //#include <OpenGL/OpenGL.h>
    //#include <GLUT/GLUT.h>
//#endif

//#ifdef __linux__
  // Linux Includes Here
  //#error Can't be compiled on Linux yet
//#endif

//#ifdef _WIN32 || _WIN64
//    #include <GL\freeglut.h>
//    #include <GL\GL.h>
//#endif


class Hud
{
public:
	Hud(void);
	~Hud(void);
	static void drawMeta();
	static void drawMini();
};

#endif