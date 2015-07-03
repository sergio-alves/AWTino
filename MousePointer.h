// MousePointer.h

#ifndef _MOUSEPOINTER_h
#define _MOUSEPOINTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "InputDevice.h"
#include "Bounds.h"
#include "MouseState.h"

class MousePointer : public InputDevice
{
public:
	MousePointer(const Bounds &);
	MouseState * updateMouseState();
	void doSetup();

protected:
	int tmp, xval, yval;
	boolean doesMousePositionChanged(int xval, int yval);
	void updateMouseCoordinates(int xval, int yval);
	void convertAnalogMouseMoveToPixels(int xval, int yval);

};

#endif

