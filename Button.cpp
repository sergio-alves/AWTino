#include "Button.h"

Button::Button(const PROGMEM char  *  t) : Component() {
	setText(t);
	setTextSize(1);
	setBorderSize(QuadValue(1));
	setPadding(QuadValue(3));
}

Button::Button() : Button(("Label")) {
}

void Button::paint(Graphics * g) {
	if (paintComponent) {
		calcBounds();

		if (mouseIsOverComponent)
			g->fillRect(getBounds()->x, getBounds()->y, getBounds()->width, getBounds()->height, Color(200, 200, 200).toAdafruitColor());
		else
			g->fillRect(getBounds()->x, getBounds()->y, getBounds()->width, getBounds()->height, Color::Grey.toAdafruitColor());

		if (mouseb1PressedComponent) {
			//If pressed 
			g->drawFastHLine(getBounds()->x, getBounds()->y, getBounds()->width, Color::Grey.toAdafruitColor());
			g->drawFastHLine(getBounds()->x, getBounds()->y + getBounds()->height, getBounds()->width, Color::DarkGrey.toAdafruitColor());
			g->drawFastVLine(getBounds()->x, getBounds()->y, getBounds()->height, Color::LightGrey.toAdafruitColor());
			g->drawFastVLine(getBounds()->x + getBounds()->width, getBounds()->y, getBounds()->height, Color::DarkGrey.toAdafruitColor());
		}
		else
		{
			//Normal
			g->drawFastHLine(getBounds()->x, getBounds()->y, getBounds()->width, Color::DarkGrey.toAdafruitColor());
			g->drawFastHLine(getBounds()->x, getBounds()->y + getBounds()->height, getBounds()->width, Color::DarkGrey.toAdafruitColor());
			g->drawFastVLine(getBounds()->x, getBounds()->y, getBounds()->height, Color::DarkGrey.toAdafruitColor());
			g->drawFastVLine(getBounds()->x + getBounds()->width, getBounds()->y, getBounds()->height, Color::DarkGrey.toAdafruitColor());
		}


		g->setCursor(getBounds()->x + getOffset()->x, getBounds()->y + getOffset()->y);
		if (mouseIsOverComponent)
			g->setTextColor(getTextColor()->toAdafruitColor(), Color(200, 200, 200).toAdafruitColor());
		else
			g->setTextColor(getTextColor()->toAdafruitColor(), Color::Grey.toAdafruitColor());
		g->setTextSize(getTextSize());
		g->println(text);

		paintComponent = false;
	}
}

void Button::setText(const PROGMEM char  *  t) {
	text = t;
	paintComponent = true;
};

const PROGMEM char  *  Button::getText() {
	return text;
};

void Button::setTextSize(byte s) {
	textSize = s;
	paintComponent = true;
};

byte Button::getTextSize() {
	return textSize;
};

void Button::calcBounds(){
	if (bounds != NULL && padding != NULL && borderSize != NULL) {
		bounds->width = (strlen_P(text) * 6) - 1 + padding->getLeft() + padding->getRight() + borderSize->getLeft() + borderSize->getRight();
		bounds->height = 8 + padding->getTop() + padding->getBottom() + borderSize->getTop() + borderSize->getBottom();
	}
};
