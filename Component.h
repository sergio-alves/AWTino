#ifndef _ALVISOFT_COMPONENT_H
#define _ALVISOFT_COMPONENT_H

#include "Commons.h"
#include "Graphics.h"
#include "MouseState.h"
#include "Point.h"
#include "Bounds.h"
#include "MouseEvents.h"
#include "QuadValue.h"
#include "Color.h"


class Component {
public:
	Component();
	virtual void paint(Graphics *) = 0;
	boolean isMouseOver(MouseState * ms);
	void setParent(Component * p);
	Bounds * getBounds();
	void setBounds(const Bounds& b);

	void attachMouseEvents(MouseEvents * _me);
	void detachMouseEvents(void);
	MouseEvents * getMouseEvents(void);

	void setMousePressed(byte);
	void setMouseReleased(byte);
	void setMouseEntered();
	void setMouseExited();

	void setBgColor(Color *);
	void setTextColor(Color *);
	void setBgColor(const Color &);
	void setTextColor(const Color &);

	void setPosition(const Point &);

	Color * getBgColor();
	Color * getTextColor();
	void setBorderSize(const QuadValue &);
	void setPadding(const QuadValue &);
	QuadValue * getBorderSize();
	QuadValue * getPadding();
	Point * getOffset();

protected:
	virtual void calcBounds(void) = 0;

	boolean mouseIsOverComponent = false;
	boolean mouseb1PressedComponent = false;
	boolean mouseb2PressedComponent = false;

	Bounds * bounds;
	Component * parent;
	MouseEvents * me;
	Point * offset;

	boolean paintComponent;

	QuadValue * borderSize;
	QuadValue * padding;

	Color * bgColor;
	Color * textColor;

};

#endif
