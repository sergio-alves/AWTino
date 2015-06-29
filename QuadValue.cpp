#include "QuadValue.h"

QuadValue::QuadValue(const QuadValue & pad) {
	top = pad.top;
	left = pad.left;
	right = pad.right;
	bottom = pad.bottom;
}

void QuadValue::set(const QuadValue & pad) {
	top = pad.top;
	left = pad.left;
	right = pad.right;
	bottom = pad.bottom;
}

QuadValue::QuadValue(byte t, byte r, byte b, byte l){
	top = t;
	left = l;
	right = r;	
	bottom = b;
}

QuadValue::QuadValue(byte tb, byte lr) {
	top = tb;
	bottom = tb;
	left = lr;
	right = lr;
};

QuadValue::QuadValue(byte v) {
	top = v;
	bottom = v;
	left = v;
	right = v;
};

byte QuadValue::getTop() {
	return top;
};

void QuadValue::setTop(byte t) {
	top = t;
};

byte QuadValue::getLeft() {
	return left;
};

void QuadValue::setLeft(byte l) {
	left = l;
};

byte QuadValue::getRight() {
	return right;
};

void QuadValue::setRight(byte r) {
	right = r;
};

byte QuadValue::getBottom() {
	return bottom;
};

void QuadValue::setBottom(byte b){
	bottom = b;
};


