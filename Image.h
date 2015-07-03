// Image.h

#ifndef _IMAGE_h
#define _IMAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"
#include "Graphics.h"

class Image : public Component
{
public:
	Image();

	const PROGMEM char * getFileName();
	void setFileName(const PROGMEM char *);
	void paint(Graphics * g);
	void calcBounds(void);

protected:
	 const PROGMEM char * fname;

};

#endif

