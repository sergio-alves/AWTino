#ifndef _GFXAPPLICATION_H
#define _GFXAPPLICATION_H

#include "Arduino.h"
#include "Commons.h"
#include "Container.h"
#include "Component.h"
#include "Graphics.h"
#include "MouseEvents.h"

class GfxApplication {

public:
	GfxApplication(void);
	~GfxApplication(void);

public:
	void doLoop(void);
public:
	void doSetup(void);
	void displayFPS(boolean);
	virtual void initialize() = 0;

protected:
	Container * getContainer(void);
	void paint(Graphics * g);
	void paintMousePointer(Graphics *);
	void updateMouseState(void);
	void convertAnalogMouseMoveToPixels(int, int);
	boolean doesMousePositionChanged(int, int);
	void updateMouseCoordinates(int, int);
	void updateMouseButtonsState(void);

private:
	//Mouse related variables
	MouseState * ms;
	MouseState * oms;
	int b1pressedmillis, b2pressedmillis;
	boolean drawMousePointer;

	// The components collection and counter
	Container * container;
	Component * focusedComponent;
	Component * previousFocusedComponent;

	// Stores the time in ms from last frame rendering
	int refreshScreenMillis;
	int refreshMouseMillis;

	// The Screen Driver for the application 
	Graphics * g;

	//Display/or not the fps
	boolean dfps = false;
	int fpsmillis, fpscounter, fps, oldfps;
	char fpsbuffer[7];
	char _buffer[32];

	//The colors
	Color * bgColor;
	Color * textColor;
	Color * mousePointer;
};

#endif
