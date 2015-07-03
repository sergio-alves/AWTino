// 
// 
// 

#include "Image.h"

Image::Image() {
	setBorderSize(QuadValue(1));
	setPadding(QuadValue(1));
}

const PROGMEM char * Image::getFileName() {
	return fname;
}

void Image::setFileName(const PROGMEM char * fn) {
	fname = fn;
	paintComponent = true;
}

void Image::paint(Graphics * g) {
	if (paintComponent) {
		
		int imageWidth = bounds->width - borderSize->getLeft() - borderSize->getRight() - padding->getLeft() - padding->getRight();
		int imageHeight = bounds->height - borderSize->getTop() - borderSize->getBottom() - padding->getTop() - padding->getBottom();

		//Draws border
		for (byte i = 0; i < getBorderSize()->getTop(); i++)
			g->drawFastHLine(getBounds()->x + i, getBounds()->y + i, getBounds()->width - 2 * i, Color::DarkGrey.toAdafruitColor());

		for (byte i = 0; i < getBorderSize()->getRight(); i++)
			g->drawFastVLine(getBounds()->x + getBounds()->width - i, getBounds()->y + i, getBounds()->height - 2 * i, Color::DarkGrey.toAdafruitColor());

		for (byte i = 0; i < getBorderSize()->getBottom(); i++)
			g->drawFastHLine(getBounds()->x + i, getBounds()->y + getBounds()->height - i, getBounds()->width - 2 * i, Color::DarkGrey.toAdafruitColor());

		for (byte i = 0; i < getBorderSize()->getLeft(); i++)
			g->drawFastVLine(getBounds()->x + i, getBounds()->y + i, getBounds()->height - 2 * i, Color::DarkGrey.toAdafruitColor());
	
		g->bmpDraw(fname, getBounds()->x + getOffset()->x, getBounds()->y + getOffset()->y, imageWidth, imageHeight);
		
		g->drawPixel(getBounds()->x + getOffset()->x, getBounds()->y + getOffset()->y, Color::Red.toAdafruitColor());
		paintComponent = false;
	}
}

void Image::calcBounds(){

};