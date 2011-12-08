

#ifndef H_TEXTPRINT
#define H_TEXTPRINT


class TextPrint
{
public:
	TextPrint(void);
	~TextPrint(void);
	// This prints a 
	void bitText(int x, int y, int z, float r, float g, float b, void * font, char *string);
	void hudText(int x, int y, int z, float r, float g, float b, void * font, char *string);
};

#endif