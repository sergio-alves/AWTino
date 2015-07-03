#include "TestApp.h"


void TestApp::initialize(void) {
	byte index = 0;


	displayFPS(true);

	getContainer()->attachMouseEvents(this);

	lbl = new Label("Test");
	getContainer()->append(lbl);
	lbl->attachMouseEvents(this);
	lbl->setPosition(Point(0, 10));

	btn1 = new Button("Inc");
	getContainer()->append(btn1);
	btn1->attachMouseEvents(this);
	btn1->setPosition(Point(0, 20));

	btn2 = new Button("Dec");
	getContainer()->append(btn2);
	btn2->attachMouseEvents(this);
	btn2->setPosition(Point(60, 20));

	pb = new ProgressBar();
	getContainer()->append(pb);
	pb->setMaxValue(100);
	pb->setProgressValue(30);
	pb->setBounds(Bounds(0, 40, 100, 10, 1));
	pb->attachMouseEvents(this);

	img = new Image();
	getContainer()->append(img);
	img->setBounds(Bounds(10, 60, 30, 30, 1));
	img->setFileName("16_16_3.bmp");
	img->attachMouseEvents(this);
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
		pb->setProgressValue(pb->getProgressValue() + 5);
	}

	if (sender == (void *)btn2) {
		pb->setProgressValue(pb->getProgressValue() - 5);
	}

};