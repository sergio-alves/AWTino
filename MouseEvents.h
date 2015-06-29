#ifndef _ALVISOFT_MOUSE_EVENTS_H
#define _ALVISOFT_MOUSE_EVENTS_H

#include "Arduino.h"
#include "Point.h"
#include "MouseState.h"

class MouseEvents
{
  public:
	  virtual void onMouseMove(void * sender, Point *) = 0;
	  virtual void onMouseClick(void * sender, byte) = 0;
	  virtual void onMouseButtonReleased(void * sender, MouseState *, byte) = 0;
	  virtual void onMouseButtonPressed(void * sender, MouseState *, byte) = 0;
};

#endif

