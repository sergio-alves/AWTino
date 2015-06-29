#ifndef _ALVISOFT_TESTAPP_H
#define _ALVISOFT_TESTAPP_H

#include "GfxApplication.h"
#include "MouseEvents.h"
#include "Label.h"
#include "WString.h"
#include "Component.h"
#include "Button.h"
#include "ProgressBar.h"
#include "Image.h"

class TestApp : public GfxApplication, public MouseEvents {
  public:
    TestApp();
	void initialize(void);
	void onMouseMove(void * sender, Point *);
	void onMouseClick(void * sender, byte);
	void onMouseButtonReleased(void * sender, MouseState *, byte);
	void onMouseButtonPressed(void * sender, MouseState *, byte);

private:
	Label * lbl;
	Button * btn1;
	ProgressBar * pb;

};

#endif
