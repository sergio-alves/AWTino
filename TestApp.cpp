#include "TestApp.h"


void TestApp::initialize(void) {
	byte index = 0;


	displayFPS(true);

	getContainer()->attachMouseEvents(this);

	lbl = new Label(F("Test"));
	index = getContainer()->append(lbl);
	lbl->attachMouseEvents(this);
	lbl->setPosition(Point(0, 10));

	btn1 = new Button("Inc");

	index = getContainer()->append(btn1);
	btn1->attachMouseEvents(this);
	btn1->setPosition(Point(0, 20));

	pb = new ProgressBar();
	index = getContainer()->append(pb);
	pb->setMaxValue(100);
	pb->setProgressValue(30);
	pb->setBounds(Bounds(0, 40, 100, 10, 1));
	pb->attachMouseEvents(this);

	/*
	Serial.print(F("Added component label with id : "));
	Serial.println(index);
	Serial.flush();
	*/

	/*
	if (DEBUG) {
		Serial.print(F("Going to add Button component"));
		Serial.println(index);
	}
	*/

	/*

	Serial.print(F("Added component Button with id : "));
	Serial.println(index);
	Serial.flush();

	Serial.println(F("Set Text To button"));
	Serial.flush();

	Serial.println(F("Attached mouse events"));
	Serial.flush();
	*/

	/*
	*/

}

TestApp::TestApp() {
}

void TestApp::onMouseMove(void * sender, Point * p) {
	Serial.println("mv");
};

void TestApp::onMouseButtonPressed(void * sender, MouseState *, byte buttonMask) {
	if (buttonMask == 1)
		Serial.println("bp1");
	else
		Serial.println("bp2");
};

void TestApp::onMouseButtonReleased(void * sender, MouseState *, byte buttonMask) {
	if (buttonMask == 1)
		Serial.println("br1");
	else
		Serial.println("br2");
};

void TestApp::onMouseClick(void * sender, byte buttonMask) {
	if (sender == (void *)btn1) {
		pb->setProgressValue(pb->getProgressValue() + 10);
	}

	if (buttonMask == 1)
		Serial.println("bc1");
	else
		Serial.println("bc2");

};