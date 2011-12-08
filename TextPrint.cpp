

#include "TextPrint.h"
#include <GL\freeglut.h>
#include <GL\GL.h>

TextPrint::TextPrint(void)
{
}


TextPrint::~TextPrint(void)
{
}

// Prints characters from GLUT in the 3d world.
// TODO: figure out why the text is dissapearing though.
/*
GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18

*/

void TextPrint::bitText(int x, int y, int z, 
	float r, float g, float b, void * font, char *string)
{
  glColor3f( r, g, b );
  glRasterPos3f(x, y, z);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

void TextPrint::hudText(int x, int y, int z, 
	float r, float g, float b, void * font, char *string)
{


}

