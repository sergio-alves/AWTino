#include "ProgressBar.h"

ProgressBar::ProgressBar() {
	progressBarColor = &Color::Green;
	setBorderSize(QuadValue(1));
	setPadding(QuadValue(0));
}

void ProgressBar::setProgressBarColor(const Color & c) {
	progressBarColor->set(c);
}

Color * ProgressBar::getProgressBarColor() {
	return progressBarColor;
}


int ProgressBar::getMaxValue() {
	return maxValue;
};

int ProgressBar::getProgressValue(){
	return currentValue;
};

/**
 * Only accepts values from 0 to maxValue. if < 0 sets value to 0 and if > maxValue set it to maxValue.
 */
void ProgressBar::setProgressValue(int p) {
	currentValue = (p < 0) ? 0 : (p>maxValue) ? maxValue : p;
	paintComponent = true;
};

void ProgressBar::setMaxValue(int p){
	maxValue = p;
	paintComponent = true;
};

void  ProgressBar::paint(Graphics * g) {
	if (paintComponent) {
		//calcBounds();
		
		int widthToDraw = (int)(((float)currentValue / (float)maxValue) * (float)(getBounds()->width - getOffset()->x * 2));

		//Draws border
		for (byte i = 0; i < getBorderSize()->getTop(); i++)
			g->drawFastHLine(getBounds()->x + i, getBounds()->y + i, getBounds()->width -2*i, Color::DarkGrey.toAdafruitColor());

		for (byte i = 0; i < getBorderSize()->getRight(); i++)
			g->drawFastVLine(getBounds()->x +getBounds()->width - i, getBounds()->y + i, getBounds()->height - 2 * i, Color::DarkGrey.toAdafruitColor());

		for (byte i = 0; i < getBorderSize()->getBottom(); i++)
			g->drawFastHLine(getBounds()->x + i, getBounds()->y + getBounds()->height - i, getBounds()->width - 2 * i, Color::DarkGrey.toAdafruitColor());

		for (byte i = 0; i < getBorderSize()->getLeft(); i++)
			g->drawFastVLine(getBounds()->x + i, getBounds()->y + i, getBounds()->height - 2 * i, Color::DarkGrey.toAdafruitColor());


		g->fillRect(getBounds()->x + getOffset()->x, getBounds()->y + getOffset()->y, getBounds()->width - getPadding()->getLeftPlusRight() - getBorderSize()->getLeftPlusRight(), getBounds()->height - getPadding()->getTopPlusBottom() - getBorderSize()->getTopPlusBottom() , getBgColor()->toAdafruitColor());
		g->fillRect(getBounds()->x + getOffset()->x, getBounds()->y + getOffset()->y, widthToDraw, getBounds()->height - 2 * getOffset()->y, progressBarColor->toAdafruitColor());

		paintComponent = false;
	}
};

void  ProgressBar::calcBounds(void) {

	//if (bounds != NULL && padding != NULL && borderSize != NULL) {
	//	bounds->width = (strlen_P(text) * 6) - 1 + padding->getLeft() + padding->getRight() + borderSize->getLeft() + borderSize->getRight();
	//	bounds->height = 8 + padding->getTop() + padding->getBottom() + borderSize->getTop() + borderSize->getBottom();
	//}
};