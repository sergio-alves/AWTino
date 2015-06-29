// Button.h

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <WString.h>
#include "Component.h"
#include "Graphics.h"
#include "Color.h"

class Button : public Component
{
public:
	Button(const char PROGMEM *);
	Button();
	void paint(Graphics *);
	void setText(const PROGMEM char  *);
	const PROGMEM char  *  getText();
	void setTextSize(byte);
	byte getTextSize();

protected:
	void calcBounds(void);

private:
	byte textSize;
	const PROGMEM char  * text;
};
#endif

