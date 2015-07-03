// QuadValue.h

#ifndef _QUADVALUE_h
#define _QUADVALUE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class QuadValue
{
public:
	QuadValue(byte, byte, byte, byte);
	QuadValue(byte, byte);
	QuadValue(byte);
	QuadValue(const QuadValue &);

	byte getTop();
	void setTop(byte);
	byte getLeft();
	void setLeft(byte);
	byte getRight();
	void setRight(byte);
	byte getBottom();
	void setBottom(byte);
	byte getTopPlusBottom(void);
	byte getLeftPlusRight(void);

	void set(const QuadValue &);

private:
	byte top;
	byte left;
	byte right;
	byte bottom;
};

#endif

