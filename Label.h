// Label.h

#ifndef _ALVISOFT_LABEL_h
#define _ALVISOFT_LABEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <WString.h>
#include "Component.h"
#include "Graphics.h"
#include "Color.h"

class Label : public Component
{
public:
	Label(const PROGMEM char  *);
	Label();
	void paint(Graphics *);
	void setText(const PROGMEM char  *);
	const PROGMEM char  *  getText();
	void setTextSize(byte);
	byte getTextSize();

protected:
	void calcBounds(void);

private:
	byte textSize;
	const PROGMEM char * text;
};

#endif

