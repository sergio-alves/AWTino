// 
// 
// 

#include "Image.h"

const PROGMEM char * Image::getFileName() {
	return fname;
}

void Image::setFileName(const PROGMEM char * fn) {
	fname = fn;
}

void Image::paint(Graphics * g) {
	if (paintComponent) {
		calcBounds();
