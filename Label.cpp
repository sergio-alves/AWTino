#include "Label.h"

Label::Label(const PROGMEM char  *  t) : Component() {
	setText(t);
	setTextSize(1);
}

Label::Label() : Label("Label"){
}

void Label::paint(Graphics * g) {
	if (paintComponent) {

		calcBounds();

		if (mouseIsOverComponent)
			g->setTextColor(Color::Grey.toAdafruitColor());
		else
			g->setTextColor(getTextColor()->toAdafruitColor());

		g->setCursor(getBounds()->x + getOffset()->x, getBounds()->y + getOffset()->y);
		g->setTextSize(getTextSize());
		g->print(text);
		paintComponent = false;
	}
}

void Label::setText(const PROGMEM char  *  t) {
	text = t;
};

const PROGMEM char  *  Label::getText() {
	return text;
};

void Label::setTextSize(byte s) {
	textSize = s;
	calcBounds();
};

byte Label::getTextSize() {
	return textSize;
};

void Label::calcBounds(){
	bounds->width = (strlen_P(text) * 6) - 1 + padding->getLeft() + padding->getRight() + borderSize->getLeft() + borderSize->getRight();
	bounds->height = 8 + padding->getTop() + padding->getBottom() + borderSize->getTop() + borderSize->getBottom();

	// on each bounds recalc redraw the component
	paintComponent = true;
};
