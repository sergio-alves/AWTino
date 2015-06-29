#ifndef _ALVISOFT_GRAPHICS_H
#define _ALVISOFT_GRAPHICS_H

#include "Arduino.h"

#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <SD.h>


typedef uint16_t color;
#define BUFFPIXEL 20

class Graphics : public Adafruit_ST7735 {

  public:
    Graphics(uint8_t CS, uint8_t RS, uint8_t RST);
    void begin(int rotation);
	void bmpDraw(char *filename, uint8_t x, uint8_t y);

	uint16_t read16(File f);
	uint32_t read32(File f);
};

#endif
