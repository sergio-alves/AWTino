// InputDevice.h

#ifndef _INPUTDEVICE_h
#define _INPUTDEVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "InputDeviceConfig.h"
#include "Point.h"
#include "MouseState.h"
#include "Bounds.h"

class InputDevice
{
public:
	InputDevice(const Bounds &);

	virtual MouseState * updateMouseState() = 0;
	virtual void doSetup() = 0;

	MouseState * getMouseState();
	MouseState * getPreviousMouseState();

protected:
	MouseState * ms;
	MouseState * oldms;
	Bounds * displayBounds;
};

#endif

