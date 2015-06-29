#include "Component.h"

Component::Component(){
	parent = NULL;
	me = NULL;
	
	paintComponent = true;
	
	bounds = new Bounds(0, 0, 0, 0, 1);
	offset = new Point(0, 0);
	padding = new QuadValue(0,0,0,0);
	borderSize = new QuadValue(0,0,0,0);
	
	bgColor = &Color::LightGrey;
	textColor = &Color::Black;
}

void Component::setParent(Component * p) {
	parent = p;
}

Bounds * Component::getBounds() {
	return bounds;
}

void Component::setBounds(const Bounds & b) {
	bounds->set(b);
	paintComponent = true;
}

void Component::setPosition(const Point & p){
	bounds->x = p.x;
	bounds->y = p.y;
}


void Component::attachMouseEvents(MouseEvents * _me) {
	me = _me;
}

void Component::detachMouseEvents(void) {
	me = NULL;
}

MouseEvents * Component::getMouseEvents(void) {
	return me;
}

boolean Component::isMouseOver(MouseState * ms) {
	return (ms->x >= bounds->x) && (ms->y >= bounds->y) && (ms->x <= (bounds->x + bounds->width)) && (ms->y <= (bounds->y + bounds->height));
}

void Component::setBorderSize(const QuadValue & bs) {
	borderSize->set(bs);
	paintComponent = true;
};

QuadValue * Component::getBorderSize() {
	return borderSize;
};

void Component::setMouseEntered(){
	mouseIsOverComponent = true;
	paintComponent = true;
};

void Component::setMouseExited(){
	mouseIsOverComponent = false;
	paintComponent = true;
};

void Component::setMousePressed(byte button){
	if (button == MOUSE_BUTTON_1) {
		mouseb1PressedComponent = true;
	}
	else if (button == MOUSE_BUTTON_2) {
		mouseb2PressedComponent = true;
	}

	paintComponent = true;
}

void Component::setMouseReleased(byte button){
	if (button == MOUSE_BUTTON_1) {
		mouseb1PressedComponent = false;
	}
	else if (button == MOUSE_BUTTON_2) {
		mouseb2PressedComponent = false;
	}

	paintComponent = true;
}

void Component::setBgColor(Color * c){
	bgColor = c;
	paintComponent = true;
}

void Component::setTextColor(Color * c){
	textColor = c;
	paintComponent = true;
}

void Component::setBgColor(const Color & c){
	bgColor->set(c);
	paintComponent = true;
}

void Component::setTextColor(const Color & c){
	textColor->set(c);
	paintComponent = true;
}

Color * Component::getBgColor(){
	return bgColor;
}

Color * Component::getTextColor(){
	return textColor;
}

void Component::setPadding(const QuadValue & pad) {
	padding->set(pad);
	paintComponent = true;
}

QuadValue * Component::getPadding() {
	return padding;
}

Point * Component::getOffset(){
	offset->x = padding->getLeft() + borderSize->getLeft();
	offset->y = padding->getTop() + borderSize->getTop();

	return offset;
}