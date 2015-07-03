#include "GfxApplication.h"

GfxApplication::GfxApplication(void) : GfxApplication(NULL, NULL){
	g = new Graphics(TFT_DISP_CS, TFT_DISP_DC, TFT_DISP_RST);
	inputDevice = new MousePointer(Bounds(0, 0, g->width(), g->height(), g->getRotation()));
	container->setBounds(Bounds(0, 0, g->width(), g->height(), g->getRotation()));
}

GfxApplication::GfxApplication(Graphics * _g, InputDevice * _inputDevice) {
	drawMousePointer = true;
	refreshScreenMillis = 0;
	refreshMouseMillis = 0;
	dfps = false;
	fpsmillis = 0;
	fpscounter = 0;
	fps = 0;
	oldfps = 0;


	// Starts Graphical driver:  
	g = _g;

	//Setup defaut container
	container = new Container();
	if (g!= NULL)
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

	inputDevice = _inputDevice;
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
	Serial.begin(SERIAL_BAUDRATE);

	inputDevice->doSetup();

	//the cs chip select 
	pinMode(SD_CS, OUTPUT);
	digitalWrite(SD_CS, LOW);

	Serial.print(F("Initializing SD card : "));

	if (!SD.begin(SD_CS)) {
		Serial.println(F("failed!"));
	}
	else{
		Serial.println(F("OK!"));
	}

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


void GfxApplication::updateMouseState(void) {
	int tmp, xval, yval;

	//save previous mouse state
	oms->set(ms);
	ms->set(inputDevice->updateMouseState());

	if (oms->x != ms->x || oms->y != ms->y) {
		drawMousePointer = true;
	}

	//Updates mouse button state
	triggerMouseEvents();
}

void GfxApplication::triggerMouseEvents() {
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
