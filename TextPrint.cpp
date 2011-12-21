
#ifdef TARGET_OS_MAC
    #include <OpenGL/OpenGL.h>
    #include <GLUT/GLUT.h>
#endif

#ifdef __linux__
  // Linux Includes Here
  #error Can't be compiled on Linux yet
#endif

#ifdef _WIN32 || _WIN64
    #include <GL\freeglut.h>
    #include <GL\GL.h>
#endif

#include "TextPrint.h"

TextPrint::TextPrint(void)
{
}


TextPrint::~TextPrint(void)
{
}

/*
GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18

*/



/*
 * Prints characters from GLUT in the 3d world which will always face the screen.
 *       Do not push or pop matrices before this!
 */


void TextPrint::bitText(int x, int y, int z, 
	float r, float g, float b, void * font, char *string)
{
    glDisable(GL_LIGHTING);
	glColor3f( r, g, b );
	glRasterPos3f(x/10, y/10, z/10);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
    glEnable(GL_LIGHTING);
}

// Standalone function that will automatically place words in a HUD.
void TextPrint::hudText(int x, int y, int zoom,
	float r, float g, float b, void * font, char *string)
{
	glColor3f( r, g, b );

	int len, i;
	
    glDisable(GL_LIGHTING);
	glRasterPos3f(x/10, y/10, zoom);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
    glEnable(GL_LIGHTING);
}

/*	Stroke fonts:
GLUT_STROKE_ROMAN
GLUT_STROKE_MONO_ROMAN
*/

void TextPrint::strokePrint(int x, int y, int z, 
	float r, float g, float b, char *string)
{
	char *p;
    
    glDisable(GL_LIGHTING);
    glPushMatrix();
	glColor3f(r,g,b);
    glTranslatef(x/10, y/10, z/10);
    for (p = string; *p; p++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    glPopMatrix();
	glEnable(GL_LIGHTING);

}