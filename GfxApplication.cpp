#include "GfxApplication.h"

GfxApplication::GfxApplication(void) {
	drawMousePointer = true;
	refreshScreenMillis = 0;
	refreshMouseMillis = 0;
	dfps = false;
	fpsmillis = 0;
	fpscounter = 0;
	fps = 0;
	oldfps = 0;

	// Starts Graphical driver:  
	g = new Graphics(TFT_DISP_CS, TFT_DISP_DC, TFT_DISP_RST);

	//Setup defaut container
	container = new Container();
	container->setBounds(Bounds(0, 0, g->width(), g->height(), g->getRotation()));
	focusedComponent = container;
	previousFocusedComponent = container;

	//Mouse management variables initialization
	ms = new MouseState(0, 0, false, false);
	oms = new MouseState(0, 0, false, false);

	//setup default colors
	bgColor = &Color::LightGrey;
	textColor = &Color::Black;
	mousePointer = &Color::Black;
}

GfxApplication::~GfxApplication(void) {
}

Container * GfxApplication::getContainer(void) {
	return container;
}

void GfxApplication::displayFPS(boolean val) {
	dfps = val;
}

void GfxApplication::doSetup(void) {
	// Starts Serial Module
	Serial.begin(115200);

	pinMode(MOUSE_BUTTON_1_IO, INPUT);           // set pin to input
	digitalWrite(MOUSE_BUTTON_1_IO, HIGH);       // turn on pullup resistors

	pinMode(MOUSE_BUTTON_2_IO, INPUT);           // set pin to input
	digitalWrite(MOUSE_BUTTON_2_IO, HIGH);       // turn on pullup resistors

	// Starts Graphical driver:  
	g->begin(1);
	g->fillScreen(bgColor->toAdafruitColor());

	initialize();
}

void GfxApplication::doLoop(void) {
	boolean found = false;

	if (millis() - refreshScreenMillis > SCREEN_REFRESH_RATE_MILLIS)
	{
		paint(g);
		refreshScreenMillis = millis();
	}

	// Display FPS
	if (dfps && (millis() - fpsmillis > 1000))
	{
		fpsmillis = millis();
		fps = fpscounter;
		fpscounter = 0;
	}

	// refresh mouse each 20ms ~ 40 refreshes/sec
	if (millis() - refreshMouseMillis > MOUSE_REFRESH_RATE_MILLIS) {
		refreshMouseMillis = millis();
		updateMouseState();
		previousFocusedComponent = focusedComponent;

		//Get object that has mouseover except container. If no object then focusedComponent is selected
		for (byte i = 0; i < container->getComponentsCount(); i++)
		{
			if (container->getComponent(i)->isMouseOver(ms)) {
				found = true;
				focusedComponent = container->getComponent(i);
				break;
			}
		}

		if (found) {
			if (focusedComponent != previousFocusedComponent) {
				previousFocusedComponent->setMouseExited();
				focusedComponent->setMouseEntered();
			}
		}
		else{
			focusedComponent = container;

			if (focusedComponent != previousFocusedComponent) {
				previousFocusedComponent->setMouseExited();
				focusedComponent->setMouseEntered();
			}
		}

		paintMousePointer(g);
	}
}

void GfxApplication::paintMousePointer(Graphics * g) {
	//draw mouse pointer
	if (drawMousePointer && oms != NULL && ms != NULL) {
		g->drawPixel(oms->x, oms->y, bgColor->toAdafruitColor());
		g->drawPixel(ms->x, ms->y, mousePointer->toAdafruitColor());
		drawMousePointer = false;
	}
}

void GfxApplication::paint(Graphics * g)
{
	//updates the fps counter
	fpscounter++;

	//display the fps
	if (dfps && oldfps != fps)
	{
		g->fillRect(0, 0, 35, 8, bgColor->toAdafruitColor());

		sprintf(fpsbuffer, "fps:%i", fps);
		fpsbuffer[6] = 0;

		g->setCursor(0, 0);
		g->setTextColor(textColor->toAdafruitColor());
		g->setTextSize(1);
		g->setTextWrap(true);
		g->print(fpsbuffer);

		oldfps = fps;
	}

	//draws container
	container->paint(g);
}

/*********************************************************************************************
 * Refresh Mouse State
 *********************************************************************************************/
void GfxApplication::updateMouseState(void) {
	int tmp, xval, yval;

	//save previous mouse state
	oms->set(ms);

	tmp = analogRead(A1);
	xval = tmp >= 0 ? tmp : 0;
	tmp = analogRead(A0);
	yval = tmp >= 0 ? tmp : 0;

	if (doesMousePositionChanged(xval, yval)) {
		updateMouseCoordinates(xval, yval);
		drawMousePointer = true;
	}

	//Updates mouse button state
	updateMouseButtonsState();
}

boolean GfxApplication::doesMousePositionChanged(int xval, int yval) {
	return !(((xval > AN_AXIS_CENTER_LOWER_BOUNDARY) && (xval < AN_AXIS_CENTER_HIGHER_BOUNDARY)) &&
		((yval > AN_AXIS_CENTER_LOWER_BOUNDARY) && (yval < AN_AXIS_CENTER_HIGHER_BOUNDARY)));
}

void GfxApplication::updateMouseButtonsState() {
	ms->b1 = !digitalRead(MOUSE_BUTTON_1_IO);
	ms->b2 = !digitalRead(MOUSE_BUTTON_2_IO);

	MouseEvents * me = focusedComponent->getMouseEvents();

	if (oms->b1 != ms->b1 && me != NULL) {
		//Button 1 changed
		//trigger onMouseButtonPressed if function is defined
		if (ms->b1) {
			me->onMouseButtonPressed(focusedComponent, ms, MOUSE_BUTTON_1);
			b1pressedmillis = millis();
			focusedComponent->setMousePressed(MOUSE_BUTTON_1);
		}

		//trigger onMouseButtonReleased if function is defined
		if (!ms->b1) {
			me->onMouseButtonReleased(focusedComponent, ms, MOUSE_BUTTON_1);
			focusedComponent->setMouseReleased(MOUSE_BUTTON_1);
		}
		//trigger onMouseClick if function is defined
		if (!ms->b1 && (millis() - b1pressedmillis < MOUSE_CLICK_INTERVAL))
			me->onMouseClick(focusedComponent, MOUSE_BUTTON_1);
	}

	if (oms->b2 != ms->b2 && me != NULL)
	{
		//Button 2 changed
		//trigger onMouseButtonPressed if function is defined
		if (ms->b2)
		{
			me->onMouseButtonPressed(focusedComponent, ms, MOUSE_BUTTON_2);
			b2pressedmillis = millis();
			focusedComponent->setMousePressed(MOUSE_BUTTON_2);
		}

		//trigger onMouseButtonReleased if function is defined
		if (!ms->b2){
			me->onMouseButtonReleased(focusedComponent, ms, MOUSE_BUTTON_2);
			focusedComponent->setMouseReleased(MOUSE_BUTTON_2);
		}

		//trigger onMouseClick if function is defined
		if (!ms->b2 && (millis() - b2pressedmillis < MOUSE_CLICK_INTERVAL))
			me->onMouseClick(focusedComponent, MOUSE_BUTTON_2);
	}
}

void GfxApplication::updateMouseCoordinates(int xval, int yval) {
	//Only update if joystick is manipulated
	convertAnalogMouseMoveToPixels(xval, yval);

	/*
	ST7735_TFTWIDTH  128
	ST7735_TFTHEIGHT 160
	*/

	ms->x = (ms->x < 0) ? 0 : ms->x;
	ms->y = (ms->y < 0) ? 0 : ms->y;

	if (getContainer()->getBounds()->rotation) // Display horizontal
	{
		//Horizontal
		ms->x = (ms->x > ST7735_TFTHEIGHT_18 - 1) ? ST7735_TFTHEIGHT_18 - 1 : ms->x;
		ms->y = (ms->y > ST7735_TFTWIDTH - 1) ? ST7735_TFTWIDTH - 1 : ms->y;
	}
	else
	{
		//Vertical
		ms->x = (ms->x > ST7735_TFTWIDTH - 1) ? ST7735_TFTWIDTH - 1 : ms->x;
		ms->y = (ms->y > ST7735_TFTHEIGHT_18 - 1) ? ST7735_TFTHEIGHT_18 - 1 : ms->y;
	}


}

void GfxApplication::convertAnalogMouseMoveToPixels(int xval, int yval) {
	if (xval < AN_AXIS_CENTER_LOWER_BOUNDARY)
		ms->x -= (int)((AN_AXIS_CENTER_LOWER_BOUNDARY - xval) / 100);
	if (xval > AN_AXIS_CENTER_HIGHER_BOUNDARY)
		ms->x += (int)((xval - AN_AXIS_CENTER_HIGHER_BOUNDARY) / 100);

	if (yval < AN_AXIS_CENTER_LOWER_BOUNDARY)
		ms->y -= (int)((AN_AXIS_CENTER_LOWER_BOUNDARY - yval) / 100);
	if (yval > AN_AXIS_CENTER_HIGHER_BOUNDARY)
		ms->y += (int)((yval - AN_AXIS_CENTER_HIGHER_BOUNDARY) / 100);
}


