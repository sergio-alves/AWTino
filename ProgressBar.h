// ProgressBar.h

#ifndef _PROGRESSBAR_h
#define _PROGRESSBAR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Component.h"
#include "Graphics.h"

class ProgressBar : public Component
{
public:
	ProgressBar();
	void setProgressValue(int p);
	void setMaxValue(int p);
	int getMaxValue();
	int getProgressValue();
	void paint(Graphics *);
	void setProgressBarColor(const Color &);
	Color * getProgressBarColor();

protected:
	void calcBounds(void);

private:
	int maxValue;
	int currentValue;

	Color * progressBarColor;
};

#endif

